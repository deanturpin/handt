// Trading strategy routines

#ifndef LOW_FREQUENCY_TRADER_H
#define LOW_FREQUENCY_TRADER_H

#include <algorithm>
#include <numeric>
#include <string>
#include <vector>

namespace lft {

// Parameteric aliases to make the strategy definitions cleaner
using result = std::pair<std::string, bool>;
using series = const std::vector<double> &;
using param = const double &;

// Helper routines used to define strategies

double AVERAGE(series s) {
  return !s.empty()
             ? accumulate(s.cbegin(), s.cend(), 0.0,
                          [](auto &sum, const auto &i) { return sum + i; }) /
                   s.size()
             : 0.0;
}

// Average of the most recent half of the series
double RECENT_AVERAGE(series s) {
  const unsigned long mid_point = s.size() / 2;
  const std::vector<double> subset(s.crbegin(), next(s.crend(), mid_point));
  return AVERAGE(subset);
}

// Average of the oldest half of the series
double DISTANT_AVERAGE(series s) {
  const unsigned long mid_point = s.size() / 2;
  const std::vector<double> subset(s.cbegin(), next(s.cend(), mid_point));
  return AVERAGE(subset);
}

std::string NAME(const std::string n, param p) {
  return std::to_string(p).substr(0, 4) + "_" + n;
}

double THRESHOLD(param p) { return (100.0 + p) / 100.0; }
double SPOT(series s) { return s.back(); }

// The strategies

result flicking_down(series s, param p) {
  const auto name = NAME("flicking_down", p);
  const bool exec = AVERAGE(s) / SPOT(s) > THRESHOLD(p);
  return result(name, exec);
}

result flicking_up(series s, param p) {
  const auto name = NAME("flicking_up", p);
  const bool exec = SPOT(s) / AVERAGE(s) > THRESHOLD(p);
  return result(name, exec);
}

result stepping_up(series s, param p) {
  const auto name = NAME("stepping_up", p);
  const bool exec = RECENT_AVERAGE(s) / DISTANT_AVERAGE(s) > THRESHOLD(p);
  return result(name, exec);
}

result stepping_down(series s, param p) {
  const auto name = NAME("stepping_down", p);
  const bool exec = DISTANT_AVERAGE(s) / RECENT_AVERAGE(s) > THRESHOLD(p);
  return result(name, exec);
}

result rolling_average(series s, param p) {
  const auto name = NAME("roll_average", p);
  const unsigned long length = 10;
  const double average =
      std::accumulate(s.crbegin(), next(s.crbegin(), length), 0.0) / length;

  const bool exec = SPOT(s) / average > THRESHOLD(p);
  return result(name, exec);
}

result average_inter(series s, param p) {
  const auto name = NAME("average_inter", p);
  const unsigned long filter1 = 5.0 * p;
  const unsigned long filter2 = 10.0 * p;

  // Average with a small window
  const double short_average =
      std::accumulate(s.crbegin(), next(s.crbegin(), filter1), 0.0) / filter1;

  // Average with a longer window
  const double long_average =
      std::accumulate(s.crbegin(), next(s.crbegin(), filter2), 0.0) / filter2;

  const bool exec = short_average > long_average;
  return result(name, exec);
}

result average_compare(series s, param p) {
  const auto name = NAME("average_comp", p);
  const unsigned long ratio = s.size() / (p > 0 ? p : 1);
  const double recent_average =
      std::accumulate(s.crbegin(), std::next(s.crbegin(), ratio), 0.0,
                      [](auto &sum, const auto &i) { return sum + i; }) /
      ratio;

  const bool exec = recent_average > AVERAGE(s);
  return result(name, exec);
}

result ski_jumping(series s, param p) {
  const auto name = NAME("ski_jumping", p);
  const bool exec = stepping_down(s, p).second && flicking_up(s, p).second;
  return result(name, exec);
}

result back_to_front(series s, param p) {
  const auto name = NAME("back_to_front", p);
  const bool exec = s.front() / s.back() > THRESHOLD(p);
  return result(name, exec);
}

result front_to_back(series s, param p) {
  const auto name = NAME("front_to_back", p);
  const bool exec = s.back() / s.front() > THRESHOLD(p);
  return result(name, exec);
}

result steady_rising(series s, param p) {
  const auto name = NAME("steady_rising", p);

  // Check if the next value is larger than the current
  unsigned long trend = 0;
  for (auto i = s.cbegin(); i != std::prev(s.cend()); ++i)
    if (*i < *std::next(i))
      ++trend;

  // Execute if a significant proportion of intervals are increasing
  const bool exec = trend > s.size() / 2;
  return result(name, exec);
}

result kosovich(series s, param p) {
  const auto name = NAME("koskosovich", p);
  const double high = *std::max_element(s.cbegin(), std::prev(s.cend()));
  const bool exec = SPOT(s) / (high > 0 ? high : 1) > THRESHOLD(p);
  return result(name, exec);
}

result random_decision(series s, param p) {
  static_cast<void>(s);
  const auto name = NAME("rand_decision", p);
  const bool exec = handt::seconds_since_epoch() / 10 % 2 == 0;
  return result(name, exec);
}
}

#endif
