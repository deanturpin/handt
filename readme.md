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

Tue 29 May 08:09:55 BST 2018 - 
3cbfcb1 regen readme

# Recent recommendations
Potential trades from the top performing stategies below. See the [raw price data](prices.csv)

Exchange|From|To|Strategy
---|---|---|---
I|GOT|NOTHING|:(

# Strategy performance
Strategies are sorted by percentage of orders that returned a profit of at least 4.5 % within 48 hours. The more orders the greater the confidence in the result.
* 328 currency pairs polled
* 48-hour trade window
* 632384 opportunities to trade
* 2140542 orders executed
<pre>
Strategy		%	Orders
30.0_ski_jumping	100.0	2
20.0_ski_jumping	100.0	2
30.0_straddler_1	100.0	22
40.0_straddler_1	100.0	14
40.0_rolling_ave_inv2	88.2	17
20.0_rolling_ave_inv2	85.6	139
30.0_rolling_ave_inv1	83.3	102
20.0_rolling_ave_inv1	82.9	187
10.0_rolling_ave_inv2	81.8	351
40.0_average_under	80.0	15
30.0_average_under	77.8	27
10.0_average_under	77.2	92
10.0_rolling_ave_inv1	76.3	1030
30.0_rolling_ave_inv2	75.8	33
10.0_rolling_ave_inv3	74.7	95
5.00_rolling_ave_inv2	73.1	2450
10.0_flicking_down	72.5	4457
30.0_flicking_down	72.5	229
10.0_straddler_1	72.4	301
20.0_average_under	72.1	43
40.0_rolling_ave_inv1	70.7	58
20.0_straddler_1	70.0	50
20.0_flicking_down	69.7	544
20.0_red_snapper	68.7	262
10.0_red_snapper	68.2	1275
5.00_rolling_ave_inv1	67.8	8553
40.0_flicking_down	67.3	162
2.50_rolling_ave_inv3	66.8	2916
40.0_red_snapper	66.7	36
2.50_average_under	66.2	3829
5.00_rolling_ave_inv3	65.6	323
20.0_average_comp2	65.4	107
40.0_stepping_down	65.4	107
20.0_old_above_new	65.0	3274
10.0_stepping_down	64.3	4425
5.00_average_comp2	64.3	4425
5.00_straddler_1	64.1	1377
20.0_rolling_ave_inv3	62.5	8
5.00_steady_rising2	62.0	497
30.0_stepping_down	61.8	170
20.0_nino_nino_1	61.6	6348
2.50_rolling_ave_inv2	61.6	20123
5.00_average_comp	61.2	7087
10.0_old_above_new	61.1	24893
30.0_red_snapper	61.0	82
5.00_steady_riser	60.9	535
2.50_steady_down	60.9	156
10.0_stepping_up	60.8	8041
5.00_average_under	60.3	557
30.0_old_above_new	60.3	856
2.50_average_inter	59.8	6252
40.0_old_above_new	59.3	322
5.00_flicking_down	59.3	31569
2.50_average_comp	58.7	35784
30.0_average_comp2	58.5	82
5.00_stepping_up	58.4	37494
10.0_nino_nino_1	57.9	47137
5.00_red_snapper	56.9	2996
10.0_new_above_old	56.5	29883
5.00_flicking_up	55.9	35127
2.50_rolling_ave_inv1	55.8	49313
5.00_stepping_down	55.7	34008
2.50_average_comp2	55.7	34010
20.0_stepping_down	54.6	511
10.0_average_comp2	54.6	511
2.50_straddler_1	54.5	2764
10.0_flicking_up	54.5	7717
5.00_new_above_old	54.0	87122
2.50_steady_rising2	54.0	20640
30.0_nino_nino_1	53.9	1650
40.0_average_comp2	53.7	67
2.50_stepping_up	53.7	98824
2.50_ski_jumping	53.4	1142
20.0_new_above_old	53.3	6459
2.50_flicking_up	53.1	93129
5.00_rolling_average2	53.0	13080
2.50_steady_riser	52.7	24480
40.0_nino_nino_1	51.9	628
5.00_average_inter	51.8	1114
2.50_rolling_average2	51.6	49476
2.50_new_above_old	51.3	155721
5.00_old_above_new	51.2	94157
2.50_roll_average	51.1	23786
20.0_stepping_up	51.0	1801
5.00_nino_nino_1	50.2	179070
5.00_roll_average	50.1	4748
10.0_ski_jumping	50.0	4
2.50_flicking_down	49.9	104062
2.50_red_snapper	49.7	3939
2.50_koskosovich	49.3	5976
2.50_stepping_down	48.6	109108
10.0_average_comp	47.8	1459
10.0_rolling_average2	47.5	2260
5.00_koskosovich	47.1	1738
2.50_nino_nino_1	46.7	342844
2.50_old_above_new	46.6	182571
30.0_straddler_2	46.4	7949
2.50_straddler_2	46.4	7949
5.00_straddler_2	46.4	7949
10.0_straddler_2	46.4	7949
20.0_straddler_2	46.4	7949
40.0_straddler_2	46.4	7949
30.0_new_above_old	46.4	2609
20.0_flicking_up	45.1	1641
10.0_koskosovich	41.0	407
30.0_stepping_up	40.6	969
10.0_roll_average	40.3	857
40.0_rolling_ave_inv3	40.0	5
30.0_rolling_ave_inv3	40.0	5
40.0_new_above_old	40.0	1480
20.0_roll_average	39.8	259
30.0_flicking_up	38.9	861
20.0_rolling_average2	38.8	580
30.0_average_comp	38.5	650
40.0_flicking_up	38.4	690
5.00_ski_jumping	38.2	76
20.0_average_comp	38.1	741
40.0_stepping_up	37.9	803
30.0_roll_average	37.2	137
40.0_average_comp	37.1	585
30.0_rolling_average2	35.7	350
20.0_koskosovich	35.2	108
40.0_roll_average	34.9	126
10.0_average_inter	34.2	424
40.0_rolling_average2	34.1	279
20.0_average_inter	33.3	339
40.0_average_inter	32.1	280
30.0_average_inter	31.4	315
40.0_koskosovich	29.4	17
30.0_koskosovich	27.8	36
</pre>
