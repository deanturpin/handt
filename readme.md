# Modular design
Each module in the chain processes the result from the previous stage and emits its contribution. Can easily test each stage in isolation. Enforcing a
simply interface between modules enforces a clean design (no complex
structures passed around).

This approach may make the interface harder to change (with is not necessarily a bad
thing) but it does make reasoning about each module much easier. A module can
even be ported to a different language so long as the interface is honoured.

The strategy module takes the list of coins/prices and emits a line for each
currency that has triggered a buy: coin name, price and list of a matching
strategies.

![](doc/handt.svg)

# C++
The C++ can be built withi a C++14 compliant compiler (gcc, clang). The code
confirms to LLVM's coding standard by virtue of periodic passes of
```clang-format``` over the source.

As the the code is designed to run periodically on a web server, between runs
state must be saved. Positions are read and written to a temporary text file
using operator>> and operator<<.

# Web server
```cron``` is used to schedule builds on a Linux web server. The project is
periodically pulled from GitHub, cleaned, compiled and if successful copied into
the web root. In the event of a crash a subsequent run could remove the
troublesome dataset before we've had chance to review it. So a flag is set at
the start of a build and cleared at the end, if on a subsequent run the flag is
already set then the build will abort.

# Exchanges
Whilst intuitively it seems you should be fetching prices often, Coinbase and
CryptoCompare don't publish updates more often than once per minute.

## CryptoCompare API
```bash
curl
'https://min-api.cryptocompare.com/data/histohour?fsym=ETH&tsym=USD&limit=168&aggregate=1&e=CCCAGG'
```

# Heading towards a strategy definition language
The current strategy definition makes use of a library of techniques.
```cpp
result stepping_up(series s, param p) { 
  const auto name = NAME("stepping_up", p);
  const bool exec = RECENT_AVERAGE(s) / DISTANT_AVERAGE(s) > THRESHOLD(p);
  return result(name, exec);
}
```

Which doesn't seem too far removed from a strategy definition language.
```
name = "stepping_up"
exec = RECENT_AVERAGE / DISTANT_AVERAGE > THRESHOLD
```
