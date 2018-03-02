#ifndef UTILS
#define UTILS

#include "position.h"
#include <fstream>
#include <iomanip>
#include <iterator>
#include <map>
#include <sstream>
#include <vector>

// Get positions from a file
auto get_positions(const std::string file = "positions.csv") {
  std::vector<lft::position> positions;
  std::ifstream in(file);
  if (in.good()) {
    lft::position p;
    while (in >> p)
      positions.push_back(p);
  }

  return positions;
}

// Get prices and return a container full of them
std::map<std::string, std::vector<double>>
get_prices(const std::string file = "prices.csv") {
  std::map<std::string, std::vector<double>> prices;

  // Read some prices
  std::ifstream in(file);
  if (in.good()) {

    // The first item is the coin name
    std::string coin;
    while (in >> coin) {

      // The remainder of the line contains values
      std::string line;
      std::getline(in, line);
      std::stringstream ss(line);

      // Extract values and add to the map
      std::vector<double> p;
      copy(std::istream_iterator<double>(ss), std::istream_iterator<double>(),
           std::back_inserter(p));

      prices.insert(std::make_pair(coin, p));
    }
  }

  return prices;
}

#endif
