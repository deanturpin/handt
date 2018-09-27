#ifndef REPORT_H
#define REPORT_H

#include <list>
#include <string>

// Structure to capture the results during a strategy backtest
struct strategy_performance {
  std::string name;
  std::string from_symbol;
  std::string to_symbol;
  std::string exchange;
  double spot = 0.0;
  unsigned int good_deals = 0;
  unsigned int bad_deals = 0;
  unsigned int opportunities = 0;
  bool buy = false;
};

static_assert(std::is_standard_layout<strategy_performance>::value);
void report_performance(const std::list<strategy_performance> &);

#endif
