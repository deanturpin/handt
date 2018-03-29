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
  std::string name;
  std::vector<double> series;

  friend std::istream &operator>>(std::istream &is, coin &p) {
    is >> p.name;
    std::copy(std::istream_iterator<double>(is),
              std::istream_iterator<double>(), std::back_inserter(p.series));
    return is;
  }
};

// Generic routine to extract a series of objects from a file and populate a
// container
template <typename T> auto get_objects_from_file(const std::string file) {

  // Declare object to be returned
  std::vector<T> objects;

  // Step through each line extracting the object and pushing onto a container
  std::ifstream in(file);
  std::string line;
  while (getline(in, line)) {

    // Skip lines that start with a comment
    if (line.front() != '#') {

      // Stream object and store it
      std::stringstream ss(line);
      T p;
      ss >> p;
      objects.push_back(p);
    }
  }

  // Return the extracted objects
  return objects;
}

// Wrappers to get various objects
auto get_prospects() {
  return get_objects_from_file<prospect>("prospects.csv");
}
auto get_prices() { return get_objects_from_file<coin>("prices.csv"); }
auto get_positions() {
  return get_objects_from_file<position>("positions.csv");
}
auto get_reviewed_positions() {
  return get_objects_from_file<position>("review.csv");
}
auto get_refreshed_positions() {
  return get_objects_from_file<position>("refresh.csv");
}
auto get_consolidated_positions() {
  return get_objects_from_file<position>("consolidate.csv");
}
}

#endif
