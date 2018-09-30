#ifndef BACKTEST_H
#define BACKTEST_H

#include "perms.h"
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
  std::vector<std::pair<int, int>> good_deals{};
  std::vector<std::pair<int, int>> bad_deals{};
  unsigned int opportunities = 0;
  bool buy = false;
};

std::list<backtest_t> run_backtests(const prices_t &,
                                    const std::vector<strategy_t> &);

#endif
