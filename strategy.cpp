#include <algorithm>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>

#include "handt.h"
#include "strategy.h"

int main() {

  std::vector<std::pair<std::string, std::vector<long>>> summary;

  // Read latest prices
  const auto &prices = handt::get_prices();

  // The size of the window we're using to decide whether to trade
  const unsigned long window_size = 24;

  // How far we're going to look ahead for maturity from the beginning of the
  // analysis window
  const unsigned long look_ahead = window_size * 3;

  // Target return
  const double target_percentage = 1.05;
  unsigned long window_count = 0;
  unsigned long total_orders = 0;

  // Test strategies on each series
  for (const auto &p : prices)
    if (!p.series.empty()) {

      // Set up some iterators
      auto a = p.series.begin();
      auto b = std::next(p.series.begin(), window_size);
      auto c = std::next(p.series.begin(), look_ahead);

      // Back test all historic prices in fixed-size windows starting from the
      // oldest
      while (c < p.series.cend()) {

        // Find the max in the subsequent prices
        const auto max = *std::max_element(b, c);
        const auto spot = *std::prev(b);
        const auto target = target_percentage * spot;

        // Run the strategy library and record if the target has been achieved
        for (const auto &name : strategy::library(a, b)) {

          ++total_orders;

          auto it =
              std::find_if(summary.rbegin(), summary.rend(),
                           [&name](const auto &s) { return s.first == name; });

          // Check if we have an entry for this strategy, if not create an empty
          // one and update the iterator
          if (it == summary.rend()) {
            summary.push_back({name, {}});
            it = summary.rbegin();
          }

          it->second.push_back(max > target ? 1 : 0);
        }

        // Nudge all iterators along
        std::advance(a, 1);

        std::advance(b, 1);
        std::advance(c, 1);

        ++window_count;
      }
    }

  const auto average_percentage = [](const auto &begin, const auto &end) {
    const auto size = std::distance(begin, end);
    return size > 0.0 ? 100.0 * std::accumulate(begin, end, 0.0) / size : 0.0;
  };

  // Sort the strategy summary
  std::sort(summary.begin(), summary.end(),
            [&average_percentage](const auto &a, const auto &b) {
              return average_percentage(a.second.cbegin(), a.second.cend()) >
                     average_percentage(b.second.cbegin(), b.second.cend());
            });

  // Find the top strategies
  std::vector<std::string> popping_strategies;
  for (const auto &strat : summary)
    if (70.0 < average_percentage(strat.second.cbegin(), strat.second.cend()))
      popping_strategies.push_back(strat.first);
    else
      break;

  // Look over the most recent prices to find what's popping
  std::stringstream popping;
  for (const auto &p : prices)
    if (!p.series.empty()) {

      // Create iterators for the most recent window of prices
      const auto begin = std::prev(p.series.cend(), window_size);
      const auto end = p.series.cend();

      // Run strategy library over recent prices
      for (const auto &strategy_name : strategy::library(begin, end))
        for (const auto &popper : popping_strategies)
          if (strategy_name.find(popper) != std::string::npos)
            popping << p.from_symbol << '\t' << p.to_symbol << '\t'
                    << strategy_name << '\t' << p.exchange << '\t'
                    << p.series.back() << '\n';
    }

  // Calculate strategy summary
  std::stringstream strategy_summary;
  for (const auto &strat : summary)
    strategy_summary << std::setprecision(1) << std::fixed << strat.first
                     << '\t' << average_percentage(strat.second.cbegin(),
                                                   strat.second.cend())
                     << '\t' << strat.second.size() << '\n';

  // Dump new orders (or clear order file if there are none)
  std::ofstream orders("orders.csv");
  if (orders.good())
    orders << popping.str();

  // Report potential new orders based on the best performing strategies
  std::cout << "# Recent recommendations\n";
  std::cout << "Potential trades from the top performing stategies below. "
               "See the [raw price data](prices.csv)\n";
  std::cout << "<pre>\n";
  std::cout << "From\tTo\tStrategy\t\tExch\tSpot\n";
  std::cout << (popping.str().empty() ? "I GOT NOTHING :(\n" : popping.str());
  std::cout << "</pre>\n";

  // Create strategy summary
  std::cout << "# Strategy back-test performance\n";
  std::cout
      << "Strategies are back-tested and sorted by percentage of orders that "
         "returned a profit of at least "
      << -100 + 100.0 * target_percentage << " % within "
      << look_ahead - window_size
      << " hours. "
         "The more orders the greater the confidence in the result.\n";
  std::cout << "* " << prices.size() << " currency pairs polled\n";
  std::cout << "* " << look_ahead - window_size << "-hour sell window\n";
  std::cout << "* " << window_count << " opportunities to trade\n";
  std::cout << "* " << total_orders << " orders executed\n";
  std::cout << "<pre>\n";
  std::cout << "Strategy\t\t%\tOrders\n";
  std::cout << strategy_summary.str();
  std::cout << "</pre>\n";
}
