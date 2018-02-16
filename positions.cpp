#include <fstream>
#include <iomanip>
#include <chrono>
#include <istream>
#include <iostream>
#include <iterator>
#include <numeric>
#include <sstream>
#include <vector>
#include <map>
#include "strategy.h"

std::map<std::string, std::vector<double>> get_prices();

// Struggled for a while how to handle a no position. Zero is the first choice
// but zero also represents a complete fail. Perhaps that also represents a no
// position?
struct position {

  std::string name = "maybe";
  std::string buy_price = "maybe";
  std::string sell_price = "maybe";
  std::string time = "maybe";
  std::string yield = "maybe";

  friend std::ostream& operator<< (std::ostream& os, const position& p) {
    return os
      << p.time << " "
      << p.name << " "
      << p.buy_price << " "
      << p.sell_price << " "
      << p.yield;
  }
};

// Create a timestamp
std::string timestamp();
int main() {

  // Get some recent prices
  auto prices = get_prices();

  // Read current position
  // TODO

  // Create a strategy
  always s;

  std::vector<position> positions;

  // Test strategy on each coin
  for (const auto &coin : prices) {

    const std::string name = coin.first;
    const double spot = coin.second.back();

    std::cout << name << "\n";
    const double position = 100000.1;

    // Do we buy?
    if (s.buy(coin.second)) {
      struct position pos({name, std::to_string(spot), timestamp()});
      positions.push_back(pos);
    }

    // Or do we... sell?
    else if (s.sell(position, spot))
      std::cout << "\tsell\n";

    // Or stay as we are
    else
      std::cout << "\tnothing\n";
  }

  // Write out positions
  std::cout << "POSITIONS\n";
  for (const auto & p : positions)
    std::cout << p << "\n";
}

// Get prices and return a container full of them
std::map<std::string, std::vector<double>> get_prices() {
  std::map<std::string, std::vector<double>> prices;

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
      std::vector<double> p;
      copy(std::istream_iterator<double>(ss), std::istream_iterator<double>(),
           std::back_inserter(p));

      prices.insert(std::make_pair(coin, p));
    }
  }

  return prices;
}

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

std::string timestamp() {
    using namespace std::chrono;
    using clock = std::chrono::system_clock;
    const auto now = clock::now();

    // Create a date string
    const auto in_time_t = clock::to_time_t(now);
    std::stringstream date;
    date << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %X");
    return date.str();
}

