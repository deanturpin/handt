#include "utils.h"
#include <iostream>
#include <map>
#include <numeric>
#include <string>
#include <vector>

int main() {

  // Configure debug
  std::stringstream out;
  out.precision(10);
  out << std::boolalpha;
  out << std::fixed;

  // Get the coins
  const auto prices = get_prices();
  out << prices.size() << " coins updated in the last minute\n";

  // Get the positions
  const auto positions = get_positions("consolidate.csv");
  out << positions.size() << " positions\n\n";

  std::map<std::string, std::vector<double>> strategies;

  // Close all positions
  for (const auto &position : positions)
    strategies[position.strategy].push_back(position.sell_price /
                                       position.buy_price);

  // Individual strategy performance
  out << "STRATEGY\t\t POS\t% RETURN\n\n";
  for (const auto &i : strategies) {
    const std::string strategy = i.first;
    const unsigned long count = i.second.size();
    const double yield =
        100.0 * std::accumulate(i.second.cbegin(), i.second.cend(), 0.0) /
        count;

    out << strategy << "\t" << std::setw(4) << count << "\t" << yield
              << "\n";
  }

  std::cout << out.str();
}
