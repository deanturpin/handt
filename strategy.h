#ifndef STRATEGY
#define STRATEGY

#include <numeric>
#include <string>
#include <vector>
#include <iostream>
#include <istream>

// SNOOPER
// Trigger when spot is 10% below average for the period
// Don't track to bottom (could fall to zero)
// Sell when spot is 10% above lowest price
struct strategy {
  const std::string name = "snooper";
  const double threshold = 1.1;
  bool buy(const std::vector<double> &p) const {
    const double spot = p.back();
    const double average =
        std::accumulate(p.cbegin(), p.cend(), 0.0,
                        [](auto &sum, auto &i) { return sum + i; }) /
        p.size();
    return average / spot > threshold;
  }

  bool sell(const double &position, const double &spot) const {
    return spot / position > threshold;
  }
};

// ALWAYS
// Always buy, always sell
struct always : strategy {
  const std::string name = "always";
  bool buy(const std::vector<double> &p) const {
    static_cast<void>(p);
    return true;
  }
  bool sell(const double &position, const double &spot) const {
    static_cast<void>(position);
    static_cast<void>(spot);
    return true;
  }
};

// SNOOPER GRANDE
// Like SNOOPER but 15%
struct snooper_grande : strategy {
  const std::string name = "snooper_grande";
  const double threshold = 1.15;
};

// SNOOPER PEQUENO
// Like SNOOPER but 5%
struct snooper_pequeno : strategy {
  const std::string name = "snooper_pequeno";
  const double threshold = 1.15;
};

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

  // Streaming out
  friend std::ostream& operator<< (std::ostream& os, const position& p) {
    return os
      << p.name << " "
      << p.buy_time << " "
      << p.sell_time << " "
      << p.duration << " "
      << p.buy_price << " "
      << p.sell_price << " "
      << p.yield << " "
      << p.strategy << "\n";
  }

  // Streaming in
  friend std::istream& operator>> (std::istream& is, position& p) {
    return is
      >> p.name
      >> p.buy_time
      >> p.sell_time
      >> p.duration
      >> p.buy_price
      >> p.sell_price
      >> p.yield
      >> p.strategy;
  }
};

#endif
