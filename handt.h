#ifndef HANDT_H
#define HANDT_H

#include "prices.h"
#include <list>

// Structure to capture the results of a strategy backtest run
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

std::list<strategy_performance> have_a_nice_day_trader(const prices_t &pr);

#endif
