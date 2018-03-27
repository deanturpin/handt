#ifndef LFT_POSITION
#define LFT_POSITION

#include <chrono>
#include <fstream>
#include <iomanip>
#include <istream>
#include <iterator>
#include <map>
#include <ostream>
#include <string>
#include <vector>

namespace handt {

unsigned long seconds_since_epoch() {

  using namespace std::chrono;
  using clock = std::chrono::system_clock;
  const auto now = clock::now();
  const auto epoch = static_cast<unsigned long>(
      duration_cast<seconds>(now.time_since_epoch()).count());

  return epoch;
}

// A stucture to represent a trade
struct position {

  std::string symbol = "sym";
  unsigned long timestamp = seconds_since_epoch();
  double buy_price = 0.0;
  double sell_price = 0.0;
  std::string strategy = "strategy";
  std::string notes = "NEWTRADE";
  bool open = true;

  // Streaming out
  friend std::ostream &operator<<(std::ostream &os, const position &p) {
    os.precision(10);
    return os << std::fixed << p.symbol << "\t" << p.strategy << "\t" << p.notes
              << " " << p.buy_price << " " << p.sell_price << " " << p.timestamp
              << " " << std::boolalpha << p.open;
  }

  // Streaming in
  friend std::istream &operator>>(std::istream &is, position &p) {
    return is >> p.symbol >> p.strategy >> p.notes >> p.buy_price >>
           p.sell_price >> p.timestamp >> std::boolalpha >> p.open;
  }
};

// Strip comments and return the remainder of the file
std::stringstream strip_comments(const std::string &file) {
  std::ifstream in(file);
  std::stringstream ss;
  if (in.good())
    ss << in.rdbuf();
  return ss;
}

// Get positions from a file
auto get_positions(const std::string file = "positions.csv") {

  std::vector<position> positions;
  position p;
  auto in = strip_comments(file);
  while (in >> p)
    positions.push_back(p);

  return positions;
}

// Get prices and return a container full of them
std::map<std::string, std::vector<double>>
get_prices(const std::string file = "prices.csv") {

  // Read some prices
  auto in = strip_comments(file);

  // The first item is the coin name
  std::string coin;
  std::map<std::string, std::vector<double>> prices;
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

  return prices;
}
}

#endif
