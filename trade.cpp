#include "position.h"
#include "strategy.h"
#include "utils.h"
#include <algorithm>
#include <fstream>
#include <vector>

// Let's trade
int main() {

  // Get some recent prices
  auto prices = get_prices();

  std::cout << prices.size() << " prices read\n";

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
  for (const auto &p : positions)
    if (strat.sell(p.buy_price, p.sell_price))
      sells.push_back(p);
    else
      buys.push_back(p);

  std::cout << positions.size() << " positions read\n";

  // Consolidate existing and new positions
  for (const auto &coin : prices) {

    const std::string name = coin.first;
    const double spot = coin.second.back();
    const auto series = coin.second;

    // Do we already hold a position on this currency?
    auto it = std::find_if(positions.begin(), positions.end(),
                           [&name](const auto &p) { return p.name == name; });

    // If we don't hold a position in this currency then create one for
    // consideration
    if (it == positions.end())
      if (strat.buy(series)) {
        struct position pos;
        pos.name = name;
        pos.buy_price = spot;
        pos.sell_price = spot;
        pos.buy_time = timestamp();
        pos.strategy = strat.name;
        pos.yield = 100.0 * pos.sell_price / pos.buy_price;

        positions.push_back(pos);
        std::cout << name << " buy@ " << spot << "\n";
      }
  }

  // Trading session is complete, write out buys and sells
  std::ofstream out(buy_file);
  for (const auto &p : buys)
    out << p;
  out.close();

  std::cout << buys.size() << " buys written\n";

  out.open("sells.csv");
  for (const auto &p : sells)
    out << p;

  std::cout << sells.size() << " sells written\n";
}
