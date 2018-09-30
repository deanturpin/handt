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

Generated Sun 30 Sep 16:29:00 GMT 2018
* 19 currency pairs
* 62,700 strategy/pair combinations
* 116,227,959 backtests

# Current prospects
Prospects based on prices from the last 24 hours.

Strategy|Pair|Good/Bad|Spot
---|---|---|---
Darting-Sphynx-2|[AMB-BNB](https://binance.com/en/trade/AMB_BNB)|13/17|0.0152
Darting-Shiba Inu-5|[AMB-BNB](https://binance.com/en/trade/AMB_BNB)|14/28|0.0152
Darting-Shiba Inu-4|[AMB-BNB](https://binance.com/en/trade/AMB_BNB)|16/54|0.0152
Crouching-Sphynx-2|[AMB-BNB](https://binance.com/en/trade/AMB_BNB)|31/106|0.0152
Crouching-Shiba Inu-5|[AMB-BNB](https://binance.com/en/trade/AMB_BNB)|31/141|0.0152
Crouching-Shiba Inu-4|[AMB-BNB](https://binance.com/en/trade/AMB_BNB)|33/191|0.0152
Crouching-Affenpinscher-4|[XVG-BTC](https://binance.com/en/trade/XVG_BTC)|5/29|2.33e-06
Darting-Affenpinscher-4|[XVG-BTC](https://binance.com/en/trade/XVG_BTC)|5/29|2.33e-06
Darting-Pomeranian-4|[XVG-BTC](https://binance.com/en/trade/XVG_BTC)|8/48|2.33e-06
Darting-Shiba Inu-3|[AMB-BNB](https://binance.com/en/trade/AMB_BNB)|17/104|0.0152
Slouching-Cricket-2|[AMB-ETH](https://binance.com/en/trade/AMB_ETH)|20/123|0.0006297

# 80-day backtest
The results are ordered by success which is measured using the proportion of
good to bad trades.

Strategy|Pair|Good/Bad|Spot
---|---|---|---
Supine-Norrbottenspets-16|[AMB-BTC](https://binance.com/en/trade/AMB_BTC)|6/0|2.247e-05
Crouching-Norrbottenspets-16|[AMB-BTC](https://binance.com/en/trade/AMB_BTC)|6/1|2.247e-05
Supine-Shiba Inu-16|[AMB-BTC](https://binance.com/en/trade/AMB_BTC)|6/1|2.247e-05
Slouching-Norrbottenspets-16|[AMB-BTC](https://binance.com/en/trade/AMB_BTC)|6/1|2.247e-05
Darting-Norrbottenspets-4|[AMB-BNB](https://binance.com/en/trade/AMB_BNB)|6/1|0.0152
Crouching-Norrbottenspets-17|[AMB-BTC](https://binance.com/en/trade/AMB_BTC)|5/0|2.247e-05
Crouching-Xoloitzcuintli-11|[AMB-BTC](https://binance.com/en/trade/AMB_BTC)|5/0|2.247e-05
Crouching-Griffon-18|[AMB-BTC](https://binance.com/en/trade/AMB_BTC)|5/0|2.247e-05
Crouching-Havanese-18|[AMB-BTC](https://binance.com/en/trade/AMB_BTC)|5/0|2.247e-05
Crouching-Pekingese-11|[AMB-BTC](https://binance.com/en/trade/AMB_BTC)|5/0|2.247e-05
Supine-Norrbottenspets-17|[AMB-BTC](https://binance.com/en/trade/AMB_BTC)|5/0|2.247e-05
Supine-Xoloitzcuintli-11|[AMB-BTC](https://binance.com/en/trade/AMB_BTC)|5/0|2.247e-05
Supine-Griffon-17|[AMB-BTC](https://binance.com/en/trade/AMB_BTC)|5/0|2.247e-05
Supine-Griffon-18|[AMB-BTC](https://binance.com/en/trade/AMB_BTC)|5/0|2.247e-05
Supine-Shiba Inu-17|[AMB-BTC](https://binance.com/en/trade/AMB_BTC)|5/0|2.247e-05
Supine-Havanese-17|[AMB-BTC](https://binance.com/en/trade/AMB_BTC)|5/0|2.247e-05
Supine-Havanese-18|[AMB-BTC](https://binance.com/en/trade/AMB_BTC)|5/0|2.247e-05
Supine-Pekingese-11|[AMB-BTC](https://binance.com/en/trade/AMB_BTC)|5/0|2.247e-05
Darting-Griffon-8|[AMB-BTC](https://binance.com/en/trade/AMB_BTC)|5/0|2.247e-05
Slouching-Norrbottenspets-17|[AMB-BTC](https://binance.com/en/trade/AMB_BTC)|5/0|2.247e-05
Slouching-Xoloitzcuintli-11|[AMB-BTC](https://binance.com/en/trade/AMB_BTC)|5/0|2.247e-05
Slouching-Griffon-18|[AMB-BTC](https://binance.com/en/trade/AMB_BTC)|5/0|2.247e-05
Slouching-Havanese-18|[AMB-BTC](https://binance.com/en/trade/AMB_BTC)|5/0|2.247e-05
Slouching-Pekingese-11|[AMB-BTC](https://binance.com/en/trade/AMB_BTC)|5/0|2.247e-05
Darting-Sphynx-4|[AMB-BNB](https://binance.com/en/trade/AMB_BNB)|5/0|0.0152
Crouching-Havanese-15|[IOT-BNB](https://binance.com/en/trade/IOT_BNB)|5/1|0.0572
Crouching-Griffon-17|[AMB-BTC](https://binance.com/en/trade/AMB_BTC)|5/1|2.247e-05
Crouching-Shiba Inu-17|[AMB-BTC](https://binance.com/en/trade/AMB_BTC)|5/1|2.247e-05
Supine-Xoloitzcuintli-10|[AMB-BTC](https://binance.com/en/trade/AMB_BTC)|5/1|2.247e-05
Supine-Pekingese-10|[AMB-BTC](https://binance.com/en/trade/AMB_BTC)|5/1|2.247e-05
Slouching-Griffon-17|[AMB-BTC](https://binance.com/en/trade/AMB_BTC)|5/1|2.247e-05
Slouching-Shiba Inu-17|[AMB-BTC](https://binance.com/en/trade/AMB_BTC)|5/1|2.247e-05
Slouching-Pomeranian-6|[IOT-ETH](https://binance.com/en/trade/IOT_ETH)|5/1|0.00242
Supine-Havanese-12|[AMB-BNB](https://binance.com/en/trade/AMB_BNB)|5/1|0.0152
Darting-Shiba Inu-8|[AMB-BNB](https://binance.com/en/trade/AMB_BNB)|5/1|0.0152
Crouching-Munchkin-7|[SALT-BTC](https://binance.com/en/trade/SALT_BTC)|5/1|7.5e-05
Darting-Munchkin-7|[SALT-BTC](https://binance.com/en/trade/SALT_BTC)|5/1|7.5e-05
Crouching-Shiba Inu-15|[IOT-BNB](https://binance.com/en/trade/IOT_BNB)|4/0|0.0572
Slouching-Shiba Inu-15|[IOT-BNB](https://binance.com/en/trade/IOT_BNB)|4/0|0.0572
Crouching-Norrbottenspets-18|[AMB-BTC](https://binance.com/en/trade/AMB_BTC)|4/0|2.247e-05
Crouching-Norrbottenspets-19|[AMB-BTC](https://binance.com/en/trade/AMB_BTC)|4/0|2.247e-05
Crouching-Xoloitzcuintli-12|[AMB-BTC](https://binance.com/en/trade/AMB_BTC)|4/0|2.247e-05
Crouching-Griffon-19|[AMB-BTC](https://binance.com/en/trade/AMB_BTC)|4/0|2.247e-05
Crouching-Shiba Inu-19|[AMB-BTC](https://binance.com/en/trade/AMB_BTC)|4/0|2.247e-05
Crouching-Havanese-19|[AMB-BTC](https://binance.com/en/trade/AMB_BTC)|4/0|2.247e-05
Crouching-Pekingese-12|[AMB-BTC](https://binance.com/en/trade/AMB_BTC)|4/0|2.247e-05
Supine-Norrbottenspets-18|[AMB-BTC](https://binance.com/en/trade/AMB_BTC)|4/0|2.247e-05
Supine-Norrbottenspets-19|[AMB-BTC](https://binance.com/en/trade/AMB_BTC)|4/0|2.247e-05
Supine-Xoloitzcuintli-12|[AMB-BTC](https://binance.com/en/trade/AMB_BTC)|4/0|2.247e-05
Supine-Capybara-10|[AMB-BTC](https://binance.com/en/trade/AMB_BTC)|4/0|2.247e-05
Supine-Badger-5|[AMB-BTC](https://binance.com/en/trade/AMB_BTC)|4/0|2.247e-05
Supine-Griffon-19|[AMB-BTC](https://binance.com/en/trade/AMB_BTC)|4/0|2.247e-05
Supine-Shiba Inu-19|[AMB-BTC](https://binance.com/en/trade/AMB_BTC)|4/0|2.247e-05
Supine-Havanese-19|[AMB-BTC](https://binance.com/en/trade/AMB_BTC)|4/0|2.247e-05
Supine-Pekingese-12|[AMB-BTC](https://binance.com/en/trade/AMB_BTC)|4/0|2.247e-05
Slouching-Norrbottenspets-18|[AMB-BTC](https://binance.com/en/trade/AMB_BTC)|4/0|2.247e-05
Slouching-Norrbottenspets-19|[AMB-BTC](https://binance.com/en/trade/AMB_BTC)|4/0|2.247e-05
Slouching-Xoloitzcuintli-12|[AMB-BTC](https://binance.com/en/trade/AMB_BTC)|4/0|2.247e-05
Slouching-Griffon-19|[AMB-BTC](https://binance.com/en/trade/AMB_BTC)|4/0|2.247e-05
Slouching-Shiba Inu-19|[AMB-BTC](https://binance.com/en/trade/AMB_BTC)|4/0|2.247e-05
Slouching-Havanese-19|[AMB-BTC](https://binance.com/en/trade/AMB_BTC)|4/0|2.247e-05
Slouching-Pekingese-12|[AMB-BTC](https://binance.com/en/trade/AMB_BTC)|4/0|2.247e-05
Leaping-Griffon-8|[AMB-BNB](https://binance.com/en/trade/AMB_BNB)|4/0|0.0152
Leaping-Griffon-9|[AMB-BNB](https://binance.com/en/trade/AMB_BNB)|4/0|0.0152
Leaping-Griffon-10|[AMB-BNB](https://binance.com/en/trade/AMB_BNB)|4/0|0.0152
Supine-Norrbottenspets-12|[AMB-BNB](https://binance.com/en/trade/AMB_BNB)|4/0|0.0152
Supine-Xoloitzcuintli-6|[AMB-BNB](https://binance.com/en/trade/AMB_BNB)|4/0|0.0152
Supine-Griffon-12|[AMB-BNB](https://binance.com/en/trade/AMB_BNB)|4/0|0.0152
Darting-Shiba Inu-9|[AMB-BNB](https://binance.com/en/trade/AMB_BNB)|4/0|0.0152
Darting-Shiba Inu-10|[AMB-BNB](https://binance.com/en/trade/AMB_BNB)|4/0|0.0152
Darting-Norrbottenspets-4|[AMB-ETH](https://binance.com/en/trade/AMB_ETH)|4/0|0.0006297
Crouching-Munchkin-6|[XVG-BTC](https://binance.com/en/trade/XVG_BTC)|4/0|2.33e-06
Crouching-Bandicoot-3|[XVG-BTC](https://binance.com/en/trade/XVG_BTC)|4/0|2.33e-06
Darting-Munchkin-6|[XVG-BTC](https://binance.com/en/trade/XVG_BTC)|4/0|2.33e-06
Darting-Bandicoot-3|[XVG-BTC](https://binance.com/en/trade/XVG_BTC)|4/0|2.33e-06
Crouching-Griffon-15|[IOT-BNB](https://binance.com/en/trade/IOT_BNB)|4/1|0.0572
Crouching-Pekingese-9|[IOT-BNB](https://binance.com/en/trade/IOT_BNB)|4/1|0.0572
Supine-Shiba Inu-13|[IOT-BNB](https://binance.com/en/trade/IOT_BNB)|4/1|0.0572
Supine-Havanese-13|[IOT-BNB](https://binance.com/en/trade/IOT_BNB)|4/1|0.0572
Slouching-Griffon-15|[IOT-BNB](https://binance.com/en/trade/IOT_BNB)|4/1|0.0572
Slouching-Havanese-15|[IOT-BNB](https://binance.com/en/trade/IOT_BNB)|4/1|0.0572
Crouching-Capybara-11|[AMB-BTC](https://binance.com/en/trade/AMB_BTC)|4/1|2.247e-05
Crouching-Shiba Inu-18|[AMB-BTC](https://binance.com/en/trade/AMB_BTC)|4/1|2.247e-05
Leaping-Xoloitzcuintli-3|[AMB-BTC](https://binance.com/en/trade/AMB_BTC)|4/1|2.247e-05
Leaping-Griffon-9|[AMB-BTC](https://binance.com/en/trade/AMB_BTC)|4/1|2.247e-05
Leaping-Griffon-10|[AMB-BTC](https://binance.com/en/trade/AMB_BTC)|4/1|2.247e-05
Leaping-Havanese-14|[AMB-BTC](https://binance.com/en/trade/AMB_BTC)|4/1|2.247e-05
Supine-Capybara-9|[AMB-BTC](https://binance.com/en/trade/AMB_BTC)|4/1|2.247e-05
Supine-Capybara-11|[AMB-BTC](https://binance.com/en/trade/AMB_BTC)|4/1|2.247e-05
Supine-Axolotl-8|[AMB-BTC](https://binance.com/en/trade/AMB_BTC)|4/1|2.247e-05
Supine-Shiba Inu-18|[AMB-BTC](https://binance.com/en/trade/AMB_BTC)|4/1|2.247e-05
Slouching-Capybara-11|[AMB-BTC](https://binance.com/en/trade/AMB_BTC)|4/1|2.247e-05
Slouching-Shiba Inu-18|[AMB-BTC](https://binance.com/en/trade/AMB_BTC)|4/1|2.247e-05
Crouching-Munchkin-7|[SALT-ETH](https://binance.com/en/trade/SALT_ETH)|4/1|0.002102
Leaping-Bandicoot-3|[SALT-ETH](https://binance.com/en/trade/SALT_ETH)|4/1|0.002102
Darting-Munchkin-7|[SALT-ETH](https://binance.com/en/trade/SALT_ETH)|4/1|0.002102
Supine-Shiba Inu-12|[AMB-BNB](https://binance.com/en/trade/AMB_BNB)|4/1|0.0152
Supine-Pekingese-6|[AMB-BNB](https://binance.com/en/trade/AMB_BNB)|4/1|0.0152
Slouching-Basenji-3|[AMB-BNB](https://binance.com/en/trade/AMB_BNB)|8/2|0.0152
Slouching-Basenji-4|[AMB-BNB](https://binance.com/en/trade/AMB_BNB)|4/1|0.0152
Crouching-Xoloitzcuintli-9|[AMB-ETH](https://binance.com/en/trade/AMB_ETH)|4/1|0.0006297
Crouching-Pekingese-9|[AMB-ETH](https://binance.com/en/trade/AMB_ETH)|4/1|0.0006297
Leaping-Xoloitzcuintli-2|[AMB-ETH](https://binance.com/en/trade/AMB_ETH)|4/1|0.0006297
Supine-Pomeranian-8|[AMB-ETH](https://binance.com/en/trade/AMB_ETH)|4/1|0.0006297
Slouching-Xoloitzcuintli-9|[AMB-ETH](https://binance.com/en/trade/AMB_ETH)|4/1|0.0006297
Slouching-Pekingese-9|[AMB-ETH](https://binance.com/en/trade/AMB_ETH)|4/1|0.0006297
Supine-Havanese-11|[AMB-ETH](https://binance.com/en/trade/AMB_ETH)|7/2|0.0006297
Crouching-Jagdterrier-9|[SALT-BTC](https://binance.com/en/trade/SALT_BTC)|7/2|7.5e-05
Darting-Jagdterrier-9|[SALT-BTC](https://binance.com/en/trade/SALT_BTC)|7/2|7.5e-05
Crouching-Norrbottenspets-15|[IOT-BNB](https://binance.com/en/trade/IOT_BNB)|3/0|0.0572
Crouching-Havanese-16|[IOT-BNB](https://binance.com/en/trade/IOT_BNB)|3/0|0.0572
Crouching-Havanese-17|[IOT-BNB](https://binance.com/en/trade/IOT_BNB)|3/0|0.0572
Crouching-Havanese-18|[IOT-BNB](https://binance.com/en/trade/IOT_BNB)|3/0|0.0572
Crouching-Pekingese-10|[IOT-BNB](https://binance.com/en/trade/IOT_BNB)|3/0|0.0572
Crouching-Pekingese-11|[IOT-BNB](https://binance.com/en/trade/IOT_BNB)|3/0|0.0572
Leaping-Norrbottenspets-4|[IOT-BNB](https://binance.com/en/trade/IOT_BNB)|3/0|0.0572
Leaping-Xoloitzcuintli-4|[IOT-BNB](https://binance.com/en/trade/IOT_BNB)|3/0|0.0572
Leaping-Xoloitzcuintli-5|[IOT-BNB](https://binance.com/en/trade/IOT_BNB)|3/0|0.0572
Darting-Capybara-2|[IOT-BNB](https://binance.com/en/trade/IOT_BNB)|3/0|0.0572
Darting-Griffon-7|[IOT-BNB](https://binance.com/en/trade/IOT_BNB)|3/0|0.0572
Slouching-Norrbottenspets-15|[IOT-BNB](https://binance.com/en/trade/IOT_BNB)|3/0|0.0572
Crouching-Norrbottenspets-20|[AMB-BTC](https://binance.com/en/trade/AMB_BTC)|3/0|2.247e-05
Crouching-Griffon-20|[AMB-BTC](https://binance.com/en/trade/AMB_BTC)|3/0|2.247e-05
Crouching-Griffon-21|[AMB-BTC](https://binance.com/en/trade/AMB_BTC)|3/0|2.247e-05
Crouching-Griffon-22|[AMB-BTC](https://binance.com/en/trade/AMB_BTC)|3/0|2.247e-05
Crouching-Shiba Inu-20|[AMB-BTC](https://binance.com/en/trade/AMB_BTC)|3/0|2.247e-05
Crouching-Shiba Inu-21|[AMB-BTC](https://binance.com/en/trade/AMB_BTC)|3/0|2.247e-05
Crouching-Shiba Inu-22|[AMB-BTC](https://binance.com/en/trade/AMB_BTC)|3/0|2.247e-05
Crouching-Havanese-20|[AMB-BTC](https://binance.com/en/trade/AMB_BTC)|3/0|2.247e-05
Crouching-Havanese-21|[AMB-BTC](https://binance.com/en/trade/AMB_BTC)|3/0|2.247e-05
Crouching-Havanese-22|[AMB-BTC](https://binance.com/en/trade/AMB_BTC)|3/0|2.247e-05
Supine-Norrbottenspets-20|[AMB-BTC](https://binance.com/en/trade/AMB_BTC)|3/0|2.247e-05
Supine-Griffon-20|[AMB-BTC](https://binance.com/en/trade/AMB_BTC)|3/0|2.247e-05
Supine-Griffon-21|[AMB-BTC](https://binance.com/en/trade/AMB_BTC)|3/0|2.247e-05
Supine-Griffon-22|[AMB-BTC](https://binance.com/en/trade/AMB_BTC)|3/0|2.247e-05
Supine-Axolotl-9|[AMB-BTC](https://binance.com/en/trade/AMB_BTC)|3/0|2.247e-05
Supine-Shiba Inu-20|[AMB-BTC](https://binance.com/en/trade/AMB_BTC)|3/0|2.247e-05
Supine-Shiba Inu-21|[AMB-BTC](https://binance.com/en/trade/AMB_BTC)|3/0|2.247e-05
Supine-Shiba Inu-22|[AMB-BTC](https://binance.com/en/trade/AMB_BTC)|3/0|2.247e-05
Supine-Havanese-20|[AMB-BTC](https://binance.com/en/trade/AMB_BTC)|3/0|2.247e-05
Supine-Havanese-21|[AMB-BTC](https://binance.com/en/trade/AMB_BTC)|3/0|2.247e-05
Supine-Havanese-22|[AMB-BTC](https://binance.com/en/trade/AMB_BTC)|3/0|2.247e-05
Slouching-Norrbottenspets-20|[AMB-BTC](https://binance.com/en/trade/AMB_BTC)|3/0|2.247e-05
Slouching-Griffon-20|[AMB-BTC](https://binance.com/en/trade/AMB_BTC)|3/0|2.247e-05
Slouching-Griffon-21|[AMB-BTC](https://binance.com/en/trade/AMB_BTC)|3/0|2.247e-05
Slouching-Griffon-22|[AMB-BTC](https://binance.com/en/trade/AMB_BTC)|3/0|2.247e-05
Slouching-Cricket-10|[AMB-BTC](https://binance.com/en/trade/AMB_BTC)|3/0|2.247e-05
Slouching-Shiba Inu-20|[AMB-BTC](https://binance.com/en/trade/AMB_BTC)|3/0|2.247e-05
Slouching-Shiba Inu-21|[AMB-BTC](https://binance.com/en/trade/AMB_BTC)|3/0|2.247e-05
Slouching-Shiba Inu-22|[AMB-BTC](https://binance.com/en/trade/AMB_BTC)|3/0|2.247e-05
Slouching-Havanese-20|[AMB-BTC](https://binance.com/en/trade/AMB_BTC)|3/0|2.247e-05
Slouching-Havanese-21|[AMB-BTC](https://binance.com/en/trade/AMB_BTC)|3/0|2.247e-05
Slouching-Havanese-22|[AMB-BTC](https://binance.com/en/trade/AMB_BTC)|3/0|2.247e-05
Crouching-Jagdterrier-19|[SALT-ETH](https://binance.com/en/trade/SALT_ETH)|3/0|0.002102
Crouching-Jagdterrier-20|[SALT-ETH](https://binance.com/en/trade/SALT_ETH)|3/0|0.002102
Crouching-Affenpinscher-15|[SALT-ETH](https://binance.com/en/trade/SALT_ETH)|3/0|0.002102
Crouching-Affenpinscher-16|[SALT-ETH](https://binance.com/en/trade/SALT_ETH)|3/0|0.002102
Crouching-Munchkin-8|[SALT-ETH](https://binance.com/en/trade/SALT_ETH)|3/0|0.002102
Crouching-Cricket-19|[SALT-ETH](https://binance.com/en/trade/SALT_ETH)|3/0|0.002102
Crouching-Cricket-20|[SALT-ETH](https://binance.com/en/trade/SALT_ETH)|3/0|0.002102
Crouching-Axolotl-19|[SALT-ETH](https://binance.com/en/trade/SALT_ETH)|3/0|0.002102
Crouching-Axolotl-20|[SALT-ETH](https://binance.com/en/trade/SALT_ETH)|3/0|0.002102
Crouching-Pomeranian-15|[SALT-ETH](https://binance.com/en/trade/SALT_ETH)|3/0|0.002102
Crouching-Pomeranian-16|[SALT-ETH](https://binance.com/en/trade/SALT_ETH)|3/0|0.002102
Leaping-Munchkin-7|[SALT-ETH](https://binance.com/en/trade/SALT_ETH)|3/0|0.002102
Leaping-Munchkin-8|[SALT-ETH](https://binance.com/en/trade/SALT_ETH)|3/0|0.002102
Darting-Jagdterrier-19|[SALT-ETH](https://binance.com/en/trade/SALT_ETH)|3/0|0.002102
Darting-Jagdterrier-20|[SALT-ETH](https://binance.com/en/trade/SALT_ETH)|3/0|0.002102
Darting-Affenpinscher-15|[SALT-ETH](https://binance.com/en/trade/SALT_ETH)|3/0|0.002102
Darting-Affenpinscher-16|[SALT-ETH](https://binance.com/en/trade/SALT_ETH)|3/0|0.002102
Darting-Munchkin-8|[SALT-ETH](https://binance.com/en/trade/SALT_ETH)|3/0|0.002102
Darting-Cricket-19|[SALT-ETH](https://binance.com/en/trade/SALT_ETH)|3/0|0.002102
Darting-Cricket-20|[SALT-ETH](https://binance.com/en/trade/SALT_ETH)|3/0|0.002102
