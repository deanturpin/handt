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

  std::string name{"turbo_20"};

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
        if (buy(series))
          return false;

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
    auto s1 = strategy();
    strategies.push_back(s1);

    {
      // Init
      auto jk = s1;
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
        // Otherwise check if we're happy with the return
        const auto sell_price = series.back();
        return sell_price / buy_price > 1.1;
      };

      strategies.push_back(jk);
    }
  }

  // Get some recent prices
  auto prices = get_prices();

  // Read in current positions
  std::vector<position> positions;
  const std::string buy_file = "buys.csv";
  std::ifstream in(buy_file);
  if (in.good()) {
    position p;
    while (in >> p)
      positions.emplace_back(p);
  }

  // Create containers to hold the results
  std::vector<position> buys, sells;

  // Review all open positions
  for (const auto &p : positions) {

    // Create a copy of the position
    auto _p = p;

    // Try to find some prices for this currency
    auto it =
        std::find_if(prices.begin(), prices.end(),
                     [&_p](const auto &coin) { return coin.first == _p.name; });

    if (it != prices.end()) {
      // Update position with latest info
      _p.sell_price = it->second.back();
      _p.sell_time = timestamp();
      _p.yield = 100.0 * _p.sell_price / _p.buy_price;

      // Find the strategy for this position
      auto strat_it =
          find_if(strategies.cbegin(), strategies.cend(),
                  [&_p](const auto &str) { return _p.strategy == str.name; });

      // Found strategy, review position
      if (strat_it != strategies.cend()) {

        // Check if it's good to sell, otherwise push it back onto the buy list
        if (strat_it->sell(it->second, _p.buy_price))
          sells.push_back(_p);
        else
          buys.push_back(_p);

        // std::cout << strat_it->name << " strat found\n";
      }

      // No strategy
      else {
        // std::cout << _p.strategy << " strat not found\n";
        _p.notes = "undefxx";
        buys.push_back(_p);
      }
    } else {
      // _p.sell_price = -1;
      _p.notes = "noprices";
      buys.push_back(_p);
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
          struct position pos;
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

  // Trading session is complete, write out buys
  std::ofstream out(buy_file);
  std::sort(buys.begin(), buys.end(), [](const auto &a, const auto &b){
              return a.yield < b.yield;
            });
  for (const auto &p : buys)
    out << p;
  out.close();

  // Append sells lest we forget
  out.open("sells.csv", std::ios::app);
  for (const auto &p : sells)
    out << p;
}
