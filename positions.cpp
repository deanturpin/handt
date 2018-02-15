#include <fstream>
#include <iostream>
#include <iterator>
#include <numeric>
#include <sstream>
#include <vector>
// #include "strategy.h"

// struct strategy {
//   const std::string name = "always";
//   const double threshold = 1.1;
//   bool buy() const { return true; }
//   bool sell() const { return true; }
// };

// struct never : strategy {
//   const std::string name = "never";
//   bool buy(const std::vector<double> &p) { return false; }
//   bool sell(const double &a, const double &b) { return false; }
// };
//
// struct neversell : strategy {
//   const std::string name = "neversell";
//   bool sell(const double &a, const double &b) { return false; }
// };
//
// struct random : strategy {
//   const std::string name = "random";
//   bool buy(const std::vector<double> &p) { return false; }
//   bool sell(const double &a, const double &b) { return false; }
// };

// SNOOPER
// Trigger when spot is 10% below average for the period
// Don't track to bottom (could fall to zero)
// Sell when spot is 10% above lowest price
struct strategy {
  // strategy(){}
  const std::string name = "snooper";
  const double threshold = 1.1;
  bool buy(const std::vector<double> &p) const {
    const double spot = p.back();
    const double average =
        std::accumulate(p.cbegin(), p.cend(), 0.0,
                        [](auto &sum, auto &i) { return sum + i; }) /
        p.size();
    return average / spot > threshold;
  }

  bool sell(const double &spot, const double &position) const {
    return spot / position > threshold;
  }
};

// SNOOPER GRANDE
// Like SNOOPER but 15%
struct snooper_grande : strategy {
  const std::string name = "snooper_grande";
  const double threshold = 1.15;
};

// SNOOPER PEQUENO
// Like SNOOPER but 5%
struct snooper_pequeno : strategy {
  const std::string name = "snooper_pequeno";
  const double threshold = 1.15;
};

int main() {

  // Create some strategies
  snooper_grande s1;
  const std::vector<struct strategy> strategies = {s1};

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

      auto &s = strategies.front();
      std::cout << coin << " " << prices.size() << " " << s.name << " " <<
        s.threshold << "\n" << "buy\t" << std::boolalpha << s.buy(prices) <<
        "\n" << "sell\t" << std::boolalpha << s.sell(9000, 10000.0) << "\n";
      }
    }

  // Nothing to do
  else
    std::cout << "no prices\n";
}
