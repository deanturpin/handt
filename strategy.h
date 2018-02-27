#include <functional>
#include <iomanip>
#include <numeric>
#include <sstream>
#include <algorithm>
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
double LEADING(series);
double TRAILING(series);
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
  const bool exec = TRAILING(s) / LEADING(s) > t;
  return result(name, exec);
}

result stepping_down(series s, threshold t) {
  const auto name = NAME("stepping_down", t);
  const bool exec = LEADING(s) / TRAILING(s) > t;
  return result(name, exec);
}

result rolling_average(series s, threshold t) {
  const auto name = NAME("roll_average", t);
  const unsigned long length = 10;

  // Start from the beginning
  const auto start = s.cbegin();

  // End a filter length from the end
  const auto end = std::prev(s.cend(), length);

  vector<double> raverage;
  std::transform(start, end, std::back_inserter(raverage),
                 [&length](const auto &i) {
                 const auto start = &i;
                 const auto end = std::next(&i, length);
                 return std::accumulate(start, end, 0.0) / length;
                 });

  const bool exec = SPOT(s) / raverage.back() > t;
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

// TODO - rename to RECENT
double LEADING(series s) {

  // Find the mid point of the series
  const unsigned long mid_point = s.size() / 2;
  return mid_point > 0.0
             ? accumulate(s.crbegin(), next(s.crbegin(), mid_point), 0.0,
                          [](auto &sum, const auto &i) { return sum + i; }) /
                   mid_point
             : 0.0;
}

double TRAILING(series s) {

  // Find the mid point of the series
  const unsigned long mid_point = s.size() / 2;
  return mid_point > 0.0
             ? accumulate(s.cbegin(), next(s.cbegin(), mid_point), 0.0,
                          [](auto &sum, const auto &i) { return sum + i; }) /
                   mid_point
             : 0.0;
}

string NAME(const string n, threshold t) { return to_string(t) + "-" + n; }

double SPOT(series s) { return s.back(); }

vector<string> run_strategies(series s) {

  // Strats that take thresholds
  const vector<double> thresholds {1.05, 1.1, 1.2, 1.3, 1.4};
  const vector<std::function<result(series, threshold)>> strategy_library1{
    crashing, spiking, jumping, stepping_up, stepping_down, steady_rise,
    kosovich, rolling_average
  };

  // Strats that take ratios
  const vector<double> ratios {2, 3, 4};
  const vector<std::function<result(series, threshold)>> strategy_library2{
    average_compare
  };

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
