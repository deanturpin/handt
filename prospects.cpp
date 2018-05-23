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

  const unsigned long window_size = 24 * 2;
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

        // Run the strategy library and record if the target has been achieved
        for (const auto &strategy : strategy::library(a, b))
          successes[strategy].push_back(max > target ? 1 : -1);

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

  std::vector<std::pair<double, std::string>> results;

  // Create results report
  for (const auto &strat : successes) {

    const long orders = strat.second.size();
    const auto sum =
        std::accumulate(strat.second.cbegin(), strat.second.cend(), 0);
    const auto name = strat.first;
    results.push_back({100.0 * sum / orders, name});
  }

  // Report sorted results
  std::sort(results.begin(), results.end());
  std::cout << "\nStrategy summary\t%\n";
  for (const auto &r : results)
    std::cout << r.second << '\t' << std::setprecision(0) << std::fixed
              << r.first << '\n';
}
