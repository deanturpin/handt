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
  std::vector<trade_position> buys, sells;

  const std::string buy_file = "buys.csv";
  std::ifstream in(buy_file);
  if (in.good()) {
    trade_position p;
    while (in >> p)
      positions.push_back(p);
  }

  // Review all open positions
  for (auto &p : positions) {

    // Create a copy of the position
    auto &pos = p;

    // Try to find some prices for this currency
    const auto it =
        std::find_if(prices.cbegin(), prices.cend(), [&pos](const auto &coin) {
          return coin.first == pos.name;
        });

    if (it != prices.cend()) {

      pos.notes = "okprices";

      // Update position with latest info
      pos.sell_price = it->second.back();
      pos.duration = timestamp() - pos.timestamp;
      pos.yield = 100.0 * pos.sell_price / pos.buy_price;

      // Find the strategy for this position

      static auto strat_it = strategies.cbegin();
      find_if(strategies.cbegin(), strategies.cend(),
              [&pos](const auto &s) { return pos.strategy == s->name(); });

      // Found strategy, review position
      if (strat_it != strategies.cend()) {
        const auto &series = it->second;

        // Check if it's good to sell, otherwise push it back onto the buy list
        (*strat_it)->sell(series, pos.buy_price) ? sells.push_back(pos)
                                                 : buys.push_back(pos);
      }

      // No strategy
      else {
        pos.notes = "undefine";
        buys.push_back(pos);
      }
    } else {
      pos.notes = "noprices";
      buys.push_back(pos);
    }
  }

  // Consolidate existing position and look for new ones
  for (const auto &coin : prices) {
    for (const auto &strat : strategies) {

      const std::string name = coin.first;
      const double spot = coin.second.back();
      const auto series = coin.second;

      // Check if we already hold a position on this currency with the current
      // strategy
      const auto it = std::find_if(
          positions.cbegin(), positions.cend(), [&name, &strat](const auto &p) {
            return p.name == name && p.strategy == strat->name();
          });

      // Check we don't already hold a position in this currency, if not
      // consider creating one
      if (it == positions.cend()) {
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

          buys.push_back(pos);
        }
      }
    }
  }

  // Trading session is complete, write out current positions sorted by yield
  std::ofstream out(buy_file);
  std::sort(buys.begin(), buys.end(),
            [](const auto &a, const auto &b) { return a.yield < b.yield; });

  for (const auto &p : buys)
    out << p;
  out.close();

  // And append our successes
  out.open("sells.csv", std::ios::app);
  for (const auto &p : sells)
    out << p;
}
