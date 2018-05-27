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
Generated Sun 27 May 09:19:01 BST 2018

# What's popping, bro?
Recent recommendations by the top performing stategies below. See the [raw price data](tmp/prices.csv)

|Currency pair|Strategy|
|---|---|
|I GOT NOTHING|:(|

# Strategy performance
Strategies are sorted by percentage of orders that returned a profit of at least 5 % within 48 hours. The more orders the greater the confidence in the result.
* 315 tradable pairs
* 315 pairs processed
* 48 hours look ahead for order to mature
* 607320 x 24 hour periods processed
* 1968290 orders placed
<pre>
Strategy		%	Orders
30.0_ski_jumping	100.0	2
20.0_ski_jumping	100.0	2
30.0_average_under	76.9	26
30.0_straddler_1	75.0	8
10.0_average_under	74.1	81
20.0_average_under	69.2	39
10.0_flicking_down	68.8	4521
30.0_flicking_down	67.9	209
10.0_straddler_1	65.6	250
20.0_flicking_down	64.6	520
10.0_red_snapper	64.2	904
5.00_straddler_1	60.8	969
20.0_old_above_new	60.8	3231
10.0_stepping_down	60.6	4427
5.00_average_comp2	60.6	4427
20.0_red_snapper	60.0	225
20.0_average_comp2	59.8	92
5.00_steady_rising2	58.5	455
20.0_nino_nino_1	57.9	6418
5.00_steady_riser	57.8	479
5.00_average_comp	57.2	7187
10.0_old_above_new	56.9	24878
10.0_stepping_up	56.9	8141
5.00_average_under	55.9	540
5.00_stepping_up	55.2	36879
5.00_flicking_down	55.1	31922
30.0_stepping_down	55.0	149
5.00_red_snapper	54.1	2019
30.0_average_comp2	54.1	74
10.0_nino_nino_1	53.9	47595
30.0_old_above_new	53.3	816
10.0_new_above_old	53.3	29455
5.00_flicking_up	52.8	34643
5.00_stepping_down	51.7	33860
10.0_flicking_up	51.5	7814
5.00_new_above_old	51.3	84667
5.00_roll_average	50.1	13059
10.0_ski_jumping	50.0	4
20.0_new_above_old	49.9	6599
20.0_stepping_down	49.4	482
10.0_average_comp2	49.4	482
5.00_average_inter	49.4	1177
30.0_nino_nino_1	48.9	1660
20.0_straddler_1	48.6	35
5.00_old_above_new	47.5	94071
20.0_stepping_up	46.8	1870
5.00_nino_nino_1	46.7	178394
5.00_straddler_2	45.6	4936
10.0_straddler_2	45.6	4936
20.0_straddler_2	45.6	4936
30.0_straddler_2	45.6	4936
10.0_roll_average	45.3	2329
5.00_koskosovich	44.1	1767
10.0_average_comp	43.7	1508
30.0_new_above_old	42.7	2700
20.0_flicking_up	42.0	1692
30.0_red_snapper	40.7	59
10.0_koskosovich	40.0	425
5.00_roll_average3	38.3	106073
20.0_roll_average3	38.2	104574
10.0_roll_average3	38.2	105774
30.0_roll_average4	38.2	103706
10.0_roll_average4	38.2	104678
5.00_roll_average4	38.2	104740
30.0_roll_average3	38.2	104226
30.0_rolling_average2	38.2	104128
20.0_roll_average4	38.2	104010
10.0_rolling_average2	38.2	105147
20.0_rolling_average2	38.2	104396
5.00_rolling_average2	38.2	105297
5.00_ski_jumping	37.7	77
20.0_roll_average	37.0	597
30.0_stepping_up	36.6	1006
30.0_flicking_up	34.8	883
30.0_average_comp	34.0	650
20.0_average_comp	33.8	745
20.0_koskosovich	33.3	114
30.0_roll_average	33.1	356
10.0_average_inter	31.0	436
20.0_average_inter	30.4	339
30.0_average_inter	28.9	315
30.0_koskosovich	23.8	42
</pre>
