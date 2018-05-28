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
  const unsigned long window_size = 24 * 1;
  const unsigned long look_ahead = window_size * 3;
  unsigned long window_count = 0;
  const double target_percentage = 1.045;
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

  // Sort the strategy summary
  std::sort(summary.begin(), summary.end(), [](const auto &a, const auto &b) {

    const auto a_return =
        100.0 * std::accumulate(a.second.cbegin(), a.second.cend(), 0) /
        a.second.size();
    const auto b_return =
        100.0 * std::accumulate(b.second.cbegin(), b.second.cend(), 0) /
        b.second.size();

    return a_return > b_return;
  });

  // Find the top strategies
  std::vector<std::string> popping_strategies;
  for (const auto &strat : summary) {
    if (65.0 >
        100.0 * std::accumulate(strat.second.cbegin(), strat.second.cend(), 0) /
            strat.second.size())
      break;

    popping_strategies.push_back(strat.first);
  }

  // Look over the most recent prices to find what's popping
  std::stringstream popping;
  for (const auto &p : prices)
    if (!p.series.empty()) {

      const auto a = std::prev(p.series.cend(), window_size);
      const auto b = p.series.cend();

      for (const auto &strategy_name : strategy::library(a, b))
        for (const auto &popper : popping_strategies)
          if (strategy_name.find(popper) != std::string::npos) {
            const std::string pair_name = p.from_symbol + '_' + p.to_symbol;
            popping << "|[" << pair_name
                    << "](https://www.binance.com/trade.html?symbol="
                    << pair_name << ")|" << strategy_name << "|\n";
          }
    }

  // Calculate strategy summary
  std::stringstream strategy_summary;
  for (const auto &strat : summary) {
    const long orders = strat.second.size();
    const auto &results = strat.second;
    const auto sum = std::accumulate(results.cbegin(), results.cend(), 0);
    const auto name = strat.first;
    strategy_summary << std::setprecision(1) << std::fixed << name << '\t'
                     << 100.0 * sum / orders << '\t' << orders << '\n';
  }

  // Report possible orders based on the best performing strategies
  std::cout << "\n# Recent recommendations\n";
  std::cout << "Potential trades from the top performing stategies below. "
               "See the [raw price data](prices.csv)\n";
  std::cout << "\n|Currency pair|Strategy|\n";
  std::cout << "|---|---|\n";
  std::cout << (popping.str().empty() ? "|I GOT NOTHING|:(|\n" : popping.str());

  // Create strategy summary
  std::cout << "\n# Strategy performance\n";
  std::cout << "Strategies are sorted by percentage of orders that returned a "
               "profit of at least "
            << -100 + 100.0 * target_percentage << " % within "
            << look_ahead - window_size
            << " hours. "
               "The more orders the greater the confidence in the result.\n";
  std::cout << "* " << handt::get_pairs().size() << " tradable pairs\n";
  std::cout << "* " << prices.size() << " pairs tested\n";
  std::cout << "* " << look_ahead - window_size << "-hour trade window\n";
  std::cout << "* " << window_count << " opportunities to trade\n";
  std::cout << "* " << total_orders << " orders executed\n";
  std::cout << "<pre>\n";
  std::cout << "Strategy\t\t%\tOrders\n";
  std::cout << strategy_summary.str();
  std::cout << "</pre>\n";
}
