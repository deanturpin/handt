#include <functional>
#include <iomanip>
#include <numeric>
#include <sstream>
#include <vector>

namespace lft {

// The parameters for a buy routine
using result = std::pair<std::string, bool>;
using series = const std::vector<double> &;
using threshold = const double &;

// Internal routines
double calculate_average(series s) {

  return s.size() > 0.0 ?
    std::accumulate(s.cbegin(), s.cend(), 0.0,
                      [](auto &sum, const auto &i) { return sum + i; }) /
      s.size() : 0.0;
}


// A dipping strategy
result dipping(series s, threshold t) {
  const double average = calculate_average(s);
  const double spot = s.back();

  return result("dipping" + std::to_string(t), average / spot > t);
}

// A rising strategy
result rising(series s, threshold t) {

  const double spot = s.back();
  const double average = calculate_average(s);

  return result("rising" + std::to_string(t), spot / average > t);
}


// A dipping strategy with a kick up at the end
result jumping(series s, threshold &t) {

  const bool dipper = dipping(s, t).second;
  const double spot = s.back();
  const double average = calculate_average(s);
  const std::string name = "jumping" + std::to_string(t);

  return result(name, dipper && spot / average > t);
}

// Strategy library
const std::vector<std::function<result(series, threshold)>> strategy_library{
    dipping, rising, jumping,
};
}

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

  series.back() = 1000.0;
  results << dump_series("Spot is max value", series);
  for (const auto &buy : lft::strategy_library)
    for (const auto &t : thresholds) {
      const auto r = buy(series, t);
      results << r.first << "\t" << std::boolalpha << r.second << "\n";
    }

  std::cout << results.str();
}
