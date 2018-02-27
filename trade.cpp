#include "position.h"
#include "strategy.h"
#include "utils.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <istream>
#include <iterator>
#include <memory>
#include <numeric>
#include <string>
#include <vector>

// Let's trade
int main() {

  // Get the strategies
  const auto &strategies = lft::strategy_library;

  // Get some recent prices
  const auto prices = get_prices();

  // Read in current positions
  std::vector<trade_position> positions;
  const std::string positions_file = "positions.csv";

  std::ifstream in(positions_file);
  if (in.good()) {
    trade_position p;
    while (in >> p)
      positions.push_back(p);
  }

  // Review all existing positions
  for (auto &pos : positions) {

    // Review all open positions
    if (pos.open) {

      // Try to find some prices for this currency
      const auto it = std::find_if(
          prices.cbegin(), prices.cend(),
          [&pos](const auto &coin) { return coin.first == pos.name; });

      if (it != prices.cend()) {

        // Update position with latest info
        pos.notes = "ok_price";
        pos.sell_price = it->second.back();
        pos.duration = timestamp() - pos.timestamp;
        pos.yield = 100.0 * pos.sell_price / pos.buy_price;

        // Check if it's good to sell
        if (pos.sell_price / pos.buy_price > 1.1) {
          pos.open = false;
          pos.notes = "isclosed";
        }

        // Couldn't find any prices for this coin
      } else
        pos.notes = "noupdate";
    }
  }

  // Look for new positions
  decltype(positions) new_positions;
  for (const auto &coin : prices) {

    const std::string name = coin.first;
    const double spot = coin.second.back();
    const auto series = coin.second;

    // Don't bother looking if there are too few prices
    if (series.size() < 50)
      continue;

    // Don't bother looking if the coin is low value
    if (series.back() < 1.0)
      continue;

    // Assess viability of a trade for each strategy
    for (const auto &buy : strategies) {

      // If the strategy returns positively then check if we already hold a
      // position, repeat for multiple thresholds
      for (const auto &threshold : {1.05, 1.1, 1.2, 1.3, 1.4}) {

        const auto decision = buy(series, threshold);
        const std::string strategy = decision.first;
        const bool execute = decision.second;

        if (execute) {

          // Try to find a matching existing position
          const auto it =
              std::find_if(positions.cbegin(), positions.cend(),
                           [&name, &strategy](const auto &p) {
                             return p.name == name && p.strategy == strategy;
                           });

          // If there isn't one create a position with current price
          if (it == positions.cend()) {

            trade_position pos;
            pos.name = name;
            pos.buy_price = pos.sell_price = spot;
            pos.strategy = strategy;
            pos.yield = 100.0 * pos.sell_price / pos.buy_price;

            // Initialise timestamp, sell price updated each time it is reviewed
            pos.timestamp = timestamp();
            pos.duration = 1;
            pos.open = true;

            new_positions.push_back(pos);
          }
        }
      }
    }
  }

  std::cout << positions.size() << " existing position\n";
  std::cout << new_positions.size() << " new position\n";

  // Append new positions to existing
  std::copy(new_positions.cbegin(), new_positions.cend(),
            std::back_inserter(positions));

  // Trading session is complete, sort all positions prior to storing
  std::sort(positions.begin(), positions.end(),
            [](const auto &a, const auto &b) { return a.yield > b.yield; });

  // Write current positions out
  std::ofstream out(positions_file);
  for (const auto &pos : positions)
    out << pos;
}
