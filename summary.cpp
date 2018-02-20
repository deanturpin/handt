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

  // Get closed positions
  {
    const auto positions = get_positions("buys.csv");
    std::cout << positions.size() << " buys\n";

    // Sum the sell prices
    std::map<std::string, double> coins;
    double in, out;
    for (const auto &p : positions) {
      coins[p.name] += p.sell_price;

      out += p.yield;
      in += 100;
    }

    // std::cout << "gross return\n";
    // for (const auto &c : coins)
      // std::cout << c.first << "\t" << c.second << "\n";
  }


  // Get open positions
  {
    const auto positions = get_positions("sells.csv");
    std::cout << positions.size() << " sells\n";
  }
}
