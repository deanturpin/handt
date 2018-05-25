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
Generated Fri 25 May 10:29:30 BST 2018

# What's popping, bro?
Recent recommendations by the top performing stategies below. See the [raw price data](tmp/prices.csv)
<pre>
WABI-BTC 5.00_steady_rising2
</pre>
# Strategy performance
Strategies are sorted by percentage of orders that returned a profit of at least 5 % within 48 hours. The more orders the greater the confidence in the result.
* 315 pairs
* 315 series of prices
* 24 hours window size
* 48 hours look ahead
* 607320 windows processed
<pre>
STRATEGY		%	orders
30.0_ski_jumping	100.0	2
20.0_ski_jumping	100.0	2
30.0_straddler_1	75.0	8
10.0_flicking_down	68.6	4516
30.0_flicking_down	67.9	209
10.0_straddler_1	65.3	248
20.0_flicking_down	64.6	520
10.0_red_snapper	64.1	891
5.00_straddler_1	60.8	954
20.0_old_above_new	60.7	3232
10.0_stepping_down	60.6	4445
20.0_red_snapper	60.0	225
5.00_steady_rising2	59.1	450
5.00_steady_riser	58.6	473
5.00_average_comp	57.2	7245
10.0_stepping_up	56.8	8210
10.0_old_above_new	56.6	24432
5.00_stepping_up	55.2	37024
30.0_stepping_down	55.0	149
5.00_flicking_down	54.9	31590
5.00_red_snapper	54.2	1984
30.0_old_above_new	53.3	816
10.0_new_above_old	53.3	29618
5.00_flicking_up	52.9	34743
5.00_stepping_down	51.6	33309
5.00_new_above_old	51.5	84462
10.0_flicking_up	51.5	7872
5.00_roll_average	50.1	13106
10.0_ski_jumping	50.0	4
20.0_new_above_old	49.8	6616
20.0_stepping_down	49.4	482
5.00_average_inter	49.1	1179
20.0_straddler_1	48.6	35
5.00_old_above_new	47.1	93002
20.0_stepping_up	46.6	1861
30.0_straddler_2	46.0	4874
5.00_straddler_2	46.0	4874
10.0_straddler_2	46.0	4874
20.0_straddler_2	46.0	4874
10.0_roll_average	45.5	2347
5.00_koskosovich	44.3	1777
10.0_average_comp	43.5	1503
30.0_new_above_old	42.7	2700
20.0_flicking_up	42.0	1692
30.0_red_snapper	40.7	59
30.0_roll_average4	40.4	179775
5.00_rolling_average2	40.4	189631
10.0_rolling_average2	40.4	188481
5.00_roll_average4	40.4	185489
10.0_roll_average4	40.4	184289
5.00_roll_average3	40.4	189545
30.0_rolling_average2	40.4	184144
10.0_roll_average3	40.3	188105
20.0_roll_average4	40.3	181874
20.0_rolling_average2	40.3	186180
20.0_roll_average3	40.3	184498
30.0_roll_average3	40.3	181491
10.0_koskosovich	39.8	430
5.00_ski_jumping	37.7	77
20.0_roll_average	36.9	597
30.0_stepping_up	36.6	1006
30.0_flicking_up	34.7	885
30.0_average_comp	34.0	650
20.0_average_comp	33.8	745
30.0_roll_average	33.0	358
20.0_koskosovich	31.9	113
10.0_average_inter	31.0	436
20.0_average_inter	30.4	339
30.0_average_inter	28.9	315
30.0_koskosovich	22.7	44
</pre>
