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

// INTERNAL ROUTINES

double AVERAGE(series s) {
  return s.size() > 0.0 ?
    accumulate(s.cbegin(), s.cend(), 0.0,
                      [](auto &sum, const auto &i) { return sum + i; }) /
      s.size() : 0.0;
}

double LEADING(series s) {

  // Find the mid point of the series
  const unsigned long mid_point = s.size() / 2;

  return mid_point > 0.0 ?
    accumulate(s.crbegin(), next(s.crend(), mid_point), 0.0,
                    [](auto &sum, const auto &i) { return sum + i; }) / mid_point
    : 0.0;
}

double TRAILING(series s) {

  // Find the mid point of the series
  const unsigned long mid_point = s.size() / 2;

  return mid_point > 0.0 ?
    accumulate(s.cbegin(), next(s.cend(), mid_point), 0.0,
                    [](auto &sum, const auto &i) { return sum + i; }) / mid_point
    : 0.0;
}

string NAME(const string n, threshold t){
  return n + "-" + to_string(t);
}

double SPOT(series s){
  return s.back();
}

// STRATEGIES

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
result stepping(series s, threshold t) {
  const auto name = NAME("stepping", t);
  const bool exec = TRAILING(s) / LEADING(s) > t;
  return result(name, exec);
}

// |xxxx   x|
// |xxxx   x|
// |xxxxxxxx|
// |xxxxxxxx|
result jumping(series s, threshold &t) {
  const auto name = NAME("jumping", t);
  const bool exec = stepping(s, t).second && spiking(s, t).second;
  return result(name, exec);
}

// Strategy library
const vector<std::function<result(series, threshold)>> strategy_library{
    crashing, spiking, jumping, stepping
};
}
