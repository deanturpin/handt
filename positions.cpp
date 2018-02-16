#include "strategy.h"
#include <algorithm>
#include <chrono>
#include <fstream>
#include <iomanip>
#include <iterator>
#include <map>
#include <numeric>
#include <sstream>
#include <vector>

// Proto
std::map<std::string, std::vector<double>> get_prices();

// Create a timestamp
std::string timestamp();
int main() {

  // Get some recent prices
  auto prices = get_prices();

  std::cout << prices.size() << " prices read\n";

  // Create a strategy
  always s;

  // Read in current buys
  std::vector<position> positions;
  const std::string buys = "buys.txt";
  std::ifstream in(buys);
  if (in.good()) {
    position p;
    while (in >> p)
      positions.emplace_back(p);
  }

  std::cout << positions.size() << " positions read\n";

  // Test strategy on each coin
  for (const auto &coin : prices) {

    const std::string name = coin.first;
    const double spot = coin.second.back();

    // Do we already hold a position on this currency?
    auto it = std::find_if(positions.cbegin(), positions.cend(),
                           [&name](const auto &p) { return p.name == name; });

    // If not buy?
    if (it == positions.cend())
      if (s.buy(coin.second)) {
        struct position pos({name, std::to_string(spot), timestamp(), s.name});
        positions.push_back(pos);

        // Or do we... sell?
        // else if (s.sell(position, spot))
        // std::cout << "\tsell\n";
      }
  }

  // Write out buys
  std::ofstream out(buys);
  for (const auto &p : positions)
    out << p;

  std::cout << positions.size() << " positions written\n";
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

// Turn right now into a string timestamp
std::string timestamp() {

  // Get now
  using namespace std::chrono;
  using clock = std::chrono::system_clock;
  const auto now = clock::now();

  // Create a date string
  const auto in_time_t = clock::to_time_t(now);
  std::stringstream date;
  date << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d-%X");

  return date.str();
}
