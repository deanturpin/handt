[![Coverage Status](https://coveralls.io/repos/github/deanturpin/handt/badge.svg)](https://coveralls.io/github/deanturpin/handt)

**Have A Nice Day Trader** is an automated algorithmic trading platform. It
takes a list of currency symbols, requests prices for each, runs a library of
strategies and generates a web page summary of positions. The positions are
(notionally) closed if they exceed a sell threshold or expire after 24 hours.

![](doc/handt.svg)

# Clone and build
```bash
clone https://github.com/deanturpin/handt
cd handt
make
```

Build update to fetch fresh prices.
```bash
make update
```

# Continuous integration
The code is intended to run periodically on a web server. Travis builds are
invoked on commit and Coveralls reports are generated on demand.

# C++
The C++ is built with a C++14 compliant compiler (gcc, clang). The code confirms
to LLVM's coding standard by virtue of periodic runs of ```clang-format```
over the source.

# Web server
```cron``` is used to schedule builds on a Linux web server. The project is
periodically pulled from GitHub, cleaned, compiled and if successful copied into
the web root. Modules are unit tested with each compilation and a code
coverage tool can be run on demand.

A cron job can be simulated locally by running ```make cron``` before pushing to
GitHub. But if the job fails unexpectedly I soon receive an email from the cron
daemon alerting me to the error.

# Exchanges
Intuitively it feels you will respond to market changes quicker the more
frequently you request prices. But Coinbase and CryptoCompare don't publish
updates more often than once per minute. CryptoCompare also has some rate
limiting so 80 requests&mdash;each for a different coin&mdash;seems a good
compromise.

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
