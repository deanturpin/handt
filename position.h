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

  // These are set by initialiser
  using str = std::string;
  str name = "name";
  str buy_price = "buy_price";
  str buy_time = "buy_time";
  str strategy = "strategy";

  // These are defaulted
  str sell_time = "sell_time";
  str sell_price = "sell_price";
  str yield = "yield";
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
