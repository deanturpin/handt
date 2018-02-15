#include <iostream>
#include <fstream>
#include "strategy.h"

int main() {

  // Read some prices
  std::ifstream in("prices.csv");
  if (in.good()) {

    // double open, high, low, close;
    // std::vector<double> prices;
    // while (in >> open >> high >> low >> close)
    //   prices.push_back(open);

    std::vector<double> prices = {1, 2, 3,4 ,5 ,6, 6};
    // Create a strategy
    lft::snooper strategy(prices);

    // And test it
    std::cout << strategy.name << " strategy\n";
    std::cout << "buy\t" << std::boolalpha << strategy.buy() << "\n";
    std::cout << "sell\t" << std::boolalpha << strategy.sell(10000.0) << "\n";
  }

  // Nothing to do
  else
    std::cout << "no prices\n";
}
