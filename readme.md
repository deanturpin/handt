The code is designed to run periodically on a web server. Therefore, between
runs, state must be saved. Positions are stored in a temporary text file
```positions.csv```. Reads and writes are facilitated by operator<< and
operator>> overloads. See the [position structure](position.h).

# C++
The C++ can be built with any C++11 compliant compiler (gcc, clang). The code
confirms to LLVM's coding standard by virtue of periodic passes of
```clang-format``` over the source.

See the [trading engine](trade.cpp).

# Web server
```cron``` is used to schedule builds on a Linux web server. The project is
periodically pulled from GitHub, compiled from clean and if successful copied
into the web root.

# Exchanges
Coinbase and CryptoCompare - whilst intuitively it seems you should be fetching
prices often, Coinbase and CryptoCompare don't appear to publish updates more
of ten than once per minute.

## CryptoCompare API
```bash
curl
'https://min-api.cryptocompare.com/data/histohour?fsym=ETH&tsym=USD&limit=168&aggregate=1&e=CCCAGG'
```
