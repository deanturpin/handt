<!-- If this is readme.md it will be overwritten by the build process -->

[![Build Status](https://travis-ci.org/deanturpin/handt.svg?branch=master)](https://travis-ci.org/deanturpin/handt)
[![codecov](https://codecov.io/gh/deanturpin/handt/branch/master/graph/badge.svg)](https://codecov.io/gh/deanturpin/handt)

**History is no indicator of future performance. Don't invest what you can't
afford to lose.**

*Have A Nice Day Trader* is an algorithmic trading platform. Prices are
requested for all currency pairs traded by Binance over the last 80 days. Then a
library of strategies is back-tested over the prices and a strategy summary is
generated. Prices are fetched using the [CryptoCompare
API](https://min-api.cryptocompare.com/). See the [details](details.md).

---
Generated Mon 28 May 09:59:02 BST 2018

# Recent recommendations
Potential trades from the top performing stategies below. See the [raw price data](prices.csv)

|Currency pair|Strategy|
|---|---|
|I GOT NOTHING|:(|

# Strategy performance
Strategies are sorted by percentage of orders that returned a profit of at least 6 % within 48 hours. The more orders the greater the confidence in the result.
* 328 tradable pairs
* 328 pairs tested
* 48-hour trade window
* 632384 opportunities to trade
* 2166757 trades
<pre>
Strategy		%	Trades
30.0_ski_jumping	100.0	2
20.0_ski_jumping	100.0	2
40.0_straddler_1	100.0	14
30.0_straddler_1	90.9	22
40.0_rolling_ave_inv2	82.4	17
30.0_rolling_ave_inv1	82.2	107
40.0_average_under	80.0	15
20.0_rolling_ave_inv2	80.0	145
20.0_rolling_ave_inv1	79.1	196
30.0_average_under	77.8	27
10.0_average_under	77.2	92
10.0_rolling_ave_inv2	76.7	369
20.0_average_under	72.1	43
30.0_rolling_ave_inv2	71.8	39
40.0_rolling_ave_inv1	70.0	60
30.0_flicking_down	69.9	229
10.0_rolling_ave_inv1	69.9	1075
40.0_red_snapper	66.7	36
40.0_flicking_down	66.7	162
10.0_straddler_1	66.0	306
20.0_average_comp2	65.4	107
40.0_stepping_down	65.4	107
10.0_flicking_down	64.3	4636
5.00_rolling_ave_inv2	64.0	2644
20.0_straddler_1	63.5	52
10.0_rolling_ave_inv3	63.1	103
20.0_red_snapper	62.0	263
20.0_flicking_down	61.7	548
5.00_rolling_ave_inv3	59.2	341
30.0_average_comp2	58.5	82
2.50_rolling_ave_inv3	58.5	3044
30.0_stepping_down	57.6	170
5.00_rolling_ave_inv1	57.6	9043
10.0_red_snapper	57.4	1292
10.0_stepping_down	56.6	4501
5.00_average_comp2	56.6	4501
20.0_old_above_new	56.6	3306
2.50_average_under	56.3	3974
2.50_steady_down	54.4	160
40.0_old_above_new	54.0	322
40.0_average_comp2	53.7	67
30.0_red_snapper	53.7	82
20.0_nino_nino_1	53.4	6473
5.00_average_under	53.3	557
5.00_straddler_1	53.0	1421
5.00_average_comp	52.6	7181
10.0_stepping_up	52.3	8138
2.50_average_inter	52.3	6326
5.00_steady_rising2	51.5	499
2.50_rolling_ave_inv2	51.4	20852
10.0_old_above_new	51.2	25564
5.00_steady_riser	51.0	537
30.0_old_above_new	50.2	858
10.0_ski_jumping	50.0	4
2.50_average_comp	49.7	35965
5.00_stepping_up	49.5	37678
5.00_flicking_down	48.8	32779
10.0_new_above_old	48.2	30023
10.0_nino_nino_1	48.0	48364
5.00_flicking_up	47.6	35309
10.0_flicking_up	47.6	7794
40.0_nino_nino_1	47.4	656
10.0_average_comp2	47.4	511
20.0_stepping_down	47.4	511
20.0_rolling_ave_inv3	46.2	13
20.0_new_above_old	45.9	6538
5.00_rolling_average2	45.7	13201
2.50_average_comp2	45.7	34812
5.00_stepping_down	45.7	34810
5.00_average_inter	45.6	1155
2.50_steady_rising2	45.6	20660
30.0_nino_nino_1	45.4	1693
5.00_new_above_old	45.3	87367
2.50_rolling_ave_inv1	45.1	50755
2.50_ski_jumping	45.0	1171
2.50_stepping_up	44.7	99012
2.50_steady_riser	44.5	24481
5.00_red_snapper	44.4	3096
2.50_flicking_up	44.4	93411
2.50_roll_average	43.3	24073
2.50_rolling_average2	43.3	49788
20.0_stepping_up	43.2	1843
2.50_straddler_1	43.1	2833
5.00_roll_average	43.0	4814
2.50_new_above_old	42.3	155849
2.50_koskosovich	42.0	6015
10.0_rolling_average2	41.7	2306
5.00_koskosovich	41.0	1761
5.00_old_above_new	41.0	96346
5.00_nino_nino_1	40.1	181880
10.0_average_comp	39.8	1484
2.50_flicking_down	39.7	106286
30.0_new_above_old	39.6	2654
2.50_stepping_down	38.7	111143
20.0_flicking_up	38.5	1672
2.50_red_snapper	37.9	4062
10.0_koskosovich	37.8	418
2.50_nino_nino_1	37.1	344862
2.50_old_above_new	36.8	184868
10.0_straddler_2	36.1	8034
2.50_straddler_2	36.1	8034
5.00_straddler_2	36.1	8034
20.0_straddler_2	36.1	8034
30.0_straddler_2	36.1	8034
40.0_straddler_2	36.1	8034
10.0_roll_average	35.3	878
5.00_ski_jumping	34.2	79
40.0_new_above_old	32.9	1497
20.0_rolling_average2	32.8	591
30.0_stepping_up	32.7	988
20.0_roll_average	30.6	265
30.0_flicking_up	30.5	874
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
30.0_rolling_ave_inv3	20.0	5
40.0_rolling_ave_inv3	20.0	5
</pre>
