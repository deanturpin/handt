#ifndef POSITION
#define POSITION

#include <istream>
#include <ostream>
#include <string>

// A stucture to represent a trade
struct position {

  using str = std::string;
  str name = "name";
  str buy_time = "buy_time";
  str sell_time = "sell_time";
  double buy_price = 0.0;
  double sell_price = 0.0;
  str strategy = "strategy";
  double yield = 0.0;

  // Streaming out
  friend std::ostream &operator<<(std::ostream &os, const position &p) {
    return os << std::fixed << p.buy_time << " " << p.sell_time << " " << p.name
      << "\t" << p.yield << "\t" << p.strategy << "\t" << p.buy_price << " " <<
      p.sell_price << "\n";
  }

  // Streaming in
  friend std::istream &operator>>(std::istream &is, position &p) {
    return is >> p.buy_time >> p.sell_time >> p.name >> p.yield >> p.strategy >>
      p.buy_price >> p.sell_price;
  }
};

#endif
