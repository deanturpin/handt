// Trading strategies

#ifndef STRATEGY_H
#define STRATEGY_H

#include <algorithm>
#include <functional>
#include <numeric>
#include <string>
#include <vector>

namespace lft {

// Parameteric aliases to make the strategy definitions cleaner
using result = std::pair<std::string, bool>;
using series = const std::vector<double>;
using param = const double &;

// Helper routines used to define strategies

double AVERAGE(series s) {
  return !s.empty()
             ? accumulate(s.cbegin(), s.cend(), 0.0,
                          [](auto &sum, const auto &i) { return sum + i; }) /
                   s.size()
             : 0.0;
}

// Average of the oldest half of the series
double DISTANT_AVERAGE(series s) {
  const unsigned long mid_point = s.size() / 2;
  const std::vector<double> subset(s.cbegin(), next(s.cbegin(), mid_point));
  return AVERAGE(subset);
}

// Average of the recent half of the series
double RECENT_AVERAGE(series s) {
  const unsigned long mid_point = s.size() / 2;
  const std::vector<double> subset(s.crbegin(), next(s.crbegin(), mid_point));
  return AVERAGE(subset);
}

std::string NAME(const std::string n, param p) {
  return std::to_string(p).substr(0, 4) + "_" + n;
}

double THRESHOLD(param p) { return (100.0 + p) / 100.0; }
double SPOT(series s) { return (!s.empty() ? s.back() : 1.0); }

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

result rolling_average2(series s, param p) {
  const auto name = NAME("roll_average2", p);
  const unsigned long length = 100;
  const double average =
      std::accumulate(s.crbegin(), next(s.crbegin(), length), 0.0) / length;

  const bool exec = SPOT(s) / average > THRESHOLD(p);
  return result(name, exec);
}

result rolling_average3(series s, param p) {
  const auto name = NAME("roll_average3", p);
  const unsigned long length = 50;
  const double average =
      std::accumulate(s.crbegin(), next(s.crbegin(), length), 0.0) / length;

  const bool exec = SPOT(s) / average > THRESHOLD(p);
  return result(name, exec);
}

result rolling_average4(series s, param p) {
  const auto name = NAME("roll_average4", p);
  const unsigned long length = 200;
  const double average =
      std::accumulate(s.crbegin(), next(s.crbegin(), length), 0.0) / length;

  const bool exec = SPOT(s) / average > THRESHOLD(p);
  return result(name, exec);
}

result average_inter(series s, param p) {
  const auto name = NAME("average_inter", p);
  const unsigned long filter1 = s.size() / 3;
  const unsigned long filter2 = s.size() / 2;

  // Small window average
  const double short_average =
      std::accumulate(s.crbegin(), next(s.crbegin(), filter1), 0.0) / filter1;

  // Longer window average
  const double long_average =
      std::accumulate(s.crbegin(), next(s.crbegin(), filter2), 0.0) / filter2;

  const bool exec = short_average / long_average > THRESHOLD(p);
  return result(name, exec);
}

result average_compare(series s, param p) {
  const auto name = NAME("average_comp", p);
  const bool exec = RECENT_AVERAGE(s) / AVERAGE(s) > THRESHOLD(p);
  return result(name, exec);
}

result ski_jumping(series s, param p) {
  const auto name = NAME("ski_jumping", p);
  const bool exec = stepping_down(s, p).second && flicking_up(s, p).second;
  return result(name, exec);
}

result old_above_new(series s, param p) {
  const auto name = NAME("old_above_new", p);
  const bool exec = s.front() / s.back() > THRESHOLD(p);
  return result(name, exec);
}

result new_above_old(series s, param p) {
  const auto name = NAME("new_above_old", p);
  const bool exec = s.back() / s.front() > THRESHOLD(p);
  return result(name, exec);
}

result steady_riser(series s, param p) {
  const auto name = NAME("steady_riser", p);

  // Check if the next value is larger than the current
  unsigned long trend = 0;
  for (auto i = s.cbegin(); i != std::prev(s.cend()); ++i)
    if (*i < *std::next(i))
      ++trend;

  // Execute if a significant proportion of intervals are increasing
  const bool exec = trend > (s.size() / 2) + p;
  return result(name, exec);
}

result steady_rising2(series s, param p) {
  const auto name = NAME("steady_rising2", p);
  const bool a = steady_riser(s, p).second;
  const bool b = new_above_old(s, p).second;
  const bool exec = a && b;
  return result(name, exec);
}

result kosovich(series s, param p) {
  const auto name = NAME("koskosovich", p);
  const double high = *std::max_element(s.cbegin(), std::prev(s.cend()));
  const bool exec = SPOT(s) / (high > 0 ? high : 1) > THRESHOLD(p);
  return result(name, exec);
}

result steady_down(series s, param p) {
  const auto name = NAME("steady_down", p);
  const bool exec = flicking_down(s, p).second && steady_riser(s, p).second;
  return result(name, exec);
}

bool preflight_check(series s) {

  // Ensure there's a bit of activity
  auto unique_values(s);
  std::sort(unique_values.begin(), unique_values.end());
  const auto last = std::unique(unique_values.begin(), unique_values.end());
  unique_values.erase(last, unique_values.end());

  return unique_values.size() > 100;
}

// Return a list of the strategy names that reported "buy" for the series of
// prices given
auto run_strategies(series s) {

  // Return potential prospects
  std::vector<std::string> prospects;

  // Perform some initial checks to assess viability of series
  if (preflight_check(s)) {

    // Create a library of strategies
    const std::vector<std::function<result(series, param)>> library{
        flicking_down,    flicking_up,      ski_jumping,      stepping_up,
        stepping_down,    steady_riser,     kosovich,         rolling_average,
        rolling_average2, rolling_average3, rolling_average4, old_above_new,
        new_above_old,    average_inter,    average_compare,  steady_rising2,
        steady_down};

    // Test each strategy with a set of thresholds
    for (const auto &buy : library) {
      for (const auto &t : {5.0, 10.0, 20.0, 30.0}) {
        const auto b = buy(s, t);
        if (b.second)
          prospects.push_back(b.first);
      }
    }
  }

  return prospects;
}
}

#endif
