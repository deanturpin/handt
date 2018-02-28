#include <algorithm>
#include <functional>
#include <iomanip>
#include <numeric>
#include <sstream>
#include <vector>

namespace lft {

// STD shortcuts
using std::string;
using std::pair;
using std::vector;
using std::accumulate;
using std::next;
using std::to_string;

// Parameteric shortcuts
using result = pair<string, bool>;
using series = const vector<double> &;
using threshold = const double &;

// Helper routines to define strategies
double SPOT(series);
double AVERAGE(series);
double RECENT_AVERAGE(series);
double DISTANT_AVERAGE(series);
string NAME(const string, threshold t);

// Strategies

// |xxxxxxx |
// |xxxxxxx |
// |xxxxxxx |
// |xxxxxxxx|
result crashing(series s, threshold t) {
  const auto name = NAME("crashing", t);
  const bool exec = AVERAGE(s) / SPOT(s) > t;
  return result(name, exec);
}

// |       x|
// |       x|
// |       x|
// |xxxxxxxx|
result spiking(series s, threshold t) {
  const auto name = NAME("spiking", t);
  const bool exec = SPOT(s) / AVERAGE(s) > t;
  return result(name, exec);
}

// |xxxx    |
// |xxxx    |
// |xxxxxxxx|
// |xxxxxxxx|
result stepping_up(series s, threshold t) {
  const auto name = NAME("stepping_up", t);
  const bool exec = RECENT_AVERAGE(s) / DISTANT_AVERAGE(s) > t;
  return result(name, exec);
}

result stepping_down(series s, threshold t) {
  const auto name = NAME("stepping_down", t);
  const bool exec = DISTANT_AVERAGE(s) / RECENT_AVERAGE(s) > t;
  return result(name, exec);
}

result rolling_average(series s, threshold t) {
  const auto name = NAME("roll_average", t);
  const unsigned long length = 10;
  const double average =
      std::accumulate(s.crbegin(), next(s.crend(), length), 0.0) / length;

  const bool exec = SPOT(s) / average > t;
  return result(name, exec);
}

result average_inter(series s, threshold t) {
  const auto name = NAME("average_inter", t);
  const unsigned long filter1 = 10 * t;
  const unsigned long filter2 = 20 * t;

  // Average with a small window
  const double short_average =
      std::accumulate(s.crbegin(), next(s.crbegin(), filter1), 0.0) / filter1;

  // Average with a longer window
  const double long_average =
      std::accumulate(s.crbegin(), next(s.crbegin(), filter2), 0.0) / filter2;

  const bool exec = short_average > long_average;
  return result(name, exec);
}

result average_compare(series s, threshold t) {
  const auto name = NAME("average_comp", t);
  const unsigned long ratio = s.size() / t;
  const double recent_average =
      std::accumulate(s.crbegin(), std::next(s.crbegin(), ratio), 0.0,
                      [](auto &sum, auto &i) { return sum + i; }) /
      ratio;

  const bool exec = recent_average > AVERAGE(s);
  return result(name, exec);
}

// |xxxx   x|
// |xxxx   x|
// |xxxxxxxx|
// |xxxxxxxx|
result jumping(series s, threshold t) {
  const auto name = NAME("jumping", t);
  const bool exec = stepping_down(s, t).second && spiking(s, t).second;
  return result(name, exec);
}

// |      xx|
// |    xxxx|
// |  xxxxxx|
// |xxxxxxxx|
result steady_rise(series s, threshold t) {
  const auto name = NAME("steady_rise", t);
  double trend = 0.0;
  for (auto i = s.cbegin(); i != std::prev(s.cend()); ++i)
    trend += (*i < *std::next(i) ? 1.0 : -1.0);
  const bool exec = trend > s.size() * .75;
  return result(name, exec);
}

result kosovich(series s, threshold t) {
  const auto name = NAME("kosovich", t);
  const double high = *std::max_element(s.cbegin(), s.cend());
  const bool exec = SPOT(s) / high > t;
  return result(name, exec);
}

// Implementation of helper routines
double AVERAGE(series s) {
  return s.size() > 0.0
             ? accumulate(s.cbegin(), s.cend(), 0.0,
                          [](auto &sum, const auto &i) { return sum + i; }) /
                   s.size()
             : 0.0;
}

// Average of the most recent half of the series
double RECENT_AVERAGE(series s) {
  const unsigned long mid_point = s.size() / 2;
  return mid_point > 0.0
             ? accumulate(s.crbegin(), next(s.crbegin(), mid_point), 0.0,
                          [](auto &sum, const auto &i) { return sum + i; }) /
                   mid_point
             : 0.0;
}

// Average of the oldest half of the series
double DISTANT_AVERAGE(series s) {
  const unsigned long mid_point = s.size() / 2;
  return mid_point > 0.0
             ? accumulate(s.cbegin(), next(s.cbegin(), mid_point), 0.0,
                          [](auto &sum, const auto &i) { return sum + i; }) /
                   mid_point
             : 0.0;
}

string NAME(const string n, threshold t) { return to_string(t) + "-" + n; }
double SPOT(series s) { return s.back(); }

// Entry point into the library, returns a list of the strategy names that
// reported "buy" for the prices given
vector<string> run_strategies(series s) {

  // Strats that take thresholds
  const vector<double> thresholds{1.05, 1.1, 1.2, 1.3, 1.4};
  const vector<std::function<result(series, threshold)>> strategy_library1{
      crashing,      spiking,     jumping,  stepping_up,
      stepping_down, steady_rise, kosovich, rolling_average};

  // Strats that take ratios
  const vector<double> ratios{1, 2, 3, 4};
  const vector<std::function<result(series, threshold)>> strategy_library2{
      average_compare, average_inter};

  vector<string> trades;
  for (const auto &buy : strategy_library1)
    for (const auto &t : thresholds) {
      const auto b = buy(s, t);

      if (b.second)
        trades.push_back(b.first);
    }

  for (const auto &buy : strategy_library2)
    for (const auto &t : ratios) {
      const auto b = buy(s, t);

      if (b.second)
        trades.push_back(b.first);
    }

  return trades;
}
}
