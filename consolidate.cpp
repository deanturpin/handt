#include "position.h"
#include "utils.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <sstream>
#include <vector>

// A prospect has a name, an initial price and a list of strategies that
// triggered the prospect
struct prospect {
  std::string symbol;
  double spot;
  std::vector<std::string> strategies;

  friend std::istream &operator>>(std::istream &is, prospect &p) {
    is >> p.symbol >> p.spot;
    std::copy(std::istream_iterator<std::string>(is),
              std::istream_iterator<std::string>(),
              std::back_inserter(p.strategies));
    return is;
  }
};

int main() {

  // Debug config
  std::stringstream out;
  out.precision(10);
  out << std::boolalpha;

  // Process prospects
  std::ifstream in("prospects.csv");
  std::vector<prospect> prospects;
  if (in.good()) {
    std::string line;
    while (getline(in, line)) {
      std::stringstream ss(line);
      prospect p;
      ss >> p;
      prospects.push_back(p);
    }
  }

  // Get current refreshed positions
  const auto refresh = get_positions("refresh.csv");

  // Create postion for each propsect
  std::decay_t<decltype(refresh)> positions;
  for (const auto prospect : prospects) {
    for (const auto strategy : prospect.strategies) {

      // Check if we already hold a position with this currency/strategy
      const auto symbol = prospect.symbol;
      const auto it = std::find_if(
          refresh.cbegin(), refresh.cend(), [&symbol, &strategy](const auto p) {
            return p.name == symbol && p.strategy == strategy;
          });

      // Create a position if we don't already hold one
      if (it == refresh.cend()) {
        // Initialise position with prospect details
        lft::position position;
        position.name = prospect.symbol;
        position.strategy = strategy;
        position.buy_price = position.sell_price = prospect.spot;
        positions.push_back(position);
      }
    }
  }

  for (const auto p : {refresh, positions})
    for (const auto q : p)
      out << q << "\n";

  std::cout << out.str();
}
