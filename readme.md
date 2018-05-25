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
Generated Fri 25 May 13:42:29 BST 2018

# What's popping, bro?
Recent recommendations by the top performing stategies below. See the [raw price data](tmp/prices.csv)
currency pair|strategy
-|-
SALT-ETH 20.0_roll_average3
SALT-ETH 30.0_roll_average3
SALT-BTC 20.0_roll_average3
SALT-BTC 30.0_roll_average3
XMR-ETH 20.0_roll_average3
XMR-ETH 30.0_roll_average3
# Strategy performance
Strategies are sorted by percentage of orders that returned a profit of at least 5 % within 48 hours. The more orders the greater the confidence in the result.
* 315 pairs
* 3 series of prices
* 24 hours window size
* 48 hours look ahead
* 5784 windows processed
* 3435 orders placed
<pre>
STRATEGY		%	orders
10.0_flicking_down|66.7|3
10.0_rolling_average2|55.4|56
20.0_rolling_average2|55.4|56
30.0_rolling_average2|54.5|55
5.00_new_above_old|53.6|672
20.0_roll_average4|52.4|42
5.00_roll_average4|52.4|42
10.0_roll_average4|52.4|42
5.00_rolling_average2|51.7|60
30.0_roll_average4|51.2|41
30.0_roll_average3|45.5|66
5.00_flicking_up|45.5|209
20.0_roll_average3|45.1|71
10.0_roll_average3|44.6|74
5.00_roll_average3|44.6|74
5.00_stepping_up|44.4|216
5.00_koskosovich|40.0|5
10.0_new_above_old|37.4|107
5.00_flicking_down|37.1|237
5.00_roll_average|36.8|68
5.00_stepping_down|34.9|255
10.0_old_above_new|34.4|154
5.00_old_above_new|32.7|801
10.0_flicking_up|0.0|9
10.0_stepping_down|0.0|4
5.00_steady_rising2|0.0|3
5.00_steady_riser|0.0|3
10.0_roll_average|0.0|1
10.0_stepping_up|0.0|5
5.00_average_comp|0.0|4
</pre>
