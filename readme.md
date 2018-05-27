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
Generated Sun 27 May 22:12:29 BST 2018

# Recent recommendations
Recommendations by the top performing stategies below. See the [raw price data](prices.csv)

|Currency pair|Strategy|
|---|---|
|I GOT NOTHING|:(|

# Strategy performance
Strategies are sorted by percentage of orders that returned a profit of at least 6 % within 48 hours. The more orders the greater the confidence in the result.
* 315 tradable pairs
* 315 pairs tested
* 48 hours look ahead (for order to mature)
* 607320 x 24-hour periods tested
* 2085913 trades
<pre>
Strategy		%	Trades
30.0_ski_jumping	100.0	2
20.0_ski_jumping	100.0	2
40.0_straddler_1	100.0	1
30.0_rolling_ave_inv1	80.4	97
40.0_average_under	80.0	15
20.0_rolling_ave_inv2	79.0	138
20.0_rolling_ave_inv1	77.7	184
30.0_average_under	76.9	26
40.0_rolling_ave_inv2	76.9	13
10.0_rolling_ave_inv2	76.2	362
30.0_straddler_1	75.0	8
10.0_average_under	74.1	81
10.0_rolling_ave_inv1	69.5	1061
20.0_average_under	69.2	39
30.0_rolling_ave_inv2	67.6	34
30.0_flicking_down	67.0	209
40.0_rolling_ave_inv1	66.0	53
5.00_rolling_ave_inv2	64.2	2600
10.0_flicking_down	63.7	4518
40.0_flicking_down	62.5	144
10.0_rolling_ave_inv3	62.4	101
10.0_straddler_1	60.8	250
40.0_stepping_down	59.8	92
20.0_average_comp2	59.8	92
20.0_flicking_down	59.6	520
5.00_rolling_ave_inv3	59.0	339
2.50_rolling_ave_inv3	58.6	3014
2.50_steady_down	58.2	146
10.0_red_snapper	58.1	904
5.00_rolling_ave_inv1	57.6	8844
2.50_average_under	56.4	3925
5.00_average_comp2	56.2	4427
10.0_stepping_down	56.2	4427
20.0_red_snapper	55.6	225
20.0_old_above_new	55.5	3231
5.00_straddler_1	54.2	966
30.0_average_comp2	54.1	74
20.0_nino_nino_1	52.8	6402
5.00_average_comp	52.4	7172
10.0_stepping_up	52.0	8126
5.00_average_under	51.9	540
2.50_average_inter	51.8	6295
30.0_stepping_down	51.7	149
2.50_rolling_ave_inv2	51.6	20316
5.00_steady_rising2	51.3	456
10.0_old_above_new	51.1	24820
5.00_steady_riser	51.0	480
40.0_average_comp2	50.8	63
10.0_ski_jumping	50.0	4
2.50_average_comp	49.7	35203
5.00_stepping_up	49.4	36877
5.00_flicking_down	48.8	31826
10.0_new_above_old	48.1	29431
40.0_old_above_new	47.9	286
10.0_nino_nino_1	47.8	47451
5.00_flicking_up	47.5	34647
10.0_flicking_up	47.3	7792
5.00_red_snapper	47.2	2017
30.0_old_above_new	47.2	816
2.50_steady_rising2	46.5	19162
20.0_new_above_old	45.7	6573
20.0_straddler_1	45.7	35
5.00_new_above_old	45.6	84738
2.50_average_comp2	45.6	33769
5.00_stepping_down	45.6	33767
5.00_rolling_average2	45.6	13055
2.50_steady_riser	45.5	22564
2.50_straddler_1	45.5	1836
2.50_ski_jumping	45.4	1136
2.50_rolling_ave_inv1	45.3	49326
5.00_average_inter	45.3	1164
2.50_stepping_up	45.1	95889
2.50_flicking_up	44.7	90544
20.0_stepping_down	44.2	482
10.0_average_comp2	44.2	482
40.0_nino_nino_1	44.1	621
30.0_nino_nino_1	43.6	1659
2.50_rolling_average2	43.5	48694
2.50_roll_average	43.3	23650
20.0_stepping_up	43.2	1844
5.00_roll_average	42.9	4784
2.50_new_above_old	42.7	150418
2.50_koskosovich	42.0	5923
2.50_red_snapper	41.9	2538
10.0_rolling_average2	41.7	2319
5.00_old_above_new	41.2	93648
5.00_koskosovich	40.8	1764
5.00_nino_nino_1	40.3	177895
2.50_flicking_down	39.9	103436
10.0_average_comp	39.8	1484
30.0_new_above_old	39.4	2674
30.0_straddler_2	39.2	4933
20.0_straddler_2	39.2	4933
10.0_straddler_2	39.2	4933
5.00_straddler_2	39.2	4933
40.0_straddler_2	39.2	4933
2.50_straddler_2	39.2	4933
2.50_stepping_down	38.9	108119
20.0_flicking_up	38.5	1680
10.0_koskosovich	37.9	422
2.50_nino_nino_1	37.5	335635
2.50_old_above_new	37.2	179036
20.0_rolling_ave_inv3	36.4	11
30.0_red_snapper	35.6	59
10.0_roll_average	35.5	888
5.00_ski_jumping	35.1	77
20.0_rolling_average2	32.8	595
40.0_new_above_old	32.8	1502
30.0_stepping_up	32.7	988
20.0_roll_average	30.6	265
30.0_flicking_up	30.5	875
20.0_koskosovich	29.8	114
40.0_flicking_up	29.2	699
40.0_stepping_up	29.2	806
20.0_average_comp	28.9	741
30.0_average_comp	28.3	650
30.0_rolling_average2	27.8	356
30.0_roll_average	27.3	143
40.0_average_comp	26.7	585
10.0_average_inter	26.3	426
40.0_rolling_average2	25.3	285
40.0_roll_average	24.2	132
20.0_average_inter	24.2	339
30.0_koskosovich	23.8	42
40.0_average_inter	23.2	280
30.0_average_inter	22.2	315
40.0_koskosovich	21.7	23
40.0_red_snapper	7.7	13
40.0_rolling_ave_inv3	0.0	4
30.0_rolling_ave_inv3	0.0	4
</pre>
