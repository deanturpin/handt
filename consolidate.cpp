#include "position.h"
#include <fstream>
#include <iostream>
#include <iterator>
#include <sstream>
#include <vector>

// A prospect has a name, an initial price and a list of strategies that
// triggered the prospect
struct prospect {
  std::string name;
  double spot;
  std::vector<std::string> strategies;

  friend std::istream &operator>>(std::istream &is, prospect &p) {
    is >> p.name >> p.spot;
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

  // Create postion for each propsect
  for (const auto prospect : prospects) {
    for (const auto strategy : prospect.strategies) {

      // Initialise position with prospect details
      lft::position position;
      position.name = prospect.name;
      position.strategy = strategy;
      position.buy_price = position.sell_price = prospect.spot;

      out << position;
    }
  }

  std::cout << out.str();
}
