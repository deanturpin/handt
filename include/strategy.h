// Trading strategies

#ifndef STRATEGY_H
#define STRATEGY_H

#include <algorithm>
#include <functional>
#include <numeric>
#include <string>
#include <vector>

namespace strategy {

// Parameteric aliases to make the strategy definitions cleaner
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

double THRESHOLD(param p) { return (100.0 + p) / 100.0; }
double SPOT(series s) { return (!s.empty() ? s.back() : 1.0); }

// A strategy has a name and a buy routine
struct strategy_details {
  std::string name;
  std::function<bool(series, param)> buy;
};

bool find_and_run_strategy(const std::string name, series s, param p);
const std::vector<strategy_details> strategy_library {

    // The most recent price is significantly above the oldest
    {"new_above_old",
     [](series s, param p) { return s.back() / s.front() > THRESHOLD(p); }},

    {"steady_down",
     [](series s, param p) {
       return find_and_run_strategy("flicking_down", s, p) &&
              find_and_run_strategy("steady_riser", s, p);
     }},

    {"ski_jumping",
     [](series s, param p) {
       return find_and_run_strategy("stepping_down", s, p) &&
              find_and_run_strategy("flicking_up", s, p);
     }},

    {"flicking_down",
     [](series s, param p) { return AVERAGE(s) / SPOT(s) > THRESHOLD(p); }},

    {"roll_average",
     [](series s, param p) {
       const unsigned long length = 10;
       const double average =
           std::accumulate(s.crbegin(), next(s.crbegin(), length), 0.0) /
           length;

       return SPOT(s) / average > THRESHOLD(p);
     }},

    {"rolling_average2",
     [](series s, param p) {
       const unsigned long length = 100;
       const double average =
           std::accumulate(s.crbegin(), next(s.crbegin(), length), 0.0) /
           length;

       return SPOT(s) / average > THRESHOLD(p);
     }},

    {"average_inter",
     [](series s, param p) {
       const unsigned long filter1 = s.size() / 3;
       const unsigned long filter2 = s.size() / 2;

       // Small window average
       const double short_average =
           std::accumulate(s.crbegin(), next(s.crbegin(), filter1), 0.0) /
           filter1;

       // Longer window average
       const double long_average =
           std::accumulate(s.crbegin(), next(s.crbegin(), filter2), 0.0) /
           filter2;

       return short_average / long_average > THRESHOLD(p);
     }},

    {"koskosovich",
     [](series s, param p) {
       const double high = *std::max_element(s.cbegin(), std::prev(s.cend()));
       return SPOT(s) / (high > 0 ? high : 1) > THRESHOLD(p);
     }},

    // The oldest price is significantly above the most recent
    {"old_above_new",
     [](series s, param p) { return s.front() / s.back() > THRESHOLD(p); }},

    {"roll_average4",
     [](series s, param p) {
       const unsigned long length = 200;
       const double average =
           std::accumulate(s.crbegin(), next(s.crbegin(), length), 0.0) /
           length;

       return SPOT(s) / average > THRESHOLD(p);
     }},

    {"average_comp",
     [](series s, param p) {
       return RECENT_AVERAGE(s) / AVERAGE(s) > THRESHOLD(p);
     }},

    {"flicking_up",
     [](series s, param p) { return SPOT(s) / AVERAGE(s) > THRESHOLD(p); }},

    {"stepping_up",
     [](series s, param p) {
       return RECENT_AVERAGE(s) / DISTANT_AVERAGE(s) > THRESHOLD(p);
     }},

    {"stepping_down",
     [](series s, param p) {
       return DISTANT_AVERAGE(s) / RECENT_AVERAGE(s) > THRESHOLD(p);
     }},

    {"roll_average3",
     [](series s, param p) {
       const unsigned long length = 50;
       const double average =
           std::accumulate(s.crbegin(), next(s.crbegin(), length), 0.0) /
           length;
       return SPOT(s) / average > THRESHOLD(p);
     }},

    {"steady_rising2",
     [](series s, param p) {
       return find_and_run_strategy("steady_riser", s, p) &&
              find_and_run_strategy("new_above_old", s, p);
     }},

    // Check if the next value is larger than the current
    {"steady_riser",
     [](series s, param p) {
       unsigned long trend = 0;
       for (auto i = s.cbegin(); i != std::prev(s.cend()); ++i)
         if (*i < *std::next(i))
           ++trend;

       // Execute if a significant proportion of intervals are increasing
       return trend > (s.size() / 2) + p;
     }}
};

// Helper routine to find a strategy by name, used in the strategy library
// itself to reference and call other strategies
bool find_and_run_strategy(const std::string name, series s, param p) {
  const auto it = find_if(strategy_library.cbegin(), strategy_library.cend(),
                          [&name](const auto &s) { return s.name == name; });
  return (it != strategy_library.cend() ? it->buy(s, p) : false);
}

// Return a list of the strategy names that reported "buy" for the series of
// prices given
auto library(series s) {

  // Initial checks to assess viability of series
  const auto preflight_check = [](series s) {

    // Ensure there's a bit of activity
    auto unique_values(s);
    std::sort(unique_values.begin(), unique_values.end());
    const auto last = std::unique(unique_values.begin(), unique_values.end());
    unique_values.erase(last, unique_values.end());

    return unique_values.size() > 100;
  };

  const auto construct_name = [](const std::string n, param p) {
    return std::to_string(p).substr(0, 4) + "_" + n;
  };

  // Return potential prospects
  std::vector<std::string> prospects;

  // Test each strategy with a set of thresholds
  if (preflight_check(s))
    for (const auto &strat : strategy_library)
      for (const auto &t : {5.0, 10.0, 20.0, 30.0})
        if (strat.buy(s, t))
          prospects.push_back(construct_name(strat.name, t));

  return prospects;
}
}

#endif
