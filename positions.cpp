#include "position.h"
#include "strategy.h"
#include "utils.h"
#include <algorithm>
#include <fstream>
#include <map>
#include <numeric>
#include <sstream>
#include <vector>

// Let's trade
int main() {

  // Get some recent prices
  auto prices = get_prices();

  std::cout << prices.size() << " prices read\n";

  // Create a strategy
  always strat;

  // Read in current buys
  std::vector<position> positions;
  const std::string buys = "buys.txt";
  std::ifstream in(buys);
  if (in.good()) {
    position p;
    while (in >> p)
      positions.emplace_back(p);
  }

  std::cout << positions.size() << " positions read\n";

  // TODO
  // Don't go for prices and add positions.
  // Process open positions, and search for prices (mark "noprices" in the sell
  // price if there are none - good if an exchange has gone down)
  // Remove the processed coins and then create new position for whatever's
  // remaining.

  // Consolidate existing and new positions
  for (const auto &coin : prices) {

    const std::string name = coin.first;
    const double spot = coin.second.back();

    // Do we already hold a position on this currency?
    auto it = std::find_if(positions.begin(), positions.end(),
                           [&name](const auto &p) { return p.name == name; });

    // If we don't hold a position then consider creating one
    if (it == positions.end())
      if (strat.buy(coin.second)) {
        struct position pos;
        pos.name = name;
        pos.buy_price = pos.sell_price = std::to_string(spot);
        pos.buy_time = timestamp();
        pos.strategy = strat.name;

        positions.push_back(pos);
        std::cout << name << " buy@ " << spot << "\n";
      }
  }

  // Consider cashing in each position
  // for (const auto &p : positions)
  //   if (strat.sell(std::stod(p.buy_price), std::stod(p.buy_price)))
  //     std::cout << p.name << " sell@ " << p.sell_price << "\n";

  // Write out buys
  std::ofstream out(buys);
  for (const auto &p : positions)
    out << p;

  std::cout << positions.size() << " positions written\n";
}
