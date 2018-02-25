The code is designed to run periodically on a web server. Therefore, between
runs, state must be saved. Positions are stored in a temporary text file.

```cpp
#ifndef POSITION
#define POSITION

#include <iomanip>
#include <istream>
#include <ostream>
#include <string>

// A stucture to represent a trade
struct trade_position {

  std::string name = "name";
  unsigned long timestamp = 0;
  unsigned long duration = 0;
  double buy_price = 0.0;
  double sell_price = 0.0;
  std::string strategy = "strategy";
  double yield = 0.0;
  std::string notes = "NEWTRADE";
  bool open = false;

  // Streaming out
  friend std::ostream &operator<<(std::ostream &os, const trade_position &p) {
    return os << std::fixed << std::setprecision(10) << " " << p.name << "\t"
              << p.yield << "\t" << p.strategy << " " << p.notes << " "
              << p.buy_price << " " << p.sell_price << " " << p.timestamp << " "
              << p.duration << " " << std::boolalpha << p.open << "\n";
  }

  // Streaming in
  friend std::istream &operator>>(std::istream &is, trade_position &p) {
    return is >> std::setprecision(10) >> p.name >> p.yield >> p.strategy >>
           p.notes >> p.buy_price >> p.sell_price >> p.timestamp >>
           p.duration >> std::boolalpha >> p.open;
  }
};

#endif
```

# C++
The C++ can be built withi a C++14 compliant compiler (gcc, clang). The code
confirms to LLVM's coding standard by virtue of periodic passes of
```clang-format``` over the source.

# Strategies
The strategy library is implemented as a vector of classes derived from a pure
virtual base class. A subclass must implement the two methods but further
derieved classes need only override what is necessary to implememt the strategy.

```cpp
struct strategy {

  virtual std::string name() const { return "undefined"; }
  virtual bool buy(const std::vector<double> &) const = 0;
  virtual bool sell(const std::vector<double> &, const double &) const = 0;
};
```

# Web server
```cron``` is used to schedule builds on a Linux web server. The project is
periodically pulled from GitHub, cleaned, compiled and if successful copied into
the web root.

# Exchanges
Whilst intuitively it seems you should be fetching prices often, Coinbase and
CryptoCompare don't publish updates more often than once per minute.

## CryptoCompare API
```bash
curl
'https://min-api.cryptocompare.com/data/histohour?fsym=ETH&tsym=USD&limit=168&aggregate=1&e=CCCAGG'
```
