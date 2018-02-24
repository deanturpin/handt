#include "position.h"
#include "strategy.h"
#include "utils.h"
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
  auto prices = get_prices();

  // Containers for initial and ultimate positions
  std::vector<trade_position> positions;

  const std::string buy_file = "positions.csv";
  std::ifstream in(buy_file);
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
      const auto it =
          std::find_if(prices.cbegin(), prices.cend(), [&pos](const auto &coin) {
            return coin.first == pos.name;
          });

      if (it != prices.cend()) {

        pos.notes = "ok_price";

        // Update position with latest info
        pos.sell_price = it->second.back();
        pos.duration = timestamp() - pos.timestamp;
        pos.yield = 100.0 * pos.sell_price / pos.buy_price;

        // Find the strategy for this position
        const auto strat_it = strategies.cbegin();
        find_if(strategies.cbegin(), strategies.cend(),
                [&pos](const auto &s) { return pos.strategy == s->name(); });

        // Review position if we've found the strategy
        if (strat_it != strategies.cend()) {
          // Check if it's good to sell, otherwise push it back onto the buy list
          const auto &series = it->second;
          if((*strat_it)->sell(series, pos.buy_price))
            pos.open = false;
        }
        else
          pos.notes = "no_strat";

      // Couldn't find any prices for this coin
      } else
        pos.notes = "noupdate";

    } else
        pos.notes = "isclosed";
  }

  // Look for new positions
  for (const auto &coin : prices) {
    for (const auto &strat : strategies) {

      const std::string name = coin.first;
      const double spot = coin.second.back();
      const auto series = coin.second;

      // Check if we already hold a position with the current strategy
      static auto it = std::find_if(
          positions.cbegin(), positions.cend(), [&name, &strat](const auto &p) {
            return p.name == name && p.strategy == strat->name();
          });

      // If not consider creating one
      if (it == positions.cend())
        if (strat->buy(series)) {
          trade_position pos;
          pos.name = name;

          // Initialise buy and sell to same price
          pos.buy_price = pos.sell_price = spot;

          pos.strategy = strat->name();
          pos.yield = 100.0 * pos.sell_price / pos.buy_price;

          // Initialise timestamps to the same time, sell will be updated each
          // time it is reviewed
          pos.timestamp = timestamp();
          pos.duration = 1;
          pos.open = true;

          positions.push_back(pos);
        }
    }
  }

  // Trading session is complete, write out current positions sorted by yield
  std::ofstream out(buy_file);
  std::sort(positions.begin(), positions.end(),
            [](const auto &a, const auto &b) { return a.yield > b.yield; });

  for (const auto &p : positions)
    out << p;
  out.close();
}
