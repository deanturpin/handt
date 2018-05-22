#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

#include "include/handt.h"
#include "include/strategy.h"

int main() {

  std::map<std::string, long> successes;

  // Test strategies on each series
  for (const auto &p : handt::get_prices())
    if (!p.series.empty()) {

      // std::cout << '\n'
      //           << p.from_symbol << '-' << p.to_symbol << ' ' <<
      //           p.series.size()
      //           << " prices\n";

      // Set up some key iterators
      const auto a = p.series.cbegin();
      const auto b = std::next(p.series.cbegin(), 500);
      const auto c = p.series.cend();

      // std::cout << std::distance(a, b) << " size of frame\n";
      // std::cout << std::distance(a, c) << " size of series\n";

      // Find the max in the subsequent prices
      const auto max = *std::max_element(b, c);
      const auto spot = *std::prev(b);
      const auto target = handt::sell_threshold * spot;

      // std::cout << spot << " spot price\n";
      // std::cout << target << " target price\n";
      // std::cout << max << " max price\n";

      // Run the strategy library
      const auto &buys = strategy::library(a, b);
      // std::cout << buys.size() << " orders\n";
      for (const auto &b : buys)
        if (max > target)
          ++successes[b];
        else
          --successes[b];
    }

  std::cout << "\nStrategy summary\n";

  for (const auto &strat : successes)
    std::cout << strat.first << '\t' << strat.second << '\n';
}
