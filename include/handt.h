#ifndef HANDT_H
#define HANDT_H

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

  // Initialise position
  std::string symbol = "sym";
  unsigned long timestamp = seconds_since_epoch();
  double buy_price = 0.0;
  double sell_price = 0.0;
  std::string strategy = "strategy";
  std::string notes = "NEWTRADE";
  bool open = true;

  // Streaming in
  friend std::istream &operator>>(std::istream &is, position &p) {
    return is >> p.symbol >> p.strategy >> p.notes >> p.buy_price >>
           p.sell_price >> p.timestamp >> std::boolalpha >> p.open;
  }

  // Streaming out
  friend std::ostream &operator<<(std::ostream &os, const position &p) {
    os.precision(10);
    return os << std::fixed << p.symbol << "\t" << p.strategy << "\t" << p.notes
              << " " << p.buy_price << " " << p.sell_price << " " << p.timestamp
              << " " << std::boolalpha << p.open;
  }
};

// Strip comments and return the remainder of the file
std::stringstream strip_comments(const std::string &file) {

  std::ifstream in(file);
  std::stringstream ss;

  std::string line;
  if (in.good())
    while (getline(in, line))
      if (!line.empty())
        if (line.front() != '#')
          ss << line << '\n';

  return ss;
}

// Get positions from disk
auto get_positions_from_file(const std::string file) {

  // Declare object that will be returned
  std::vector<position> positions;

  // Process all lines that match a position structure
  position p;
  auto in = strip_comments(file);
  while (in >> p)
    positions.push_back(p);

  return positions;
}

// Helper routines to colocate the external filenames
auto get_positions() { return get_positions_from_file("positions.csv"); }
auto get_reviewed_positions() { return get_positions_from_file("review.csv"); }
auto get_refreshed_positions() {
  return get_positions_from_file("refresh.csv");
}
auto get_consolidated_positions() {
  return get_positions_from_file("consolidate.csv");
}

// A prospect has a name, an initial price and a list of strategies that
// triggered the prospect
struct prospect {
  std::string symbol;
  double spot;
  std::vector<std::string> strategies;

  friend std::istream &operator>>(std::istream &is, prospect &p) {
    is >> p.symbol >> p.spot;
    std::copy(std::istream_iterator<std::string>(is),
              std::istream_iterator<std::string>(),
              std::back_inserter(p.strategies));
    return is;
  }
};

// Get prospects from disk
auto get_prospects() {

  // Declare object that will be returned
  std::vector<prospect> prospects;

  // Read recent prospects
  std::stringstream in = strip_comments("prospects.csv");
  std::string line;
  while (getline(in, line)) {
    std::stringstream ss(line);
    prospect p;
    ss >> p;
    prospects.push_back(p);
  }

  return prospects;
}

// Get prices from disk
auto get_prices() {

  // Declare object that will be returned
  std::map<std::string, std::vector<double>> prices;

  // Read recent prices
  auto in = strip_comments("prices.csv");

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

    if (!p.empty())
      prices.insert(std::make_pair(coin, p));
  }

  return prices;
}
}

#endif
