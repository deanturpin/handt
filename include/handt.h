#ifndef HANDT_H
#define HANDT_H

#include <chrono>
#include <fstream>
#include <iomanip>
#include <istream>
#include <iterator>
#include <map>
#include <ostream>
#include <sstream>
#include <string>
#include <vector>

namespace handt {

const double sell_threshold = 1.08;
const double cut_losses_threshold = 0.70;

// Timestamp when a position is opened
unsigned long get_timestamp() {
  return static_cast<unsigned long>(
      std::chrono::duration_cast<std::chrono::seconds>(
          std::chrono::system_clock::now().time_since_epoch())
          .count());
}

// A stucture to represent a trade
struct position {

  // Initialise position
  std::string symbol = "sym";
  unsigned long timestamp = get_timestamp();
  double buy_price = 0.0;
  double sell_price = 0.0;
  std::string strategy = "strategy";
  std::string status = "NEWTRADE";
  bool open = true;

  // Streaming in
  friend std::istream &operator>>(std::istream &is, position &p) {
    return is >> p.symbol >> p.strategy >> p.status >> p.buy_price >>
           p.sell_price >> p.timestamp >> std::boolalpha >> p.open;
  }

  // Streaming out
  friend std::ostream &operator<<(std::ostream &os, const position &p) {
    os.precision(10);
    return os << std::fixed << p.symbol << '\t' << p.strategy << '\t'
              << p.status << ' ' << p.buy_price << ' ' << p.sell_price << ' '
              << p.timestamp << ' ' << std::boolalpha << p.open;
  }

  double yield() const {
    return buy_price > 0.0 ? sell_price / buy_price : 0.0;
  }
};

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

// A coin has a name and a series of prices
struct coin {
  std::string symbol;
  std::vector<double> series;

  friend std::istream &operator>>(std::istream &is, coin &p) {
    is >> p.symbol;
    std::copy(std::istream_iterator<double>(is),
              std::istream_iterator<double>(), std::back_inserter(p.series));
    return is;
  }
};

// Generic routine to extract a series of objects from a file and populate a
// container
template <typename Object> auto get_objects(const std::string file) {

  // Declare object to be returned
  std::vector<Object> objects;

  // Step through each line extracting the object and pushing onto a container,
  // unless the line starts with a comment character then skip it
  std::ifstream in(file);
  std::string line;
  while (getline(in, line))
    if (line.front() != '#') {
      std::stringstream ss(line);
      Object p;
      ss >> p;
      objects.push_back(p);
    }

  // Return the extracted objects
  return objects;
}

// Wrappers to parse files and return containers of various objects
auto get_prices() { return get_objects<coin>("prices.csv"); }
auto get_prospects() { return get_objects<prospect>("prospects.csv"); }
auto get_positions() { return get_objects<position>("positions.csv"); }
auto get_purged_positions() { return get_objects<position>("purge.csv"); }
auto get_closed_positions() { return get_objects<position>("closed.csv"); }
auto get_reviewed_positions() { return get_objects<position>("review.csv"); }
auto get_refreshed_positions() { return get_objects<position>("refresh.csv"); }
auto get_final_positions() { return get_objects<position>("consolidate.csv"); }
auto get_symbols() { return get_objects<std::string>("symbols.csv"); }

const std::string stats_file = "stats.txt";
auto get_stats() {
  const auto stats = get_objects<unsigned long>(stats_file);
  return stats.size() ? stats.front() : 0;
}

auto put_stats(const unsigned long &stat) {
  std::ofstream out(stats_file);
  if (out.good())
    out << stat;
}
}

#endif
