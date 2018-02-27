#include "strategy2.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>

// Don't need to search for strategy
//

std::string dump_series(const std::string title, std::vector<double> s) {

  const double average =
      std::accumulate(s.cbegin(), s.cend(), 0.0,
                      [](auto &sum, const auto &i) { return sum + i; }) /
      s.size();

  // Dump series stats
  std::stringstream ss;
  ss << "\n" << title << "\n";
  std::copy(s.cbegin(), s.cend(), std::ostream_iterator<double>(ss, ","));
  ss << "\n";
  ss << average << " average, ";
  ss << s.back() << " spot\n";

  return ss.str();
}

int main() {

  // Create a series of prices
  std::vector<double> series(20);
  std::iota(series.begin(), series.end(), 50);

  // Thresholds
  const std::vector<double> thresholds{1.05, 1.1, 1.2, 1.3};

  std::stringstream results;
  std::copy(thresholds.cbegin(), thresholds.cend(),
            std::ostream_iterator<double>(results, ","));
  results << " thresholds\n";

  results << dump_series("Ascending series", series);
  for (const auto &buy : lft::strategy_library)
    for (const auto &t : thresholds) {
      const auto r = buy(series, t);
      results << r.first << "\t" << std::boolalpha << r.second << "\n";
    }

  std::reverse(series.begin(), series.end());
  results << dump_series("Descending series", series);
  for (const auto &buy : lft::strategy_library)
    for (const auto &t : thresholds) {
      const auto r = buy(series, t);
      results << r.first << "\t" << std::boolalpha << r.second << "\n";
    }

  series.back() = series.front() + 1;
  results << dump_series("Spot is max value", series);
  for (const auto &buy : lft::strategy_library)
    for (const auto &t : thresholds) {
      const auto r = buy(series, t);
      results << r.first << "\t" << std::boolalpha << r.second << "\n";
    }

  std::cout << results.str();
}
