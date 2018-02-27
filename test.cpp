#include <vector>
#include <sstream>
#include <functional>
#include <numeric>
#include <iomanip>

namespace lft {

using result = std::pair<std::string, bool>;
using series = const std::vector<double>;
using threshold = const double;

result dipper(series &s, threshold &t) {
    const double average =
        std::accumulate(s.cbegin(), s.cend(), 0.0,
                        [](auto &sum, const auto &i) { return sum + i; }) /
        s.size();

    const double spot = s.back();

    // std::cout << average << "\n";
    // std::cout << average / spot << "\n";

    return result(
      "dipper" + std::to_string(t),
      average / spot > t
      );
}

result riser(series &s, threshold &t) {
    const double average =
        std::accumulate(s.cbegin(), s.cend(), 0.0,
                        [](auto &sum, const auto &i) { return sum + i; }) /
        s.size();

    const double spot = s.back();

    // std::cout << average << "\n";
    // std::cout << spot / average << "\n";

    return result(
      "riser" + std::to_string(t),
      spot / average > t
      );
}

// SKI JUMP
// std::string ski_jump(const std::vector<double> s, const double &t) {
//     const unsigned long mid = s.size() / 2;
//     const double back =
//         std::accumulate(s.begin(), std::next(s.begin(), mid), 0.0,
//                         [](auto &s, auto &i) { return s + i; }) / mid;
// 
//     const double front =
//         std::accumulate(s.rbegin(), std::next(s.rbegin(), mid), 0.0,
//                         [](auto &s, auto &i) { return s + i; }) / mid;
// 
//     const auto spot = s.back();
//     return back / front > t && spot / front > 1.05 ?
//       "ski_jump" + std::to_string(t) : "";
// }
// 
// ALWAYS
// result always_buy(series &s, threshold &t) {
//   return result("always_buy", true);
// }

// Strategy library
const std::vector<
std::function<
std::pair<std::string, bool>(std::vector<double>, double)>
> strategy_library{

  dipper,
  riser,
    // ski_jump,
    // always_buy,
};

}

#include <iostream>
#include <algorithm>
#include <iterator>

// Don't need to search for strategy
//

std::string dump_series(const std::vector<double> s) {

    const double average =
        std::accumulate(s.cbegin(), s.cend(), 0.0,
                        [](auto &sum, const auto &i) { return sum + i; }) /
        s.size();

  std::stringstream ss;
  std::copy(s.cbegin(), s.cend(), std::ostream_iterator<double>(ss, ","));
  ss << "\n";
  ss << average << " average\n";

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

  results << "ASCENDING\n" << dump_series(series);
  for (const auto &buy : lft::strategy_library)
    for (const auto &t : thresholds) {
      const auto r = buy(series, t);
      results << r.first << "\t" << std::boolalpha << r.second << "\n";
    }

  std::reverse(series.begin(), series.end());
  results << "DESCENDING\n" << dump_series(series);
  for (const auto &buy : lft::strategy_library)
    for (const auto &t : thresholds) {
      const auto r = buy(series, t);
      results << r.first << "\t" << std::boolalpha << r.second << "\n";
    }

  std::fill(series.begin(), series.end(), 1.0);
  series.back() = 1000.0;

  results << "SPOT IS PEAK\n" << dump_series(series);
  for (const auto &buy : lft::strategy_library)
    for (const auto &t : thresholds) {
      const auto r = buy(series, t);
      results << r.first << "\t" << std::boolalpha << r.second << "\n";
    }

  std::cout << results.str();
}
