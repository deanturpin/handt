#include "utils.h"
#include "position.h"
#include <algorithm>
#include <fstream>
#include <vector>
#include <functional>
#include <iostream>
#include <istream>
#include <numeric>
#include <string>
#include <functional>
#include <vector>

struct strategy {
  std::string name {"dive10"};
  double threshold {1.1};

  // BUY
  std::function<bool(const std::vector<double> &p)>
    buy = [&](const auto &p){
    const double spot = p.back();
    const double average =
        std::accumulate(p.cbegin(), p.cend(), 0.0,
                        [](auto &sum, auto &i) { return sum + i; }) /
        p.size();
    return average / spot > threshold;
    };

  // SELL
  std::function<bool(const std::vector<double> &series, const double &buy_price)>
    sell = [&](const auto &series, const auto &buy_price)
         {

           // if (buy(series))
             // return false;

           const auto sell_price = series.back();
           return sell_price / buy_price > threshold;
         };
};

// Let's trade
int main() {

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

  // Create some containers to hold the results
  std::vector<position> buys, sells;

  // Create a strategy
  strategy strat;

  // Review all open positions
  for (const auto &p : positions) {

    // Create a copy of the position
    auto _p = p;

    // Try to find some prices for this currency
    auto it =
        std::find_if(prices.begin(), prices.end(),
                     [&_p](const auto &coin) { return coin.first == _p.name; });

    if (it != prices.end()) {

      const auto &series = it->second;

      // Update position with latest info
      _p.sell_price = it->second.back();
      _p.sell_time = timestamp();
      _p.yield = 100.0 * _p.sell_price / _p.buy_price;

      // Check if it's good to sell, otherwise push it back onto the buy list
      if (strat.sell(series, _p.buy_price))
        sells.push_back(_p);
      else
        buys.push_back(_p);
    } else {
      _p.sell_price = -1;
      buys.push_back(_p);
    }
  }

  // Consolidate existing and new positions
  for (const auto &coin : prices) {

    const std::string name = coin.first;
    const double spot = coin.second.back();
    const auto series = coin.second;

    // Do we already hold a position on this currency?
    auto it = std::find_if(positions.begin(), positions.end(),
                           [&name](const auto &p) { return p.name == name; });

    // Check we don't already hold a position in this currency
    if (it == positions.end())

      // If not consider creating one
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

  // Trading session is complete, write out buys
  std::ofstream out(buy_file);
  for (const auto &p : buys)
    out << p;
  out.close();

  // Append sells lest we forget
  out.open("sells.csv", std::ios::app);
  for (const auto &p : sells)
    out << p;
}
