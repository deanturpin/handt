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

Sun  3 Jun 10:09:29 BST 2018 - 
05a6dec Reword
# Recent recommendations
Potential trades from the top performing stategies below. See the [raw price data](prices.csv)
<pre>
From	To	Strategy		Exch	Spot
I GOT NOTHING :(
</pre>
# Strategy back-test performance
Strategies are back-tested and sorted by percentage of orders that returned a profit of at least 6 % within 48 hours. The more orders the greater the confidence in the result.
* 328 currency pairs polled
* 48-hour sell window
* 632384 opportunities to trade
* 2095940 orders executed
<pre>
Strategy		%	Orders
30.0_ski_jumping	100.0	2
20.0_ski_jumping	100.0	2
40.0_straddler_1	100.0	14
30.0_straddler_1	90.9	22
40.0_rolling_ave_inv2	82.4	17
30.0_rolling_ave_inv1	81.4	102
40.0_average_under	80.0	15
20.0_rolling_ave_inv2	79.9	139
30.0_average_under	77.8	27
20.0_rolling_ave_inv1	77.7	184
10.0_rolling_ave_inv2	76.8	349
10.0_average_under	74.4	82
20.0_average_under	72.1	43
30.0_flicking_down	69.9	229
10.0_rolling_ave_inv1	69.8	1010
30.0_rolling_ave_inv2	69.7	33
40.0_rolling_ave_inv1	69.0	58
40.0_red_snapper	66.7	36
40.0_flicking_down	66.7	162
40.0_stepping_down	65.4	107
20.0_average_comp2	65.4	107
5.00_rolling_ave_inv2	65.0	2320
10.0_flicking_down	65.0	4192
10.0_straddler_1	63.8	279
10.0_rolling_ave_inv3	63.2	95
20.0_straddler_1	62.0	50
20.0_flicking_down	61.6	544
20.0_red_snapper	61.4	259
2.50_rolling_ave_inv3	59.5	2771
30.0_average_comp2	58.5	82
20.0_old_above_new	58.5	3124
10.0_stepping_down	58.4	4141
5.00_average_comp2	58.4	4141
5.00_rolling_ave_inv3	58.0	314
30.0_stepping_down	57.6	170
5.00_rolling_ave_inv1	57.4	8084
2.50_average_under	57.3	3578
10.0_red_snapper	55.6	1192
40.0_old_above_new	54.7	318
20.0_nino_nino_1	54.2	5983
40.0_average_comp2	53.7	67
30.0_red_snapper	53.7	82
2.50_steady_down	53.4	161
5.00_average_comp	52.7	6834
2.50_average_inter	52.4	5991
10.0_stepping_up	52.3	7758
5.00_average_under	52.0	542
10.0_old_above_new	51.5	23598
30.0_old_above_new	51.4	837
5.00_steady_rising2	51.1	507
2.50_rolling_ave_inv2	51.1	19247
5.00_steady_riser	50.7	550
5.00_straddler_1	50.3	1251
20.0_rolling_ave_inv3	50.0	8
10.0_ski_jumping	50.0	4
2.50_average_comp	49.6	35197
5.00_stepping_up	49.4	36892
10.0_new_above_old	48.3	29165
5.00_flicking_down	48.2	30161
10.0_flicking_up	48.0	7444
5.00_flicking_up	47.8	34441
40.0_nino_nino_1	47.5	579
10.0_nino_nino_1	47.5	44430
20.0_stepping_down	47.4	511
10.0_average_comp2	47.4	511
5.00_average_inter	46.1	1081
20.0_new_above_old	46.0	6229
5.00_rolling_average2	45.9	12701
30.0_nino_nino_1	45.8	1568
5.00_new_above_old	45.4	86639
2.50_average_comp2	45.2	32009
5.00_stepping_down	45.2	32007
2.50_ski_jumping	45.2	1025
2.50_stepping_up	44.7	98101
2.50_rolling_ave_inv1	44.5	47661
20.0_stepping_up	44.4	1720
2.50_steady_rising2	44.3	21083
2.50_flicking_up	44.3	92745
5.00_roll_average	43.6	4536
5.00_red_snapper	43.6	2777
2.50_rolling_average2	43.3	48499
2.50_roll_average	43.3	23059
2.50_steady_riser	43.2	25126
10.0_rolling_average2	42.7	2159
2.50_straddler_1	42.4	2600
2.50_koskosovich	42.2	5916
2.50_new_above_old	42.0	156377
5.00_koskosovich	41.5	1711
30.0_new_above_old	41.0	2511
5.00_old_above_new	40.9	91584
10.0_average_comp	40.5	1385
5.00_nino_nino_1	39.8	173411
20.0_flicking_up	39.4	1590
2.50_flicking_down	39.3	101918
2.50_stepping_down	38.2	106435
10.0_koskosovich	38.0	392
5.00_ski_jumping	37.5	64
2.50_red_snapper	36.8	3722
2.50_nino_nino_1	36.8	338418
2.50_old_above_new	36.4	180067
10.0_roll_average	36.0	817
40.0_straddler_2	35.3	7539
30.0_straddler_2	35.3	7539
20.0_straddler_2	35.3	7539
10.0_straddler_2	35.3	7539
5.00_straddler_2	35.3	7539
2.50_straddler_2	35.3	7539
40.0_new_above_old	34.3	1435
20.0_rolling_average2	33.6	566
20.0_koskosovich	32.4	105
30.0_stepping_up	32.2	938
20.0_roll_average	31.9	254
30.0_flicking_up	31.4	847
30.0_koskosovich	30.3	33
40.0_flicking_up	29.7	687
40.0_koskosovich	29.4	17
40.0_stepping_up	29.1	803
20.0_average_comp	28.9	741
30.0_rolling_average2	28.5	347
30.0_roll_average	28.5	137
30.0_average_comp	28.3	650
40.0_average_comp	26.7	585
10.0_average_inter	26.4	424
40.0_rolling_average2	25.8	279
40.0_roll_average	25.4	126
20.0_average_inter	24.2	339
40.0_average_inter	23.2	280
30.0_average_inter	22.2	315
40.0_rolling_ave_inv3	20.0	5
30.0_rolling_ave_inv3	20.0	5
</pre>
