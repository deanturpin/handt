#include <vector>
#include <functional>
#include <numeric>
#include <iomanip>

namespace lft {

// AVERAGE
std::string spot_average2(const std::vector<double> s, const double &t) {
    const double average =
        std::accumulate(s.cbegin(), s.cend(), 0.0,
                        [](auto &sum, const auto &i) { return sum + i; }) /
        s.size();

    const double spot = s.back();

    return average / spot > t ? "spot_average" + std::to_string(t) : "";
}

// SKI JUMP
std::string ski_jump2(const std::vector<double> s, const double &t) {
    const unsigned long mid = s.size() / 2;
    const double back =
        std::accumulate(s.begin(), std::next(s.begin(), mid), 0.0,
                        [](auto &s, auto &i) { return s + i; }) / mid;

    const double front =
        std::accumulate(s.rbegin(), std::next(s.rbegin(), mid), 0.0,
                        [](auto &s, auto &i) { return s + i; }) / mid;

    const auto spot = s.back();
    return back / front > t && spot / front > 1.05 ?
      "ski_jump" + std::to_string(t) : "";
}

// ALWAYS
std::string always_buy(const std::vector<double> s, const double &t) {
  return "always_buy";
}

// Strategy library
const std::vector<
std::function<
std::string(std::vector<double>, double)>
> strategy_library{

  spot_average2,
    ski_jump2,
    always_buy,
};

}

#include <iostream>
#include <algorithm>
#include <iterator>

// Don't need to search for strategy
//

void dump_series(const std::vector<double> s) {
  std::copy(s.cbegin(), s.cend(), std::ostream_iterator<double>(std::cout, ","));
  std::cout << "\n";
}

int main() {

  // Create a series of prices
  std::vector<double> series(10);
  std::iota(series.begin(), series.end(), 100);

  // Thresholds
  const std::vector<double> thresholds {1.05, 1.1, 1.2, 1.3};

  // Ascending
  dump_series(series);
  for (const auto &buy : lft::strategy_library)
    for (const auto &t : thresholds)
      std::cout << std::quoted(buy(series, t)) << "\n";

  // Descending
  std::reverse(series.begin(), series.end());
  dump_series(series);
  for (const auto &buy : lft::strategy_library)
    for (const auto &t : thresholds)
      std::cout << std::quoted(buy(series, t)) << "\n";

  // Spot is peak
  std::fill(series.begin(), series.end(), 1.0);
  series.back() = 1000.0;

  dump_series(series);
  for (const auto &buy : lft::strategy_library)
    for (const auto &t : thresholds)
      std::cout << std::quoted(buy(series, t)) << "\n";

}
