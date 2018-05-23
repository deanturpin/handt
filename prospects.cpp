#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

#include "handt.h"
#include "strategy.h"

int main() {

  std::vector<std::pair<std::string, std::vector<long>>> successes;

  // Read latest prices
  const auto &prices = handt::get_prices();
  std::cout << handt::get_pairs().size() << " pairs\n";
  std::cout << prices.size() << " prices\n";

  const unsigned long window_size = 24 * 1;
  unsigned long window_count = 0;

  // Test strategies on each series
  for (const auto &p : prices) {

    if (!p.series.empty()) {

      // Set up some iterators
      auto a = p.series.begin();
      auto b = std::next(p.series.begin(), window_size);
      auto c = std::next(p.series.begin(), window_size * 3);

      while (c < p.series.cend()) {

        // Find the max in the subsequent prices
        const auto max = *std::max_element(b, c);
        const auto spot = *std::prev(b);
        const auto target = 1.05 * spot;

        // Run the strategy library and record if the target has been achieved
        for (const auto &name : strategy::library(a, b)) {

          auto it =
              std::find_if(successes.rbegin(), successes.rend(),
                           [&name](const auto &s) { return s.first == name; });

          // Check if we have an entry for this strategy, if not create an empty
          // one and update the iterator
          if (it == successes.rend()) {
            successes.push_back({name, {}});
            it = successes.rbegin();
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
  }

  std::cout << window_size << " window size\n";
  std::cout << window_count << " windows processed\n";

  // Sort the strategy summary
  std::sort(
      successes.begin(), successes.end(), [](const auto &a, const auto &b) {

        const auto a_return =
            100.0 * std::accumulate(a.second.cbegin(), a.second.cend(), 0) /
            a.second.size();
        const auto b_return =
            100.0 * std::accumulate(b.second.cbegin(), b.second.cend(), 0) /
            b.second.size();

        return a_return > b_return;
      });

  // Create results report
  std::cout << "STRATEGY\t\t%\torders\n";
  for (const auto &strat : successes) {
    const long orders = strat.second.size();
    const auto sum =
        std::accumulate(strat.second.cbegin(), strat.second.cend(), 0);
    const auto name = strat.first;
    std::cout << name << '\t' << std::setprecision(1) << std::fixed
              << 100.0 * sum / orders << '\t' << orders << '\n';
  }
}
