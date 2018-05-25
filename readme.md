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

See the [details](details.md) and the [raw prices](tmp/prices.csv).

---
Generated Fri 25 May 06:58:50 BST 2018

# What's popping, bro?
Recent recommendations by the top performing stategies below.
<pre>
I GOT NOTHING :(
</pre>
# Strategy performance
Strategies are sorted by percentage of orders that returned a profit of at least 5 % within 48 hours.The more orders the greater the confidence in the result.
* 315 pairs
* 3 series of prices
* 24 hours window size
* 48 hours look ahead
* 5784 windows processed
<pre>
STRATEGY		%	orders
10.0_flicking_down	66.7	3
5.00_new_above_old	53.6	672
5.00_flicking_up	45.5	209
5.00_stepping_up	44.4	216
5.00_roll_average4	40.7	4081
30.0_roll_average4	40.7	4081
20.0_roll_average4	40.7	4081
10.0_roll_average4	40.7	4081
20.0_rolling_average2	40.6	4085
30.0_rolling_average2	40.6	4085
10.0_rolling_average2	40.6	4085
5.00_rolling_average2	40.6	4089
5.00_koskosovich	40.0	5
30.0_roll_average3	38.3	4566
20.0_roll_average3	38.3	4570
5.00_roll_average3	38.3	4574
10.0_roll_average3	38.3	4572
10.0_new_above_old	37.4	107
5.00_flicking_down	37.3	236
5.00_roll_average	36.8	68
10.0_old_above_new	35.6	149
5.00_stepping_down	35.5	251
5.00_old_above_new	33.1	795
10.0_flicking_up	0.0	9
10.0_stepping_down	0.0	4
5.00_steady_rising2	0.0	3
5.00_steady_riser	0.0	3
10.0_roll_average	0.0	1
10.0_stepping_up	0.0	5
5.00_average_comp	0.0	4
</pre>
