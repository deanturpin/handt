#include <fstream>
#include <istream>
#include <iostream>
#include <iterator>
#include <numeric>
#include <sstream>
#include <vector>
#include "strategy.h"

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

int main() {

  // Read some prices
  std::ifstream in("prices.csv");
  if (in.good()) {

    // The first item is the coin name
    std::string coin;
    while (in >> coin) {

      // The remainder of the line contains values
      std::string line;
      std::getline(in, line);
      std::stringstream ss(line);

      // Extract values into a container
      std::vector<double> prices;
      copy(std::istream_iterator<double>(ss), std::istream_iterator<double>(),
           std::back_inserter(prices));

      // Create a strategy
      snooper_grande s;

      std::cout << coin << "\n";

      const double buy = 0.1;
      const double sell = prices.back();

      // Check if we hold a position
      if (buy > 0.0) {
        if (s.sell(buy, sell))
          std::cout << "sell\n";
      }
      // Otherwise consider buying
      else if (s.buy(prices))
        std::cout << "buy\n";
    }
    }

  // Nothing to do
  else
    std::cout << "no prices\n";
}
