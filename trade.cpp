#include "position.h"
#include "utils.h"
#include <algorithm>
#include <fstream>
#include <functional>
#include <iostream>
#include <istream>
#include <numeric>
#include <string>
#include <vector>

struct strategy {

  std::string name = "turbo_20";

  // BUY
  std::function<bool(const std::vector<double> &p)> buy = [&](const auto &p) {
    const double spot = p.back();
    const double average =
        std::accumulate(p.cbegin(), p.cend(), 0.0,
                        [](auto &sum, auto &i) { return sum + i; }) /
        p.size();
    return average / spot > 1.2;
  };

  // SELL
  std::function<bool(const std::vector<double> &series,
                     const double &buy_price)>
      sell = [&](const auto &series, const auto &buy_price) {

        // If there's still a buy on then hang on
        // if (buy(series))
          // return false;

        // Otherwise check if we're happy with the return
        const auto sell_price = series.back();
        return sell_price / buy_price > 1.1;
      };
};

// Let's trade
int main() {

  std::vector<strategy> strategies;
  {
    // Original and best
    strategy s1;
    strategies.push_back(s1);

    {
      // Init
      strategy jk;
      jk.name = "jkrise10";

      // Buy
      jk.buy = [&](const auto &p) {
        const double spot = p.back();
        const double average =
          std::accumulate(p.cbegin(), p.cend(), 0.0,
                          [](auto &sum, auto &i) { return sum + i; }) /
          p.size();
        return spot / average > 1.1;
      };

      // Sell
      jk.sell = [&](const auto &series, const auto &buy_price) {
        return series.back() / buy_price > 1.1;
      };

      strategies.push_back(jk);
    }
  }

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
  for (auto &p: positions) {

    // Create a copy of the position
    auto &pos = p;

    // Try to find some prices for this currency
    auto it =
        std::find_if(prices.begin(), prices.end(), [&pos](const auto &coin)
                     { return coin.first == pos.name; });

    if (it != prices.end()) {

      pos.notes = "okprices";

      // Update position with latest info
      pos.sell_price = it->second.back();
      pos.sell_time = timestamp();
      pos.yield = 100.0 * pos.sell_price / pos.buy_price;

      // Find the strategy for this position

      static auto strat_it = strategies.cbegin();
      find_if(strategies.cbegin(), strategies.cend(),
                              [&pos](const auto &s) {
                              return pos.strategy == s.name;
                              });

      // Found strategy, review position
      if (strat_it != strategies.cend()) {
        const auto &series = it->second;

        // Check if it's good to sell, otherwise push it back onto the buy list
        strat_it->sell(series, pos.buy_price) ?
          sells.push_back(pos) : buys.push_back(pos);
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
      auto it = std::find_if(
        positions.begin(), positions.end(), [&name, &strat](const auto &p) {
        return p.name == name && p.strategy == strat.name;
        });

      // Check we don't already hold a position in this currency, if not
      // consider creating one
      if (it == positions.end()) {
        if (strat.buy(series)) {
          trade_position pos;
          pos.name = name;

          // Initialise buy and sell to same price
          pos.buy_price = pos.sell_price = spot;

          pos.strategy = strat.name;
          pos.yield = 100.0 * pos.sell_price / pos.buy_price;

          // Initialise timestamps to the same time, sell will be updated each
          // time it is reviewed
          pos.buy_time = pos.sell_time = timestamp();

          buys.push_back(pos);
        }
      }
    }
  }

  // Trading session is complete, write out current positions sorted by yield
  std::ofstream out(buy_file);
  std::sort(buys.begin(), buys.end(), [](const auto &a, const auto &b){
              return a.yield < b.yield;
            });

  for (const auto &p : buys) out << p;
  out.close();

  // And append our successes
  out.open("sells.csv", std::ios::app);
  for (const auto &p : sells) out << p;
}
