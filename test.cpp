#include <vector>
#include <sstream>
#include <functional>
#include <numeric>
#include <iomanip>

namespace lft {

using result = std::pair<std::string, bool>;
using series = const std::vector<double> &;
using threshold = const double &;

result dipper(series s, threshold t) {
    const double average =
        std::accumulate(s.cbegin(), s.cend(), 0.0,
                        [](auto &sum, const auto &i) { return sum + i; }) /
        s.size();

    const double spot = s.back();

    return result(
      "dipper" + std::to_string(t),
      average / spot > t
      );
}

result riser(series s, threshold t) {
    const double average =
        std::accumulate(s.cbegin(), s.cend(), 0.0,
                        [](auto &sum, const auto &i) { return sum + i; }) /
        s.size();

    const double spot = s.back();

    return result(
      "riser" + std::to_string(t),
      spot / average > t
      );
}

result ski_jump(series s, threshold &t) {

    const unsigned long mid = s.size() / 2;
    const double back =
        std::accumulate(s.begin(), std::next(s.begin(), mid), 0.0,
                        [](auto &s, auto &i) { return s + i; }) / mid;

    const double front =
        std::accumulate(s.rbegin(), std::next(s.rbegin(), mid), 0.0,
                        [](auto &s, auto &i) { return s + i; }) / mid;


    const double spot = s.back();

    return result(
      "skijump" + std::to_string(t),
      back / front > t && spot / front > 1.05
      );
}

// Strategy library
const std::vector<
std::function<
std::pair<std::string, bool>(std::vector<double>, double)>
> strategy_library{

  dipper,
  riser,
  ski_jump,
};

}

#include <iostream>
#include <fstream>
#include <algorithm>
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
  const std::vector<double> thresholds {1.05, 1.1, 1.2, 1.3};

  std::stringstream results;
  std::copy(thresholds.cbegin(), thresholds.cend(), std::ostream_iterator<double>(results, ","));
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


  // Open the previous results and compare
  std::ifstream pass("results.txt");
  if (pass.good()) {

    std::stringstream previous;
    previous << pass.rdbuf();

    if (results.str() != previous.str())
      std::cout << "Test fail\n";

    std::cout << results.str();
  }
  else
    std::cout << "Couldn't find test results\n";
}
