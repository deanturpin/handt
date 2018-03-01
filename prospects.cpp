#include "strategy.h"
#include "utils.h"
#include <string>
#include <vector>
#include <algorithm>

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
using param = const double &;

// Helper routines to define strategies
double SPOT(series);
double AVERAGE(series);
double RECENT_AVERAGE(series);
double DISTANT_AVERAGE(series);
double THRESHOLD(param);
string NAME(const string, param p);

// Strategies

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
      std::accumulate(s.crbegin(), next(s.crend(), length), 0.0) / length;

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
  const unsigned long ratio = s.size() / p;
  const double recent_average =
      std::accumulate(s.crbegin(), std::next(s.crbegin(), ratio), 0.0,
                      [](auto &sum, auto &i) { return sum + i; }) /
      ratio;

  const bool exec = recent_average > AVERAGE(s);
  return result(name, exec);
}

result ski_jumping(series s, param p) {
  const auto name = NAME("ski_jumping", p);
  const bool exec = stepping_down(s, p).second && flicking_up(s, p).second;
  return result(name, exec);
}

result steady_rising(series s, param p) {
  const auto name = NAME("steady_rising", p);
  double trend = 0.0;
  for (auto i = s.cbegin(); i != std::prev(s.cend()); ++i)
    trend += (*i < *std::next(i) ? 1.0 : -1.0);
  const bool exec = trend > s.size() * .75;
  return result(name, exec);
}

result kosovich(series s, param p) {
  const auto name = NAME("kosovich", p);
  const double high = *std::max_element(s.cbegin(), s.cend());
  const bool exec = SPOT(s) / high > THRESHOLD(p);
  return result(name, exec);
}

result random_decision(series s, param p) {
  static_cast<void>(s);
  const auto name = NAME("f5f5f5f5f5...", p);
  std::default_random_engine generator;
  std::uniform_real_distribution<double> distribution(0.0, p);
  const double dice_roll = distribution(generator);
  const bool exec = dice_roll < 1.0;
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
  vector<double> subset(s.crbegin(), next(s.crend(), mid_point));
  return AVERAGE(subset);
}

// Average of the oldest half of the series
double DISTANT_AVERAGE(series s) {
  const unsigned long mid_point = s.size() / 2;
  vector<double> subset(s.cbegin(), next(s.cend(), mid_point));
  return AVERAGE(subset);
}

string NAME(const string n, param p) {
  return to_string(p).substr(0, 4) + "_" + n;
}

double THRESHOLD(param p) { return (100.0 + p) / 100.0; }

double SPOT(series s) { return s.back(); }

// Entry point into the library, returns a list of the strategy names that
// reported "buy" for the prices given
vector<string> run_strategies(series s) {

  using library = const vector<std::function<result(series, param)>>;

  // Strategies that take thresholds (in percent)
  const vector<double> thresholds{10.0};
  library lib1{flicking_down, flicking_up,     ski_jumping,
               stepping_up,   stepping_down,   steady_rising,
               kosovich,      rolling_average, random_decision};

  vector<string> trades;
  for (const auto &buy : lib1)
    for (const auto &t : thresholds) {
      const auto b = buy(s, t);

      if (b.second)
        trades.push_back(b.first);
    }

  // Strategies that take ratios
  const vector<double> ratios{2.0};
  library lib2{average_compare, average_inter};

  for (const auto &buy : lib2)
    for (const auto &t : ratios) {
      const auto b = buy(s, t);

      if (b.second)
        trades.push_back(b.first);
    }

  return trades;
}

#include <iostream>
#include <sstream>
int main() {

  // Get some example prices
  const auto prices = get_prices();

  // A place for the results
  std::stringstream results;
  results.precision(10);

  // Test strategies on each series
  for (const auto &p : prices) {

    const auto &name = p.first;
    const auto &series = p.second;
    const auto spot = series.back();

    const auto buys = run_strategies(series);
    if (!buys.empty()) {
      results << name << "\t" << spot << " ";
      for (const auto &buy : buys)
        results << buy << " ";
      results << "\n";
    }
  }

  std::cout << results.str();
}
