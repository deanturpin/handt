#include <fstream>
#include <iostream>
#include <iterator>
#include <numeric>
#include <sstream>
#include <vector>
#include "strategy.h"

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

      std::cout << coin << " " << prices.size() << " " << s.name << " " <<
        s.threshold << "\n" << "buy\t" << std::boolalpha << s.buy(prices) <<
        "\n" << "sell\t" << std::boolalpha << s.sell(9000, 10000.0) << "\n";
      }
    }

  // Nothing to do
  else
    std::cout << "no prices\n";
}
