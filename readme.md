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
Generated Mon 28 May 12:35:12 BST 2018

# Recent recommendations
Potential trades from the top performing stategies below. See the [raw price data](prices.csv)

|Currency pair|Strategy|
|---|---|
|[XRB_BTC](https://www.binance.com/trade.html?symbol=XRB_BTC)|5.00_rolling_ave_inv1|
|[BCPT_BTC](https://www.binance.com/trade.html?symbol=BCPT_BTC)|5.00_rolling_ave_inv1|
|[BCN_BNB](https://www.binance.com/trade.html?symbol=BCN_BNB)|5.00_rolling_ave_inv1|
|[BCN_BTC](https://www.binance.com/trade.html?symbol=BCN_BTC)|5.00_rolling_ave_inv1|
|[ARN_BTC](https://www.binance.com/trade.html?symbol=ARN_BTC)|5.00_rolling_ave_inv1|
|[ELF_BTC](https://www.binance.com/trade.html?symbol=ELF_BTC)|5.00_rolling_ave_inv1|
|[ICX_BTC](https://www.binance.com/trade.html?symbol=ICX_BTC)|5.00_rolling_ave_inv1|
|[QLC_BTC](https://www.binance.com/trade.html?symbol=QLC_BTC)|5.00_rolling_ave_inv1|
|[QLC_BNB](https://www.binance.com/trade.html?symbol=QLC_BNB)|5.00_rolling_ave_inv1|

# Strategy performance
Strategies are sorted by percentage of orders that returned a profit of at least 4.5 % within 48 hours. The more orders the greater the confidence in the result.
* 328 tradable pairs
* 328 pairs tested
* 48-hour trade window
* 632384 opportunities to trade
* 2166757 orders
<pre>
Strategy		%	Orders
30.0_ski_jumping	100.0	2
20.0_ski_jumping	100.0	2
30.0_straddler_1	100.0	22
40.0_straddler_1	100.0	14
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
30.0_flicking_down	72.5	229
10.0_flicking_down	72.5	4636
5.00_rolling_ave_inv2	72.4	2644
20.0_average_under	72.1	43
40.0_rolling_ave_inv1	71.7	60
20.0_straddler_1	71.2	52
20.0_flicking_down	69.9	548
20.0_red_snapper	68.8	263
10.0_red_snapper	67.6	1292
5.00_rolling_ave_inv1	67.4	9043
40.0_flicking_down	67.3	162
40.0_red_snapper	66.7	36
5.00_rolling_ave_inv3	66.6	341
2.50_rolling_ave_inv3	66.5	3044
2.50_average_under	65.5	3974
40.0_stepping_down	65.4	107
20.0_average_comp2	65.4	107
20.0_old_above_new	65.0	3306
5.00_average_comp2	63.9	4501
10.0_stepping_down	63.9	4501
5.00_straddler_1	63.0	1421
30.0_stepping_down	61.8	170
5.00_steady_rising2	61.7	499
20.0_nino_nino_1	61.7	6473
2.50_rolling_ave_inv2	61.3	20852
2.50_steady_down	61.2	160
30.0_red_snapper	61.0	82
5.00_average_comp	60.8	7181
10.0_old_above_new	60.8	25564
5.00_steady_riser	60.7	537
10.0_stepping_up	60.5	8138
30.0_old_above_new	60.4	858
5.00_average_under	60.3	557
2.50_average_inter	59.8	6326
40.0_old_above_new	59.3	322
5.00_flicking_down	58.9	32779
2.50_average_comp	58.5	35965
30.0_average_comp2	58.5	82
5.00_stepping_up	58.3	37678
10.0_nino_nino_1	57.7	48364
10.0_new_above_old	56.4	30023
5.00_flicking_up	55.8	35309
2.50_rolling_ave_inv1	55.6	50755
5.00_red_snapper	55.5	3096
5.00_stepping_down	55.4	34810
2.50_average_comp2	55.4	34812
20.0_stepping_down	54.6	511
10.0_average_comp2	54.6	511
30.0_nino_nino_1	54.5	1693
10.0_flicking_up	54.4	7794
2.50_steady_rising2	54.1	20660
5.00_new_above_old	54.0	87367
20.0_rolling_ave_inv3	53.8	13
40.0_average_comp2	53.7	67
2.50_stepping_up	53.7	99012
2.50_straddler_1	53.7	2833
2.50_flicking_up	53.1	93411
20.0_new_above_old	53.0	6538
2.50_ski_jumping	53.0	1171
5.00_rolling_average2	52.9	13201
2.50_steady_riser	52.8	24481
40.0_nino_nino_1	52.6	656
5.00_average_inter	52.4	1155
2.50_rolling_average2	51.5	49788
2.50_new_above_old	51.3	155849
5.00_old_above_new	51.0	96346
2.50_roll_average	50.9	24073
20.0_stepping_up	50.7	1843
5.00_nino_nino_1	50.1	181880
10.0_ski_jumping	50.0	4
5.00_roll_average	49.9	4814
2.50_flicking_down	49.8	106286
2.50_koskosovich	49.2	6015
2.50_red_snapper	48.6	4062
2.50_stepping_down	48.5	111143
10.0_average_comp	47.8	1484
10.0_rolling_average2	47.4	2306
5.00_koskosovich	46.8	1761
2.50_nino_nino_1	46.8	344862
2.50_old_above_new	46.6	184868
30.0_new_above_old	46.1	2654
30.0_straddler_2	46.1	8034
2.50_straddler_2	46.1	8034
5.00_straddler_2	46.1	8034
10.0_straddler_2	46.1	8034
20.0_straddler_2	46.1	8034
40.0_straddler_2	46.1	8034
20.0_flicking_up	45.0	1672
10.0_koskosovich	41.1	418
30.0_stepping_up	41.0	988
10.0_roll_average	40.1	878
40.0_rolling_ave_inv3	40.0	5
30.0_rolling_ave_inv3	40.0	5
40.0_new_above_old	39.5	1497
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
40.0_roll_average	33.3	132
20.0_average_inter	33.3	339
20.0_koskosovich	33.3	114
40.0_rolling_average2	33.3	285
40.0_average_inter	32.1	280
30.0_average_inter	31.4	315
30.0_koskosovich	23.8	42
40.0_koskosovich	21.7	23
</pre>
