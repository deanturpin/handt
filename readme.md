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

Generated Mon 1 Oct 10:10:51 GMT 2018
* 322 currency pairs
* 1,062,600 strategy/pair combinations
* 1,952,817,717 backtests

# Current prospects
Prospects based on prices from the last 24 hours.

Strategy|Pair|Good/Bad|Spot|Last (days)
---|---|---|---|---
Darting-Cricket-9|[RDN*-BTC](https://binance.com/en/trade/RDN_BTC)|7/1|7.442e-05|10
Darting-Axolotl-9|[RDN*-BTC](https://binance.com/en/trade/RDN_BTC)|7/1|7.442e-05|10
Crouching-Jagdterrier-9|[RDN*-BTC](https://binance.com/en/trade/RDN_BTC)|6/0|7.442e-05|10
Darting-Jagdterrier-9|[RDN*-BTC](https://binance.com/en/trade/RDN_BTC)|6/0|7.442e-05|10
Darting-Pekingese-7|[CHAT-BTC](https://binance.com/en/trade/CHAT_BTC)|6/1|3.62e-06|10
Darting-Pomeranian-11|[CHAT-ETH](https://binance.com/en/trade/CHAT_ETH)|5/0|0.0001034|10
Darting-Havanese-18|[CHAT-BTC](https://binance.com/en/trade/CHAT_BTC)|5/1|3.62e-06|9
Leaping-Sphynx-2|[REQ-ETH](https://binance.com/en/trade/REQ_ETH)|4/0|0.0002032|14
Darting-Pekingese-7|[VIA-BNB](https://binance.com/en/trade/VIA_BNB)|4/1|0.06613|14
Crouching-Axolotl-9|[RDN*-BTC](https://binance.com/en/trade/RDN_BTC)|7/2|7.442e-05|10
Darting-Pomeranian-10|[CHAT-ETH](https://binance.com/en/trade/CHAT_ETH)|7/2|0.0001034|10

# 80-day backtest
The results are ordered by success which is measured using the proportion of
good to bad trades.

Strategy|Pair|Good/Bad|Spot
---|---|---|---
Supine-Pomeranian-6|[ZRX-ETH](https://binance.com/en/trade/ZRX_ETH)|10/0|0.002758
Crouching-Axolotl-10|[VIBE-BTC](https://binance.com/en/trade/VIBE_BTC)|11/1|1.183e-05
Crouching-Xoloitzcuintli-6|[BCPT-ETH](https://binance.com/en/trade/BCPT_ETH)|9/0|0.0004062
Slouching-Xoloitzcuintli-6|[BCPT-ETH](https://binance.com/en/trade/BCPT_ETH)|9/0|0.0004062
Slouching-Pekingese-6|[BCPT-ETH](https://binance.com/en/trade/BCPT_ETH)|9/0|0.0004062
Supine-Pomeranian-8|[MTH-BTC](https://binance.com/en/trade/MTH_BTC)|10/1|4.46e-06
Crouching-Pomeranian-9|[QLC-ETH](https://binance.com/en/trade/QLC_ETH)|10/1|0.000235
Supine-Havanese-11|[ZRX-ETH](https://binance.com/en/trade/ZRX_ETH)|9/0|0.002758
Crouching-Havanese-16|[ONT-BNB](https://binance.com/en/trade/ONT_BNB)|9/1|0.1996
Crouching-Pekingese-10|[ONT-BNB](https://binance.com/en/trade/ONT_BNB)|8/0|0.1996
Supine-Capybara-5|[APPC-ETH](https://binance.com/en/trade/APPC_ETH)|8/0|0.0005052
Supine-Havanese-14|[ZRX-BTC](https://binance.com/en/trade/ZRX_BTC)|8/1|9.678e-05
Supine-Pekingese-7|[RCN-ETH](https://binance.com/en/trade/RCN_ETH)|8/1|0.0001198
Leaping-Axolotl-9|[TRIG-ETH](https://binance.com/en/trade/TRIG_ETH)|8/1|0.001048
Leaping-Havanese-9|[TRIG-ETH](https://binance.com/en/trade/TRIG_ETH)|8/1|0.001048
Supine-Xoloitzcuintli-8|[MTH-BTC](https://binance.com/en/trade/MTH_BTC)|8/1|4.46e-06
Supine-Pomeranian-9|[MTH-BTC](https://binance.com/en/trade/MTH_BTC)|8/1|4.46e-06
Crouching-Havanese-14|[GVT-BTC](https://binance.com/en/trade/GVT_BTC)|8/1|0.001383
Crouching-Havanese-17|[CDT-ETH](https://binance.com/en/trade/CDT_ETH)|8/1|6.669e-05
Darting-Pomeranian-6|[RDN*-BTC](https://binance.com/en/trade/RDN_BTC)|7/0|7.442e-05
Crouching-Cricket-16|[QLC-BNB](https://binance.com/en/trade/QLC_BNB)|7/0|0.005531
Crouching-Havanese-15|[LSK-BTC](https://binance.com/en/trade/LSK_BTC)|7/0|0.0005029
Supine-Griffon-16|[MTH-BTC](https://binance.com/en/trade/MTH_BTC)|7/0|4.46e-06
Supine-Havanese-12|[ZRX-ETH](https://binance.com/en/trade/ZRX_ETH)|7/0|0.002758
Crouching-Pekingese-11|[CND-BTC](https://binance.com/en/trade/CND_BTC)|7/0|3.27e-06
Darting-Cricket-9|[RDN*-BTC](https://binance.com/en/trade/RDN_BTC)|7/1|7.442e-05
Darting-Axolotl-9|[RDN*-BTC](https://binance.com/en/trade/RDN_BTC)|7/1|7.442e-05
Slouching-Havanese-16|[ONT-BNB](https://binance.com/en/trade/ONT_BNB)|7/1|0.1996
Crouching-Pomeranian-10|[NEO-USDT](https://binance.com/en/trade/NEO_USDT)|7/1|18.79
Crouching-Munchkin-5|[VIB-BTC](https://binance.com/en/trade/VIB_BTC)|7/1|5.95e-06
Darting-Munchkin-5|[VIB-BTC](https://binance.com/en/trade/VIB_BTC)|7/1|5.95e-06
Crouching-Griffon-14|[ZRX-BTC](https://binance.com/en/trade/ZRX_BTC)|7/1|9.678e-05
Crouching-Shiba Inu-14|[ZRX-BTC](https://binance.com/en/trade/ZRX_BTC)|7/1|9.678e-05
Supine-Griffon-14|[ZRX-BTC](https://binance.com/en/trade/ZRX_BTC)|7/1|9.678e-05
Supine-Shiba Inu-14|[ZRX-BTC](https://binance.com/en/trade/ZRX_BTC)|7/1|9.678e-05
Slouching-Griffon-14|[ZRX-BTC](https://binance.com/en/trade/ZRX_BTC)|7/1|9.678e-05
Slouching-Shiba Inu-14|[ZRX-BTC](https://binance.com/en/trade/ZRX_BTC)|7/1|9.678e-05
Slouching-Havanese-14|[ZRX-BTC](https://binance.com/en/trade/ZRX_BTC)|7/1|9.678e-05
Darting-Pekingese-7|[WTC-BTC](https://binance.com/en/trade/WTC_BTC)|7/1|0.0004452
Crouching-Cricket-9|[ADX-ETH](https://binance.com/en/trade/ADX_ETH)|7/1|0.0008754
Darting-Cricket-9|[ADX-ETH](https://binance.com/en/trade/ADX_ETH)|7/1|0.0008754
Crouching-Havanese-15|[GVT-BTC](https://binance.com/en/trade/GVT_BTC)|7/1|0.001383
Crouching-Basenji-8|[CDT-ETH](https://binance.com/en/trade/CDT_ETH)|7/1|6.669e-05
Darting-Basenji-8|[CDT-ETH](https://binance.com/en/trade/CDT_ETH)|7/1|6.669e-05
Crouching-Havanese-19|[CND-BTC](https://binance.com/en/trade/CND_BTC)|7/1|3.27e-06
Crouching-Havanese-20|[CND-BTC](https://binance.com/en/trade/CND_BTC)|7/1|3.27e-06
Crouching-Jagdterrier-9|[RDN*-BTC](https://binance.com/en/trade/RDN_BTC)|6/0|7.442e-05
Crouching-Affenpinscher-6|[RDN*-BTC](https://binance.com/en/trade/RDN_BTC)|6/0|7.442e-05
Leaping-Jagdterrier-9|[RDN*-BTC](https://binance.com/en/trade/RDN_BTC)|6/0|7.442e-05
Leaping-Affenpinscher-6|[RDN*-BTC](https://binance.com/en/trade/RDN_BTC)|6/0|7.442e-05
Darting-Jagdterrier-9|[RDN*-BTC](https://binance.com/en/trade/RDN_BTC)|6/0|7.442e-05
Darting-Affenpinscher-6|[RDN*-BTC](https://binance.com/en/trade/RDN_BTC)|6/0|7.442e-05
Supine-Norrbottenspets-16|[AMB-BTC](https://binance.com/en/trade/AMB_BTC)|6/0|2.252e-05
Crouching-Basenji-6|[WAVES-ETH](https://binance.com/en/trade/WAVES_ETH)|6/0|0.009535
Darting-Basenji-6|[WAVES-ETH](https://binance.com/en/trade/WAVES_ETH)|6/0|0.009535
Darting-Pekingese-6|[WAVES-ETH](https://binance.com/en/trade/WAVES_ETH)|6/0|0.009535
Crouching-Xoloitzcuintli-10|[ONT-BNB](https://binance.com/en/trade/ONT_BNB)|6/0|0.1996
Crouching-Havanese-19|[ONT-BNB](https://binance.com/en/trade/ONT_BNB)|6/0|0.1996
Crouching-Havanese-20|[ONT-BNB](https://binance.com/en/trade/ONT_BNB)|6/0|0.1996
Supine-Pekingese-10|[ONT-BNB](https://binance.com/en/trade/ONT_BNB)|6/0|0.1996
Slouching-Xoloitzcuintli-10|[ONT-BNB](https://binance.com/en/trade/ONT_BNB)|6/0|0.1996
Slouching-Pekingese-10|[ONT-BNB](https://binance.com/en/trade/ONT_BNB)|6/0|0.1996
Supine-Griffon-15|[MTH-ETH](https://binance.com/en/trade/MTH_ETH)|6/0|0.0001279
Supine-Griffon-16|[MTH-ETH](https://binance.com/en/trade/MTH_ETH)|6/0|0.0001279
Supine-Griffon-17|[MTH-ETH](https://binance.com/en/trade/MTH_ETH)|6/0|0.0001279
Supine-Havanese-16|[MTH-ETH](https://binance.com/en/trade/MTH_ETH)|6/0|0.0001279
Supine-Havanese-17|[MTH-ETH](https://binance.com/en/trade/MTH_ETH)|6/0|0.0001279
Supine-Capybara-6|[APPC-ETH](https://binance.com/en/trade/APPC_ETH)|6/0|0.0005052
Supine-Badger-3|[APPC-ETH](https://binance.com/en/trade/APPC_ETH)|6/0|0.0005052
Supine-Pomeranian-9|[AION-BNB](https://binance.com/en/trade/AION_BNB)|6/0|0.04307
Supine-Cricket-5|[ZRX-BTC](https://binance.com/en/trade/ZRX_BTC)|6/0|9.678e-05
Leaping-Griffon-4|[RCN-BTC](https://binance.com/en/trade/RCN_BTC)|6/0|4.18e-06
Leaping-Griffon-5|[RCN-BTC](https://binance.com/en/trade/RCN_BTC)|6/0|4.18e-06
