#include <fstream>
#include <istream>
#include <iostream>
#include <iterator>
#include <numeric>
#include <sstream>
#include <vector>
#include <map>
#include "strategy.h"

/*
struct trade {
  std::string name = "blah";
  std::string buy_time = "TBD"; //chrono
  std::string sell_time = "TBD";
  double buy = 0.0;
  double sell = 0.0;

  friend std::ostream& operator<<(std::ostream& os, const trade& t) {
    return os
      << t.name << " "
      << t.buy_time << " "
      << t.sell_time << " "
      << t.buy << " "
      << t.sell;
  }
};

struct trade2 {

  std::map<std::string, std::string> stats {
    {"name", "undefined"},
    {"buy_time", "undefined"},
    {"sell_time", "undefined"},
    {"buy", "undefined"},
    {"sell", "undefined"},
  };

  friend std::ostream& operator<<(std::ostream& os, const trade2& t) {

    for (const auto &s : t.stats)
      os << s.second << " ";

    return os;
  }
};
*/

int main() {

  std::map<std::string, std::vector<double>> prices;
  std::ifstream in("prices.csv");

  // Read some prices
  if (in.good()) {

    // The first item is the coin name
    std::string coin;
    while (in >> coin) {

      // The remainder of the line contains values
      std::string line;
      std::getline(in, line);
      std::stringstream ss(line);

      // Extract values into a container
      std::vector<double> p;
      copy(std::istream_iterator<double>(ss), std::istream_iterator<double>(),
           std::back_inserter(p));

      prices.insert(std::make_pair(coin, p));
    }
  }

  // Read current positions

  // Create a strategy
  snooper_grande s;

  // Test strategy on each coin
  for (const auto &coin : prices) {

    std::cout << coin.first << "\n";
    const double position = 100000.1;
    const double spot = coin.second.back();

    // Do we buy?
    if (s.buy(coin.second))
      std::cout << "\tbuy\n";

    // Or do we... sell?
    else if (s.sell(position, spot))
      std::cout << "\tsell\n";

    // Or stay as we are
    else
      std::cout << "\tnothing\n";
  }
}
