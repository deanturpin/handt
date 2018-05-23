#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

#include "include/handt.h"
#include "include/strategy.h"

int main() {

  std::map<std::string, std::vector<long>> successes;

  // Read latest prices
  const auto &prices = handt::get_prices();
  std::cout << handt::get_pairs().size() << " pairs\n";
  std::cout << prices.size() << " prices\n";

  const unsigned long window_size = 200;
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
        const auto target = handt::sell_threshold * spot;

        // Run the strategy library
        const auto &buys = strategy::library(a, b);
        for (const auto &b : buys)
          if (max > target)
            successes[b].push_back(1);
          else
            successes[b].push_back(-1);

        // Move iterators to next window
        std::advance(a, window_size / 4);
        std::advance(b, window_size / 4);
        std::advance(c, window_size / 4);

        ++window_count;
      }
    }
  }

  std::cout << window_size << " window size\n";
  std::cout << window_count << " windows processed\n";
  std::cout << "\nStrategy summary\n";

  for (const auto &strat : successes) {
    std::cout << strat.first << '\t'
              << std::accumulate(strat.second.cbegin(), strat.second.cend(), 0)
              << "\t(" << strat.second.size() << ")\n";
  }
}
