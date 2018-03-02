#include "position.h"
#include "strategy.h"
#include "utils.h"
#include <fstream>
#include <iostream>
#include <map>
#include <numeric>
#include <string>
#include <vector>

int main() {

  // Get the coins
  const auto prices = get_prices();
  std::cout << prices.size() << " coins updated in the last minute\n";

  // Get the positions
  const auto positions = get_positions("consolidate.csv");
  std::cout << positions.size() << " positions\n\n";

  std::map<std::string, std::vector<double>> yield;

  // Close all positions
  for (const auto &position : positions)
    yield[position.strategy].push_back(position.sell_price /
                                       position.buy_price);

  // Individual strategy performance
  std::cout << "STRATEGY\t\tPOS\t% RETURN\n\n";
  for (const auto &i : yield) {
    const std::string strategy = i.first;
    const unsigned long positions = i.second.size();
    const double yield =
        100.0 * std::accumulate(i.second.cbegin(), i.second.cend(), 0.0) /
        positions;

    std::cout << strategy << "\t" << std::fixed << positions << "\t" << yield
              << "\n";
  }
}
