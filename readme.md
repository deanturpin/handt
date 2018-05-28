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
Generated Mon 28 May 17:46:30 BST 2018
32cc8d4 Don't report price count [skip ci]

# Recent recommendations
Potential trades from the top performing stategies below. See the [raw price data](prices.csv)

|Currency pair|Strategy|
|---|---|
|[ARN_BTC](https://www.binance.com/trade.html?symbol=ARN_BTC)|5.00_rolling_ave_inv1|

# Strategy performance
Strategies are sorted by percentage of orders that returned a profit of at least 4.5 % within 48 hours. The more orders the greater the confidence in the result.
* 328 currency pairs polled
* 48-hour trade window
* 632384 opportunities to trade
* 2160960 orders executed
<pre>
Strategy		%	Orders
30.0_ski_jumping	100.0	2
20.0_ski_jumping	100.0	2
40.0_straddler_1	100.0	14
30.0_straddler_1	100.0	22
40.0_rolling_ave_inv2	88.2	17
20.0_rolling_ave_inv2	86.2	145
30.0_rolling_ave_inv1	84.1	107
20.0_rolling_ave_inv1	83.7	196
10.0_rolling_ave_inv2	81.8	369
40.0_average_under	80.0	15
30.0_rolling_ave_inv2	79.5	39
30.0_average_under	77.8	27
10.0_average_under	77.2	92
10.0_rolling_ave_inv1	76.7	1075
10.0_rolling_ave_inv3	73.8	103
10.0_straddler_1	72.9	306
10.0_flicking_down	72.5	4630
5.00_rolling_ave_inv2	72.5	2639
30.0_flicking_down	72.5	229
20.0_average_under	72.1	43
40.0_rolling_ave_inv1	71.7	60
20.0_straddler_1	71.2	52
20.0_flicking_down	69.9	548
20.0_red_snapper	68.8	263
10.0_red_snapper	67.6	1292
5.00_rolling_ave_inv1	67.5	9015
40.0_flicking_down	67.3	162
40.0_red_snapper	66.7	36
5.00_rolling_ave_inv3	66.6	341
2.50_rolling_ave_inv3	66.5	3040
2.50_average_under	65.6	3965
40.0_stepping_down	65.4	107
20.0_average_comp2	65.4	107
20.0_old_above_new	65.0	3305
5.00_average_comp2	63.9	4495
10.0_stepping_down	63.9	4495
5.00_straddler_1	63.0	1421
30.0_stepping_down	61.8	170
5.00_steady_rising2	61.7	499
20.0_nino_nino_1	61.7	6471
2.50_rolling_ave_inv2	61.4	20767
2.50_steady_down	61.2	160
5.00_average_comp	61.1	7131
30.0_red_snapper	61.0	82
10.0_old_above_new	60.9	25485
10.0_stepping_up	60.8	8083
5.00_steady_riser	60.7	537
30.0_old_above_new	60.4	858
5.00_average_under	60.3	557
2.50_average_inter	59.9	6309
40.0_old_above_new	59.3	322
5.00_flicking_down	59.0	32663
2.50_average_comp	58.6	35864
30.0_average_comp2	58.5	82
5.00_stepping_up	58.4	37576
10.0_nino_nino_1	57.8	48232
10.0_new_above_old	56.5	29949
5.00_red_snapper	56.0	3067
5.00_flicking_up	55.8	35243
2.50_rolling_ave_inv1	55.7	50540
5.00_stepping_down	55.5	34707
2.50_average_comp2	55.5	34709
10.0_average_comp2	54.6	511
20.0_stepping_down	54.6	511
10.0_flicking_up	54.5	7769
30.0_nino_nino_1	54.5	1693
2.50_steady_rising2	54.1	20649
5.00_new_above_old	54.0	87291
2.50_straddler_1	53.9	2819
20.0_rolling_ave_inv3	53.8	13
40.0_average_comp2	53.7	67
2.50_stepping_up	53.7	98907
20.0_new_above_old	53.2	6506
2.50_ski_jumping	53.2	1166
2.50_flicking_up	53.1	93323
5.00_rolling_average2	52.9	13180
2.50_steady_riser	52.9	24468
40.0_nino_nino_1	52.6	656
5.00_average_inter	52.4	1155
2.50_rolling_average2	51.5	49729
2.50_new_above_old	51.3	155812
5.00_old_above_new	51.1	95780
2.50_roll_average	50.9	24027
20.0_stepping_up	50.9	1833
5.00_nino_nino_1	50.2	181191
10.0_ski_jumping	50.0	4
5.00_roll_average	50.0	4808
2.50_flicking_down	49.9	105821
2.50_koskosovich	49.2	6012
2.50_red_snapper	49.0	4023
2.50_stepping_down	48.6	110631
10.0_average_comp	47.8	1482
10.0_rolling_average2	47.5	2297
5.00_koskosovich	47.0	1757
2.50_nino_nino_1	46.8	344211
2.50_old_above_new	46.6	184134
30.0_straddler_2	46.2	8008
5.00_straddler_2	46.2	8008
2.50_straddler_2	46.2	8008
20.0_straddler_2	46.2	8008
40.0_straddler_2	46.2	8008
10.0_straddler_2	46.2	8008
30.0_new_above_old	46.1	2643
20.0_flicking_up	45.0	1664
10.0_koskosovich	41.1	418
30.0_stepping_up	41.0	988
10.0_roll_average	40.0	874
30.0_rolling_ave_inv3	40.0	5
40.0_rolling_ave_inv3	40.0	5
40.0_new_above_old	39.6	1495
20.0_roll_average	38.9	265
30.0_average_comp	38.5	650
30.0_flicking_up	38.4	874
20.0_rolling_average2	38.4	591
20.0_average_comp	38.1	741
40.0_stepping_up	38.0	806
40.0_flicking_up	37.9	699
40.0_average_comp	37.1	585
5.00_ski_jumping	36.7	79
30.0_roll_average	35.7	143
30.0_rolling_average2	35.1	356
10.0_average_inter	34.0	426
20.0_average_inter	33.3	339
40.0_roll_average	33.3	132
40.0_rolling_average2	33.3	285
20.0_koskosovich	33.3	114
40.0_average_inter	32.1	280
30.0_average_inter	31.4	315
30.0_koskosovich	23.8	42
40.0_koskosovich	21.7	23
</pre>
