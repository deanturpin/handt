#ifndef BACKTEST_H
#define BACKTEST_H

#include "perms.h"
#include "trade.h"
#include <string>
#include <vector>

// Structure to capture the results of a strategy backtest run
struct backtest_t {
  std::string name;
  std::string from_symbol;
  std::string to_symbol;
  std::string exchange;
  double spot = 0.0;
  strategy_t strategy{};
  // const std::vector<double> &prices;

  std::vector<std::pair<int, int>> good_deals{};
  std::vector<std::pair<int, int>> bad_deals{};
  unsigned int opportunities = 0;
  bool buy = false;
};

std::vector<backtest_t> run_backtests(const std::vector<trade_t> &,
                                      const std::vector<strategy_t> &);

// static_assert(std::is_standard_layout<backtest_t>::value);

#endif
