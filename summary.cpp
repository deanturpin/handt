#include <map>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "position.h"

auto get_positions(const std::string file) {

  std::vector<trade_position> positions;

  std::ifstream in(file);
  if (in.good()) {
    trade_position p;
    while (in >> p)
      positions.push_back(p);
  }

  return positions;
}

int main() {

  // Get the buys
  auto positions = get_positions("buys.csv");

  // Append the sells
  auto sells = get_positions("sells.csv");
  positions.insert(std::end(positions), std::begin(sells), std::end(sells));

  // Sum the sell prices
  std::map<std::string, double> coins;
  double in, out;
  for (const auto &p : positions) {
    coins[p.name] += p.sell_price;

    // Each position implies an investment
    in += 100;

    // Sum of all the investments
    out += p.yield;
  }

  std::cout << in << " in\n";
  std::cout << out << " out\n";
  std::cout << 100.0 * out / in << " %\n";
}
