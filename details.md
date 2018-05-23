[![Build Status](https://travis-ci.org/deanturpin/handt.svg?branch=master)](https://travis-ci.org/deanturpin/handt)

**Have A Nice Day Trader** is an algorithmic trading platform. Prices are
requested for a list of currency symbols, a library of strategies is run over
the prices and a web page summary of strategy performance is generated every
minute. The positions are (notionally) closed if they exceed a sell threshold or
expire after 24 hours.

![](doc/handt.svg)

Build "update" to fetch fresh prices and symbols.
```bash
make update
```

# C++
The C++ is built with a C++14 compliant compiler (gcc, clang). The code confirms
to LLVM's coding standard by virtue of periodic runs of ```clang-format``` over
the source. To speed up development the bash script ```bin/waitandcompile.sh```
can be used to compile and run C++ code as it is saved.

```bash
$ bin/waitandcompile.sh index.cpp 
Wait for index.cpp
Using standard c++14
```

# Web server
```cron``` is used to schedule builds on a Linux web server. The project is
periodically pulled from GitHub, compiled, run and if successful the results are
copied into the web root. Modules are unit tested with each compilation and a
code coverage tool can be run on demand. Compilation errors discovered on the
server are reported immediately by email.

```bash
*/1 * * * * cd ~/handt && nice make CXX=g++ --silent gitpull update && cp -u index.html ~/public_html/
```

The web page is created from an [HTML template](include/index.html). The
template contains keywords which are substituted for current data.

```html
<h1>Have A Nice Day Trader <small>DATE</small></h1>
```

# Exchanges
Intuitively it feels that requesting prices more often will make the software
more responsive to market changes. But Coinbase and CryptoCompare actually don't
publish updates more often than once per minute. CryptoCompare also has API
request rate limiting but in practice only 60 coins can be processed per minute
to ensure we don't clash with the next cron job.

## Currency viability
Before running the strategies coins are subjected to a preflight check to ensure
the currency has some activity.

# Strategy window during back-testing
*Any* strategy that triggered a year ago on BTC would have succeeded by now. So we
must consider how far into the future we are prepared to go.

For example: should we expect a return after one day from a decision based on a
week's worth of prices?
