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
Generated Sun 27 May 12:38:09 BST 2018

# What's popping, bro?
Recent recommendations by the top performing stategies below. See the [raw price data](prices.csv)

|Currency pair|Strategy|
|---|---|
|I GOT NOTHING|:(|

# Strategy performance
Strategies are sorted by percentage of orders that returned a profit of at least 10 % within 48 hours. The more orders the greater the confidence in the result.
* 315 tradable pairs
* 315 pairs processed
* 48 hours look ahead for order to mature
* 607320 x 24 hour periods processed
* 2088386 orders placed
<pre>
Strategy		%	Orders
30.0_ski_jumping	100.0	2
20.0_ski_jumping	100.0	2
40.0_straddler_1	100.0	1
30.0_rolling_ave_inv1	80.4	97
40.0_average_under	80.0	15
30.0_average_under	76.9	26
40.0_rolling_ave_inv2	76.9	13
30.0_straddler_1	75.0	8
20.0_average_under	69.2	39
10.0_average_under	69.1	81
20.0_rolling_ave_inv1	66.8	184
40.0_rolling_ave_inv1	66.0	53
20.0_rolling_ave_inv2	65.9	138
30.0_flicking_down	63.6	209
30.0_rolling_ave_inv2	61.8	34
10.0_rolling_ave_inv2	61.0	362
40.0_flicking_down	60.4	144
20.0_average_comp2	55.4	92
40.0_stepping_down	55.4	92
10.0_rolling_ave_inv1	53.9	1061
10.0_ski_jumping	50.0	4
30.0_average_comp2	50.0	74
20.0_flicking_down	46.9	520
40.0_average_comp2	46.0	63
30.0_stepping_down	45.0	149
10.0_flicking_down	44.4	4518
5.00_rolling_ave_inv2	44.0	2598
2.50_steady_down	42.4	151
5.00_rolling_ave_inv3	41.2	342
40.0_old_above_new	40.9	286
5.00_average_under	40.7	540
10.0_rolling_ave_inv3	40.6	101
20.0_old_above_new	40.5	3231
10.0_straddler_1	39.6	250
2.50_rolling_ave_inv3	39.4	3017
10.0_stepping_down	39.1	4427
5.00_average_comp2	39.1	4427
2.50_average_under	38.4	3930
5.00_rolling_ave_inv1	37.6	8855
20.0_red_snapper	37.3	225
20.0_nino_nino_1	37.2	6415
40.0_nino_nino_1	36.9	621
20.0_rolling_ave_inv3	36.4	11
2.50_average_inter	35.8	6304
5.00_average_comp	35.1	7180
10.0_stepping_up	34.8	8135
10.0_red_snapper	33.3	904
10.0_flicking_up	33.1	7813
30.0_old_above_new	32.6	816
2.50_average_comp	32.2	35203
5.00_average_inter	32.2	1171
5.00_stepping_up	32.0	36876
10.0_new_above_old	32.0	29457
20.0_new_above_old	31.9	6595
10.0_old_above_new	31.8	24855
10.0_average_comp2	31.7	482
20.0_stepping_down	31.7	482
2.50_rolling_ave_inv2	31.4	20388
5.00_flicking_up	31.0	34649
2.50_ski_jumping	30.8	1137
10.0_rolling_average2	30.5	2323
5.00_rolling_average2	30.5	13059
20.0_stepping_up	30.2	1864
30.0_nino_nino_1	30.0	1660
5.00_straddler_1	29.9	969
5.00_steady_rising2	29.6	456
5.00_steady_riser	29.4	480
2.50_steady_rising2	29.3	19127
10.0_nino_nino_1	29.2	47563
5.00_flicking_down	29.0	31901
5.00_roll_average	28.9	4782
5.00_new_above_old	28.7	84737
20.0_straddler_1	28.6	35
5.00_ski_jumping	28.6	77
2.50_steady_riser	28.3	22528
2.50_flicking_up	28.1	90556
2.50_roll_average	27.9	23660
2.50_stepping_up	27.9	95907
2.50_koskosovich	27.7	5919
2.50_rolling_average2	27.7	48685
5.00_koskosovich	27.6	1766
2.50_average_comp2	27.2	33843
5.00_stepping_down	27.2	33841
10.0_koskosovich	27.1	425
30.0_new_above_old	26.8	2694
10.0_average_comp	26.6	1503
20.0_flicking_up	26.6	1686
2.50_rolling_ave_inv1	26.1	49515
10.0_roll_average	26.0	891
2.50_new_above_old	26.0	150241
5.00_red_snapper	24.2	2019
30.0_koskosovich	23.8	42
20.0_koskosovich	23.7	114
20.0_rolling_average2	23.5	595
2.50_straddler_1	23.4	1838
5.00_old_above_new	23.1	93948
5.00_nino_nino_1	22.7	178304
2.50_flicking_down	22.3	103802
2.50_stepping_down	21.9	108284
40.0_koskosovich	21.7	23
40.0_new_above_old	21.6	1520
20.0_roll_average	21.5	265
2.50_straddler_2	21.2	4936
5.00_straddler_2	21.2	4936
10.0_straddler_2	21.2	4936
20.0_straddler_2	21.2	4936
30.0_straddler_2	21.2	4936
40.0_straddler_2	21.2	4936
30.0_stepping_up	21.1	1004
2.50_red_snapper	21.1	2540
2.50_nino_nino_1	20.8	335719
2.50_old_above_new	20.2	179469
30.0_flicking_up	20.1	877
30.0_rolling_average2	19.7	356
30.0_roll_average	18.9	143
30.0_red_snapper	18.6	59
40.0_flicking_up	18.3	699
40.0_stepping_up	17.6	818
20.0_average_comp	17.3	745
10.0_average_inter	16.9	432
40.0_rolling_average2	16.8	285
30.0_average_comp	16.5	650
40.0_roll_average	15.2	132
40.0_average_comp	14.5	585
20.0_average_inter	14.5	339
40.0_average_inter	13.2	280
30.0_average_inter	12.7	315
40.0_red_snapper	7.7	13
30.0_rolling_ave_inv3	0.0	4
40.0_rolling_ave_inv3	0.0	4
</pre>
