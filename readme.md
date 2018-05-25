<!-- If this is readme.md it will be overwritten by the build process -->

[![Build Status](https://travis-ci.org/deanturpin/handt.svg?branch=master)](https://travis-ci.org/deanturpin/handt)
[![codecov](https://codecov.io/gh/deanturpin/handt/branch/master/graph/badge.svg)](https://codecov.io/gh/deanturpin/handt)

**History is no indicator of future performance. Don't invest what you can't
afford to lose.**

*Have A Nice Day Trader* is an algorithmic trading platform. Prices are
requested for all currency pairs traded by Binance over the last 80 days. Then a
library of strategies is back-tested over the prices and a strategy summary is
generated. Prices are fetched using the [CryptoCompare
API](https://min-api.cryptocompare.com/).

See the [details](details.md).

---
Generated Fri 25 May 20:56:51 BST 2018

# What's popping, bro?
Recent recommendations by the top performing stategies below. See the [raw price data](tmp/prices.csv)

|Currency pair|Strategy|
|---|---|
|I GOT NOTHING|:(|

# Strategy performance
Strategies are sorted by percentage of orders that returned a profit of at least 5 % within 48 hours. The more orders the greater the confidence in the result.
* 315 pairs
* 3 series of prices
* 24 hours window size
* 48 hours look ahead
* 5784 windows processed
* 24250 orders placed

|Strategy|%|Orders|
|---|---|---|
|10.0_flicking_down|66.7|3|
|5.00_new_above_old|53.3|675|
|5.00_flicking_up|45.0|211|
|5.00_stepping_up|44.4|216|
|20.0_rolling_average2|42.8|2004|
|30.0_rolling_average2|42.7|1997|
|10.0_rolling_average2|42.4|2049|
|5.00_rolling_average2|42.2|2079|
|30.0_roll_average4|40.9|1200|
|20.0_roll_average4|40.9|1200|
|5.00_roll_average4|40.7|1228|
|10.0_roll_average4|40.5|1224|
|5.00_roll_average3|40.4|2133|
|10.0_roll_average3|40.4|2133|
|20.0_roll_average3|40.3|2126|
|30.0_roll_average3|40.3|2115|
|5.00_koskosovich|40.0|5|
|5.00_flicking_down|37.4|238|
|10.0_new_above_old|37.4|107|
|5.00_roll_average|36.8|68|
|5.00_stepping_down|34.9|255|
|10.0_old_above_new|34.4|154|
|5.00_old_above_new|33.1|801|
|10.0_flicking_up|0.0|9|
|10.0_stepping_down|0.0|4|
|5.00_steady_rising2|0.0|3|
|5.00_steady_riser|0.0|3|
|10.0_roll_average|0.0|1|
|10.0_stepping_up|0.0|5|
|5.00_average_comp|0.0|4|
