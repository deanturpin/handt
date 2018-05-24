<!-- If this is readme.md it will be overwritten by the build process -->

[![Build
Status](https://travis-ci.org/deanturpin/handt.svg?branch=master)](https://travis-ci.org/deanturpin/handt)

History is no indicator of future performance. Don't invest what you can't
afford to lose.

**Have A Nice Day Trader** is an algorithmic trading platform. Prices are
requested for all currency pairs traded by Binance, a library of strategies is
then back-tested over the prices and a strategy summary is produced below. See
the [details](details.md).

Prices are fetched using the [CryptoCompare
API](https://min-api.cryptocompare.com/).

Generated Thu 24 May 12:51:49 BST 2018

# What's popping now?
Recent recommendations from the top performing stategies below.
<pre>
ETH-USDT 10.0_red_snapper
</pre>

See the [raw price date](prices.csv).

# Strategy performance
Strategies are sorted by percentage of orders that returned a profit of at least -5 %, the more orders the greater the confidence.
* 24 hours window size
* 315 pairs
* 315 series of prices
* 48 hours look ahead
* 607320 windows processed
<pre>
STRATEGY		%	orders
30.0_ski_jumping	100.0	2
20.0_ski_jumping	100.0	2
30.0_straddler_1	75.0	8
10.0_flicking_down	68.8	4539
30.0_flicking_down	67.9	209
10.0_straddler_1	65.3	248
20.0_flicking_down	64.6	520
10.0_red_snapper	64.1	891
5.00_straddler_1	60.9	952
20.0_old_above_new	60.9	3243
10.0_stepping_down	60.7	4460
20.0_red_snapper	60.0	225
5.00_steady_rising2	59.1	450
5.00_steady_riser	58.6	473
10.0_old_above_new	57.2	24398
5.00_average_comp	56.8	7350
10.0_stepping_up	56.4	8336
5.00_flicking_down	55.3	31469
5.00_stepping_up	55.0	37503
30.0_stepping_down	55.0	149
5.00_red_snapper	54.8	1963
30.0_old_above_new	53.3	816
10.0_new_above_old	53.1	30028
5.00_flicking_up	52.8	35158
5.00_stepping_down	51.9	33382
5.00_new_above_old	51.5	85165
10.0_flicking_up	51.2	7972
5.00_roll_average	50.0	13256
10.0_ski_jumping	50.0	4
20.0_new_above_old	49.5	6691
20.0_stepping_down	49.4	482
5.00_average_inter	49.1	1180
20.0_straddler_1	48.6	35
5.00_old_above_new	47.6	92242
20.0_stepping_up	46.5	1872
5.00_straddler_2	46.3	4844
10.0_straddler_2	46.3	4844
20.0_straddler_2	46.3	4844
30.0_straddler_2	46.3	4844
10.0_roll_average	45.4	2361
5.00_koskosovich	44.3	1799
10.0_average_comp	43.6	1506
30.0_new_above_old	42.4	2727
20.0_flicking_up	42.0	1698
5.00_roll_average3	41.0	281381
5.00_roll_average4	41.0	277970
10.0_rolling_average2	41.0	277023
5.00_rolling_average2	41.0	279800
10.0_roll_average4	41.0	275236
20.0_roll_average3	41.0	263566
10.0_roll_average3	41.0	277087
30.0_rolling_average2	41.0	261265
30.0_roll_average4	41.0	261634
20.0_rolling_average2	41.0	267546
20.0_roll_average4	41.0	266575
30.0_roll_average3	40.9	256426
30.0_red_snapper	40.7	59
10.0_koskosovich	39.8	430
5.00_ski_jumping	38.5	78
20.0_roll_average	36.9	597
30.0_stepping_up	36.6	1006
30.0_flicking_up	34.7	886
30.0_average_comp	34.0	650
20.0_average_comp	33.8	745
30.0_roll_average	33.0	358
20.0_koskosovich	31.9	113
10.0_average_inter	31.0	436
20.0_average_inter	30.4	339
30.0_average_inter	28.9	315
30.0_koskosovich	22.7	44
</pre>
