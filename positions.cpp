#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <iterator>
#include "strategy.h"

int main() {

  // Price file structure is one currency per line, a coin name followed by a
  // series of values
  // coin1 1 2 3 3 4 5 6
  // coin2 2 3 3

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
    lft::snooper strategy(prices);

    // And test it
    std::cout << coin << " " << strategy.name << "\n";
    std::cout << "buy\t" << std::boolalpha << strategy.buy() << "\n";
    std::cout << "sell\t" << std::boolalpha << strategy.sell(10000.0) << "\n";
  }
  }

  // Nothing to do
  else
    std::cout << "no prices\n";
}
