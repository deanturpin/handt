#ifndef TRADE_H
#define TRADE_H

#include <string>
#include <vector>

struct trade_t {
  std::string from_symbol;
  std::string to_symbol;
  std::string exchange;
  std::vector<double> prices;

  double mean_variance();
};

std::vector<trade_t> get_trades();

#endif
