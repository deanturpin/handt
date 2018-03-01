
# Modular design
Each module reads the result of running the previous and emits its contribution
to the processing chain. Can easily test each stage in isolation. Enforcing a
simply interface between modules enforces a clean design (no complex
structures passed around).

This approach may make the interface harder to change (with is not necessarily a bad
thing) but it does make reasoning about each module much easier.

The strategy module takes the list of coins/prices and emits a line for each
currency that has triggered a buy: coin name, price and list of a matching
strategies.

```
<file.cpp> -> <file.csv>
prices.cpp -> prices.csv
```

## symbols.py
* Get symbol list from CryptoCompare all coins list

## prices.py
* Get prices from CryptoCompare
* Filter small value coins and bad prices

## update.cpp
* Update current positions with recent prices

## strategy.cpp
* Run strategies

## positions.cpp
* Takes the outcome of new strategies
* Consolidate existing and new positions

## execute.cpp
* Execute chosen symbols on an exchange

## close.cpp
* Consider closing each position

## summary.cpp
* Summarise trades so far

## render.sh
* Render HTML page of summary

```
SPK 0.3205666667 10.0_flicking_down 2.00_average_comp 
STA 0.9531 10.0_flicking_down 10.0_stepping_down 2.00_average_inter 
TEC 0.1317666667 10.0_flicking_up 10.0_stepping_up 2.00_average_comp
2.00_average_inter 
TX  1.09 10.0_stepping_down 2.00_average_comp 2.00_average_inter 
UIS 0.04105666667 10.0_stepping_up 2.00_average_inter 
UNC 0.0001058666667 10.0_stepping_down 2.00_average_comp 2.00_average_inter 
URO 0.06262333333 2.00_average_inter 
VIRAL 0.03136 10.0_stepping_down 
VSX 0.03706666667 10.0_stepping_down 
X2  0.00025 10.0_flicking_down 10.0_stepping_up 
ZCC 0.3705666667 10.0_stepping_up 2.00_average_comp 2.00_average_inter 
ZEN 38.01 2.00_average_comp 
```

# C++
The C++ can be built withi a C++14 compliant compiler (gcc, clang). The code
confirms to LLVM's coding standard by virtue of periodic passes of
```clang-format``` over the source.

As the the code is designed to run periodically on a web server, between runs
state must be saved. Positions are read and written to a temporary text file
using operator>> and operator<<.

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

# Heading towards strategy definition language
The current strategy definition makes use of a library of techniques.
```cpp
result stepping_up(series s, param p) { 
  const auto name = NAME("stepping_up", p);
  const bool exec = RECENT_AVERAGE(s) / DISTANT_AVERAGE(s) > THRESHOLD(p);
  return result(name, exec);
}
```

Which isn't too far removed from a strategy definition language.
```
name = "stepping_up"
exec = RECENT_AVERAGE / DISTANT_AVERAGE > THRESHOLD
```


# Coinbase only
After a few days of Coinbase only trading
```
21 strategies have the opportunity to trade 4 coins every two minutes
60480 decisions per day
20 positions held
1 complete trades

STRATEGY % RETURN       $ IN            $ OUT           DURATION (hrs)   

bigcap10 89.425145      400.000000      357.700581      99.199931
bigcap20 0.000000       0.000000        0.000000        0.000000
jklonga3 0.000000       0.000000        0.000000        0.000000
jklonga4 0.000000       0.000000        0.000000        0.000000
jklongav 92.104356      500.000000      460.521780      91.036667
jkrise10 87.207315      400.000000      348.829259      69.887500
jkstep20 0.000000       0.000000        0.000000        0.000000
kossages 0.000000       0.000000        0.000000        0.000000
manualxx 0.000000       0.000000        0.000000        0.000000
nino1000 0.000000       0.000000        0.000000        0.000000
nino1001 0.000000       0.000000        0.000000        0.000000
nino1003 0.000000       0.000000        0.000000        0.000000
rolav10a 86.881881      300.000000      260.645642      42.194722
rolav20a 88.248806      400.000000      352.995225      56.104236
simsimma 0.000000       0.000000        0.000000        0.000000
skisun05 94.082333      100.000000      94.082333       10.166667
skisun10 0.000000       0.000000        0.000000        0.000000
skisun20 0.000000       0.000000        0.000000        0.000000
turbo_10 0.000000       0.000000        0.000000        0.000000
turbo_20 0.000000       0.000000        0.000000        0.000000
turbo_30 0.000000       0.000000        0.000000        0.000000

TOTAL    89.274991      2100.000000     1874.774820                     
```

```
 BTC    110.203179      jklongav okprices 10537.010000 11612.120000 1519410962
 302640
 ```

