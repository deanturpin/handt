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

Generated Mon 1 Oct 15:37:13 GMT 2018
* 4 currency pairs
* 3,300 strategies
* 13,200 strategy/pair combinations
* 24,133,660 backtests

# Current prospects
Prospects based on prices from the last 24 hours.

Strategy|Pair|Good/Bad|Spot|Last (days)
---|---|---|---|---
Leaping-Jagdterrier-3|[SALT-ETH](https://binance.com/en/trade/SALT_ETH)|12/82|0.002144|8
Leaping-Munchkin-2|[SALT-ETH](https://binance.com/en/trade/SALT_ETH)|9/62|0.002144|8
Crouching-Jagdterrier-3|[SALT-ETH](https://binance.com/en/trade/SALT_ETH)|15/112|0.002144|8
Darting-Jagdterrier-3|[SALT-ETH](https://binance.com/en/trade/SALT_ETH)|15/112|0.002144|8
Leaping-Jagdterrier-2|[SALT-ETH](https://binance.com/en/trade/SALT_ETH)|12/95|0.002144|8
Crouching-Munchkin-2|[SALT-ETH](https://binance.com/en/trade/SALT_ETH)|12/98|0.002144|8
Darting-Munchkin-2|[SALT-ETH](https://binance.com/en/trade/SALT_ETH)|12/98|0.002144|8
Darting-Jagdterrier-2|[SALT-ETH](https://binance.com/en/trade/SALT_ETH)|16/138|0.002144|4
Crouching-Jagdterrier-2|[SALT-ETH](https://binance.com/en/trade/SALT_ETH)|16/142|0.002144|4
Darting-Axolotl-3|[SALT-ETH](https://binance.com/en/trade/SALT_ETH)|17/159|0.002144|4
Darting-Cricket-3|[SALT-ETH](https://binance.com/en/trade/SALT_ETH)|18/172|0.002144|3

# 80-day backtest
The results are ordered by success which is measured using the proportion of
good to bad trades.

Strategy|Pair|Good/Bad|Spot
---|---|---|---
Crouching-Munchkin-7|[SALT-BTC](https://binance.com/en/trade/SALT_BTC)|5/1|7.45e-05
Darting-Munchkin-7|[SALT-BTC](https://binance.com/en/trade/SALT_BTC)|5/1|7.45e-05
Crouching-Munchkin-7|[SALT-ETH](https://binance.com/en/trade/SALT_ETH)|4/1|0.002144
Leaping-Bandicoot-3|[SALT-ETH](https://binance.com/en/trade/SALT_ETH)|4/1|0.002144
Darting-Munchkin-7|[SALT-ETH](https://binance.com/en/trade/SALT_ETH)|4/1|0.002144
Crouching-Jagdterrier-9|[SALT-BTC](https://binance.com/en/trade/SALT_BTC)|7/2|7.45e-05
Darting-Jagdterrier-9|[SALT-BTC](https://binance.com/en/trade/SALT_BTC)|7/2|7.45e-05
Crouching-Jagdterrier-19|[SALT-ETH](https://binance.com/en/trade/SALT_ETH)|3/0|0.002144
Crouching-Jagdterrier-20|[SALT-ETH](https://binance.com/en/trade/SALT_ETH)|3/0|0.002144
Crouching-Affenpinscher-15|[SALT-ETH](https://binance.com/en/trade/SALT_ETH)|3/0|0.002144
Crouching-Affenpinscher-16|[SALT-ETH](https://binance.com/en/trade/SALT_ETH)|3/0|0.002144
Crouching-Munchkin-8|[SALT-ETH](https://binance.com/en/trade/SALT_ETH)|3/0|0.002144
Crouching-Cricket-19|[SALT-ETH](https://binance.com/en/trade/SALT_ETH)|3/0|0.002144
Crouching-Cricket-20|[SALT-ETH](https://binance.com/en/trade/SALT_ETH)|3/0|0.002144
Crouching-Axolotl-19|[SALT-ETH](https://binance.com/en/trade/SALT_ETH)|3/0|0.002144
Crouching-Axolotl-20|[SALT-ETH](https://binance.com/en/trade/SALT_ETH)|3/0|0.002144
Crouching-Pomeranian-15|[SALT-ETH](https://binance.com/en/trade/SALT_ETH)|3/0|0.002144
Crouching-Pomeranian-16|[SALT-ETH](https://binance.com/en/trade/SALT_ETH)|3/0|0.002144
Leaping-Munchkin-7|[SALT-ETH](https://binance.com/en/trade/SALT_ETH)|3/0|0.002144
Leaping-Munchkin-8|[SALT-ETH](https://binance.com/en/trade/SALT_ETH)|3/0|0.002144
Darting-Jagdterrier-19|[SALT-ETH](https://binance.com/en/trade/SALT_ETH)|3/0|0.002144
Darting-Jagdterrier-20|[SALT-ETH](https://binance.com/en/trade/SALT_ETH)|3/0|0.002144
Darting-Affenpinscher-15|[SALT-ETH](https://binance.com/en/trade/SALT_ETH)|3/0|0.002144
Darting-Affenpinscher-16|[SALT-ETH](https://binance.com/en/trade/SALT_ETH)|3/0|0.002144
Darting-Munchkin-8|[SALT-ETH](https://binance.com/en/trade/SALT_ETH)|3/0|0.002144
Darting-Cricket-19|[SALT-ETH](https://binance.com/en/trade/SALT_ETH)|3/0|0.002144
Darting-Cricket-20|[SALT-ETH](https://binance.com/en/trade/SALT_ETH)|3/0|0.002144
Darting-Axolotl-19|[SALT-ETH](https://binance.com/en/trade/SALT_ETH)|3/0|0.002144
Darting-Axolotl-20|[SALT-ETH](https://binance.com/en/trade/SALT_ETH)|3/0|0.002144
Darting-Havanese-19|[SALT-ETH](https://binance.com/en/trade/SALT_ETH)|3/0|0.002144
Darting-Havanese-20|[SALT-ETH](https://binance.com/en/trade/SALT_ETH)|3/0|0.002144
Darting-Pomeranian-15|[SALT-ETH](https://binance.com/en/trade/SALT_ETH)|3/0|0.002144
Darting-Pomeranian-16|[SALT-ETH](https://binance.com/en/trade/SALT_ETH)|3/0|0.002144
Crouching-Havanese-11|[XMR-ETH](https://binance.com/en/trade/XMR_ETH)|3/0|0.4974
Crouching-Jagdterrier-18|[SALT-BTC](https://binance.com/en/trade/SALT_BTC)|3/0|7.45e-05
Crouching-Jagdterrier-19|[SALT-BTC](https://binance.com/en/trade/SALT_BTC)|3/0|7.45e-05
Crouching-Affenpinscher-15|[SALT-BTC](https://binance.com/en/trade/SALT_BTC)|3/0|7.45e-05
Crouching-Munchkin-8|[SALT-BTC](https://binance.com/en/trade/SALT_BTC)|3/0|7.45e-05
Crouching-Bandicoot-4|[SALT-BTC](https://binance.com/en/trade/SALT_BTC)|3/0|7.45e-05
Darting-Jagdterrier-18|[SALT-BTC](https://binance.com/en/trade/SALT_BTC)|3/0|7.45e-05
Darting-Jagdterrier-19|[SALT-BTC](https://binance.com/en/trade/SALT_BTC)|3/0|7.45e-05
Darting-Affenpinscher-15|[SALT-BTC](https://binance.com/en/trade/SALT_BTC)|3/0|7.45e-05
Darting-Munchkin-8|[SALT-BTC](https://binance.com/en/trade/SALT_BTC)|3/0|7.45e-05
Darting-Bandicoot-4|[SALT-BTC](https://binance.com/en/trade/SALT_BTC)|3/0|7.45e-05
Darting-Pomeranian-15|[SALT-BTC](https://binance.com/en/trade/SALT_BTC)|3/0|7.45e-05
Leaping-Affenpinscher-5|[XMR-BTC](https://binance.com/en/trade/XMR_BTC)|3/0|0.01732
Crouching-Jagdterrier-16|[SALT-ETH](https://binance.com/en/trade/SALT_ETH)|3/1|0.002144
Crouching-Jagdterrier-17|[SALT-ETH](https://binance.com/en/trade/SALT_ETH)|3/1|0.002144
Crouching-Jagdterrier-18|[SALT-ETH](https://binance.com/en/trade/SALT_ETH)|3/1|0.002144
Crouching-Affenpinscher-13|[SALT-ETH](https://binance.com/en/trade/SALT_ETH)|3/1|0.002144
Crouching-Affenpinscher-14|[SALT-ETH](https://binance.com/en/trade/SALT_ETH)|3/1|0.002144
Crouching-Axolotl-18|[SALT-ETH](https://binance.com/en/trade/SALT_ETH)|3/1|0.002144
Leaping-Griffon-7|[SALT-ETH](https://binance.com/en/trade/SALT_ETH)|3/1|0.002144
Leaping-Pomeranian-6|[SALT-ETH](https://binance.com/en/trade/SALT_ETH)|6/2|0.002144
Darting-Jagdterrier-16|[SALT-ETH](https://binance.com/en/trade/SALT_ETH)|3/1|0.002144
Darting-Jagdterrier-17|[SALT-ETH](https://binance.com/en/trade/SALT_ETH)|3/1|0.002144
Darting-Jagdterrier-18|[SALT-ETH](https://binance.com/en/trade/SALT_ETH)|3/1|0.002144
Darting-Affenpinscher-13|[SALT-ETH](https://binance.com/en/trade/SALT_ETH)|3/1|0.002144
Darting-Affenpinscher-14|[SALT-ETH](https://binance.com/en/trade/SALT_ETH)|3/1|0.002144
Darting-Axolotl-18|[SALT-ETH](https://binance.com/en/trade/SALT_ETH)|3/1|0.002144
Darting-Pomeranian-13|[SALT-ETH](https://binance.com/en/trade/SALT_ETH)|3/1|0.002144
Darting-Pomeranian-14|[SALT-ETH](https://binance.com/en/trade/SALT_ETH)|3/1|0.002144
Crouching-Jagdterrier-9|[XMR-ETH](https://binance.com/en/trade/XMR_ETH)|3/1|0.4974
Crouching-Cricket-9|[XMR-ETH](https://binance.com/en/trade/XMR_ETH)|3/1|0.4974
Crouching-Axolotl-9|[XMR-ETH](https://binance.com/en/trade/XMR_ETH)|3/1|0.4974
Leaping-Jagdterrier-9|[XMR-ETH](https://binance.com/en/trade/XMR_ETH)|3/1|0.4974
Leaping-Cricket-9|[XMR-ETH](https://binance.com/en/trade/XMR_ETH)|3/1|0.4974
Leaping-Axolotl-9|[XMR-ETH](https://binance.com/en/trade/XMR_ETH)|3/1|0.4974
Leaping-Havanese-9|[XMR-ETH](https://binance.com/en/trade/XMR_ETH)|3/1|0.4974
Darting-Jagdterrier-9|[XMR-ETH](https://binance.com/en/trade/XMR_ETH)|3/1|0.4974
Darting-Cricket-9|[XMR-ETH](https://binance.com/en/trade/XMR_ETH)|3/1|0.4974
Darting-Axolotl-9|[XMR-ETH](https://binance.com/en/trade/XMR_ETH)|3/1|0.4974
