#ifndef PRICES_H
#define PRICES_H

#include <string>
#include <vector>

struct trade_t {
  std::string from_symbol;
  std::string to_symbol;
  std::string exchange;
  std::vector<double> prices;
};

std::vector<trade_t> get_prices();

#endif
