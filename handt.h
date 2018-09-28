#ifndef HANDT_H
#define HANDT_H

#include "prices.h"
#include <list>
#include <string>

// Structure to capture the results of a strategy backtest run
struct backtest_t {
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

std::list<backtest_t> have_a_nice_day_trader(const prices_t &pr);

#endif
