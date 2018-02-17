#ifndef POSITION
#define POSITION

#include <string>
#include <istream>
#include <ostream>

// Struggled for a while how to handle a no position. Zero is the first choice
// but zero also represents a complete fail. Perhaps that also represents a no
// position? All state is stored in a text file so it makes sense to handle it
// so.
struct position {

  using str = std::string;
  str name = "name";
  str buy_time = "buy_time";
  str sell_time = "sell_time";
  double buy_price = 0.0;
  double sell_price = 0.0;
  str strategy = "strategy";
  double yield = 0.0;
  str duration = "duration";
  str exchange = "cryptocompare";

  // Streaming out
  friend std::ostream &operator<<(std::ostream &os, const position &p) {
    return os << p.name << " " << p.buy_time << " " << p.sell_time << " "
              << p.duration << " " << p.buy_price << " " << p.sell_price << " "
              << p.yield << " " << p.exchange << " " << p.strategy << "\n";
  }

  // Streaming in
  friend std::istream &operator>>(std::istream &is, position &p) {
    return is >> p.name >> p.buy_time >> p.sell_time >> p.duration >>
           p.buy_price >> p.sell_price >> p.yield >> p.exchange >> p.strategy;
  }
};

#endif
