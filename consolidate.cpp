#include "position.h"
#include <fstream>
#include <iostream>
#include <iterator>
#include <sstream>
#include <vector>

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

  friend std::ostream &operator<<(std::ostream &os, prospect &p) {
    os << p.name << p.spot;

    std::copy(p.strategies.cbegin(), p.strategies.cend(),
              std::ostream_iterator<std::string>(os, " "));

    return os;
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

  out << prospects.size() << " prospects\n";
  for (const auto p : prospects)
    out << p.name << "\n";

  // Create postion for each propsect


  // Get current positions (not necessarily for all prices)
  // const auto positions = get_positions("refresh.csv");

  // out << positions.size() << " reviewed positions\n";

  // Close any positions
  // for (auto p : positions)
  //   if (p.sell_price / p.buy_price > 1.1)
  //     p.open = false;

  // for (const auto p : positions)
  //   out << p;

  std::cout << out.str();
}
