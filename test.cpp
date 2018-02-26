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

// Strategy library
const std::vector<
std::function<
std::string(std::vector<double>, double)>
> strategy_library{

  spot_average2,
    ski_jump2,
};

}

#include <iostream>
#include <algorithm>

// Don't need to search for strategy

int main() {

  // Create a series of prices
  std::vector<double> series(100);
  std::iota(series.begin(), series.end(), 0);

  // Thresholds
  const std::vector<double> thresholds {7, 5, 4, 3, 2};

  // Ascending
  for (const auto &buy : lft::strategy_library)
    for (const auto &t : thresholds)
      std::cout << std::quoted(buy(series, t)) << "\n";

  // Descending
  std::sort(series.begin(), series.end());
  for (const auto &buy : lft::strategy_library)
    for (const auto &t : thresholds)
      std::cout << std::quoted(buy(series, t)) << "\n";

  // Spot is peak
  std::fill(series.begin(), series.end(), 1.0);
  series.back() = 10.0;

  for (const auto &buy : lft::strategy_library)
    for (const auto &t : thresholds)
      std::cout << std::quoted(buy(series, t)) << "\n";

  std::cout << series.back() << " spot\n";
}
