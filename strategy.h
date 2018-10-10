#ifndef STRATEGY_H
#define STRATEGY_H

#include "low_frequency_trader.h"
#include <cmath>
#include <string>
#include <vector>

// Generate strategy permutations: a complete strategy consists of a primary
// and secondary strategy and a buy threshold

struct strategy_t {
  std::string name;
  func1 primary;
  func2 secondary;
  int threshold;
  using iter = const std::vector<double>::const_iterator &;
  bool execute(iter historic_price_index, iter current_price_index) const {

    // Calculate the buy ratio
    const double ratio = (100.0 + threshold) / 100.0;

    // Test the strategies
    const auto primary_response =
        primary({historic_price_index, current_price_index});
    const auto secondary_response =
        secondary({historic_price_index, current_price_index});

    // Check we haven't ended up with a huge number (or NaN) by inadvertantly
    // dividing a double with a very similar double (or zero), and then
    // return strategy success
    return !std::isinf(secondary_response) && !std::isnan(primary_response) &&
           primary_response && secondary_response > ratio;
  }
};

std::vector<strategy_t> get_strategies();

#endif
