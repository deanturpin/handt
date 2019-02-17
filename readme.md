[![Build Status](https://travis-ci.org/deanturpin/handt.svg?branch=master)](https://travis-ci.org/deanturpin/handt)

**History is no indicator of future performance. Don't invest what you can't
afford to lose.**

*Have A Nice Day Trader* is an algorithmic trading platform that uses patterns
in historic prices to influence future trades. 80 days of prices are requested
for hundreds of currency pairs, then a library of strategies is backtested and
a summary is generated.

Run in Docker:
```bash
docker run deanturpin/handt
```

Prices are fetched using the [CryptoCompare
API](https://min-api.cryptocompare.com/). See the entry point in
[main.cpp](https://github.com/deanturpin/handt/blob/master/main.cpp) and [all
exchanges](https://min-api.cryptocompare.com/data/all/exchanges). The
strategies are defined in the
[low_frequency_trader.cpp](low_frequency_trader.cpp), the permutations and
thresholds are generated in [strategy.cpp](strategy.cpp).

