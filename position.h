#ifndef POSITION
#define POSITION

#include <istream>
#include <ostream>
#include <string>

// A stucture to represent a trade
struct trade_position {

  using str = std::string;
  str name = "name";
  unsigned long buy_time = 0;
  unsigned long sell_time = 0;
  double buy_price = 0.0;
  double sell_price = 0.0;
  str strategy = "strategy";
  double yield = 0.0;
  str notes = "default";

  // Streaming out
  friend std::ostream &operator<<(std::ostream &os, const trade_position &p) {
    return os << std::fixed << p.buy_time << " " << p.sell_time << " " << p.name
              << "\t" << p.yield << "\t" << p.strategy << " " << p.notes << " "
              << p.buy_price << " " << p.sell_price << "\n";
  }

  // Streaming in
  friend std::istream &operator>>(std::istream &is, trade_position &p) {
    return is >> p.buy_time >> p.sell_time >> p.name >> p.yield >> p.strategy >>
           p.notes >> p.buy_price >> p.sell_price;
  }
};

#endif
