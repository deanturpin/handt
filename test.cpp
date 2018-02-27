#include "strategy.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>

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

  std::stringstream results;

  {
    results << dump_series("Ascending series", series);
    const auto buys = lft::run_strategies(series);
    for (const auto &buy : buys)
      results << buy << "\n";
  }

  {
    std::reverse(series.begin(), series.end());
    results << dump_series("Descending series", series);
    const auto buys = lft::run_strategies(series);
    for (const auto &buy : buys)
      results << buy << "\n";
  }

  {
    series.back() = series.front() + 1;
    results << dump_series("Spot is max value", series);
    const auto buys = lft::run_strategies(series);
    for (const auto &buy : buys)
      results << buy << "\n";
  }

  std::cout << results.str();
}
