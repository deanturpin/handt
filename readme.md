[![Build Status](https://travis-ci.org/deanturpin/handt.svg?branch=master)](https://travis-ci.org/deanturpin/handt)

**History is no indicator of future performance. Don't invest what you can't
afford to lose.**

Having said that... *Have A Nice Day Trader* is an algorithmic trading platform
that uses patterns in historic prices to forecast prospective trades. Prices
are requested for all currency pairs traded by Binance and Coinbase over the
last 80 days. A library of strategies is backtested over all pairs and the
summary below is generated.

Prices are fetched using the [CryptoCompare
API](https://min-api.cryptocompare.com/).

---

Generated Sun Oct  7 15:49:20 2018

* 4 threads
* 3 currency pairs
* 3,432 strategies
* 18,503,692 backtests

# Current prospects

Strategy|Pair|Good/Bad|Spot|Last (days)
---|---|---|---|---
Supine-Sphynx-4|[SALT-BTC](https://binance.com/en/trade/SALT_BTC)|16/51|9.23e-05|22
Supine-Sphynx-4|[SALT-ETH](https://binance.com/en/trade/SALT_ETH)|15/66|0.002715|7
Supine-Sphynx-5|[SALT-ETH](https://binance.com/en/trade/SALT_ETH)|12/53|0.002715|15
Supine-Sphynx-3|[SALT-BTC](https://binance.com/en/trade/SALT_BTC)|18/89|9.23e-05|4
Indifferent-Sphynx-5|[SALT-ETH](https://binance.com/en/trade/SALT_ETH)|12/61|0.002715|15
Slouching-Sphynx-5|[SALT-ETH](https://binance.com/en/trade/SALT_ETH)|12/61|0.002715|15
Supine-Sphynx-3|[SALT-ETH](https://binance.com/en/trade/SALT_ETH)|18/92|0.002715|7
Slouching-Sphynx-4|[SALT-ETH](https://binance.com/en/trade/SALT_ETH)|15/77|0.002715|7
Indifferent-Sphynx-4|[SALT-ETH](https://binance.com/en/trade/SALT_ETH)|15/78|0.002715|7
Supine-Norrbottenspets-6|[SALT-ETH](https://binance.com/en/trade/SALT_ETH)|17/93|0.002715|7
Supine-Shiba Inu-8|[SALT-ETH](https://binance.com/en/trade/SALT_ETH)|15/84|0.002715|13

# 80-day backtest

Strategy|Pair|Good/Bad|Spot|Last (days)
---|---|---|---|---
Indifferent-Munchkin-7|[SALT-BTC](https://binance.com/en/trade/SALT_BTC)|6/1|9.23e-05|2
Darting-Munchkin-7|[SALT-BTC](https://binance.com/en/trade/SALT_BTC)|6/1|9.23e-05|2
Indifferent-Munchkin-7|[SALT-ETH](https://binance.com/en/trade/SALT_ETH)|5/1|0.002715|2
Leaping-Bandicoot-3|[SALT-ETH](https://binance.com/en/trade/SALT_ETH)|5/1|0.002715|2
Darting-Munchkin-7|[SALT-ETH](https://binance.com/en/trade/SALT_ETH)|5/1|0.002715|2
Indifferent-Jagdterrier-19|[SALT-ETH](https://binance.com/en/trade/SALT_ETH)|4/0|0.002715|2
Indifferent-Jagdterrier-20|[SALT-ETH](https://binance.com/en/trade/SALT_ETH)|4/0|0.002715|2
Indifferent-Affenpinscher-15|[SALT-ETH](https://binance.com/en/trade/SALT_ETH)|4/0|0.002715|2
Indifferent-Affenpinscher-16|[SALT-ETH](https://binance.com/en/trade/SALT_ETH)|4/0|0.002715|2
Indifferent-Munchkin-8|[SALT-ETH](https://binance.com/en/trade/SALT_ETH)|4/0|0.002715|2
Indifferent-Cricket-19|[SALT-ETH](https://binance.com/en/trade/SALT_ETH)|4/0|0.002715|2
Indifferent-Cricket-20|[SALT-ETH](https://binance.com/en/trade/SALT_ETH)|4/0|0.002715|2
Indifferent-Axolotl-19|[SALT-ETH](https://binance.com/en/trade/SALT_ETH)|4/0|0.002715|2
Indifferent-Axolotl-20|[SALT-ETH](https://binance.com/en/trade/SALT_ETH)|4/0|0.002715|2
Indifferent-Pomeranian-15|[SALT-ETH](https://binance.com/en/trade/SALT_ETH)|4/0|0.002715|2
Indifferent-Pomeranian-16|[SALT-ETH](https://binance.com/en/trade/SALT_ETH)|4/0|0.002715|2
Leaping-Munchkin-7|[SALT-ETH](https://binance.com/en/trade/SALT_ETH)|4/0|0.002715|2
Leaping-Munchkin-8|[SALT-ETH](https://binance.com/en/trade/SALT_ETH)|4/0|0.002715|2
Darting-Jagdterrier-19|[SALT-ETH](https://binance.com/en/trade/SALT_ETH)|4/0|0.002715|2
Darting-Jagdterrier-20|[SALT-ETH](https://binance.com/en/trade/SALT_ETH)|4/0|0.002715|2
Darting-Affenpinscher-15|[SALT-ETH](https://binance.com/en/trade/SALT_ETH)|4/0|0.002715|2

# Strategy performance summary
3432 strategies
```
Indifferent-Jagdterrier-19 8/0
Indifferent-Affenpinscher-15 8/0
Darting-Jagdterrier-19 8/0
Darting-Affenpinscher-15 8/0
Darting-Pomeranian-15 8/0
Indifferent-Cricket-19 8/1
Indifferent-Axolotl-19 8/1
Darting-Cricket-19 8/1
Darting-Axolotl-19 8/1
Indifferent-Jagdterrier-18 8/1
Darting-Jagdterrier-18 8/1
Indifferent-Affenpinscher-16 7/1
Darting-Affenpinscher-16 7/1
Darting-Pomeranian-16 7/1
Indifferent-Affenpinscher-17 6/0
Indifferent-Affenpinscher-18 6/0
Indifferent-Pomeranian-18 6/0
Darting-Affenpinscher-17 6/0
Darting-Affenpinscher-18 6/0
Darting-Pomeranian-17 6/0
Darting-Pomeranian-18 6/0
Indifferent-Munchkin-7 13/2
Darting-Munchkin-7 13/2
Indifferent-Pomeranian-17 6/1
Leaping-Pomeranian-16 5/1
Leaping-Affenpinscher-17 4/0
Leaping-Affenpinscher-18 4/0
Leaping-Pomeranian-17 4/0
Leaping-Pomeranian-18 4/0
Indifferent-Jagdterrier-17 8/2
Indifferent-Affenpinscher-13 8/2
```

