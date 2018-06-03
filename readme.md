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

Sun  3 Jun 14:27:00 BST 2018 - 
e8cb9ff Use init lists
# Recent recommendations
Potential trades from the top performing stategies below. See the [raw price data](prices.csv)
<pre>
From	To	Strategy		Exch	Spot
I GOT NOTHING :(
</pre>
# Strategy back-test performance
Strategies are back-tested and sorted by percentage of orders that returned a profit of at least 5 % within 48 hours. The more orders the greater the confidence in the result.
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
40.0_rolling_ave_inv2	88.2	17
20.0_rolling_ave_inv2	82.7	139
30.0_rolling_ave_inv1	82.4	102
20.0_rolling_ave_inv1	80.4	184
40.0_average_under	80.0	15
10.0_rolling_ave_inv2	79.7	349
30.0_average_under	77.8	27
10.0_average_under	74.4	82
10.0_rolling_ave_inv1	73.3	1010
30.0_rolling_ave_inv2	72.7	33
20.0_average_under	72.1	43
30.0_flicking_down	70.7	229
40.0_rolling_ave_inv1	70.7	58
10.0_rolling_ave_inv3	70.5	95
5.00_rolling_ave_inv2	70.0	2320
10.0_flicking_down	69.8	4192
10.0_straddler_1	67.4	279
40.0_flicking_down	67.3	162
40.0_red_snapper	66.7	36
20.0_flicking_down	66.2	544
40.0_stepping_down	65.4	107
20.0_average_comp2	65.4	107
20.0_red_snapper	65.3	259
2.50_rolling_ave_inv3	64.3	2771
20.0_straddler_1	64.0	50
5.00_rolling_ave_inv1	63.4	8084
20.0_old_above_new	63.2	3124
2.50_average_under	63.0	3578
10.0_red_snapper	62.9	1192
5.00_rolling_ave_inv3	62.7	314
5.00_average_comp2	62.5	4141
10.0_stepping_down	62.5	4141
20.0_rolling_ave_inv3	62.5	8
30.0_stepping_down	60.6	170
20.0_nino_nino_1	59.1	5983
30.0_average_comp2	58.5	82
40.0_old_above_new	58.2	318
5.00_average_comp	57.9	6834
5.00_steady_rising2	57.6	507
10.0_old_above_new	57.5	23598
10.0_stepping_up	57.4	7758
2.50_rolling_ave_inv2	57.4	19247
30.0_red_snapper	57.3	82
2.50_average_inter	57.3	5991
5.00_straddler_1	57.2	1251
30.0_old_above_new	56.9	837
5.00_steady_riser	56.7	550
5.00_average_under	56.1	542
2.50_average_comp	55.4	35197
5.00_stepping_up	55.2	36892
5.00_flicking_down	54.6	30161
2.50_steady_down	54.0	161
40.0_average_comp2	53.7	67
10.0_nino_nino_1	53.7	44430
10.0_new_above_old	53.5	29165
5.00_flicking_up	53.0	34441
10.0_flicking_up	52.3	7444
10.0_average_comp2	52.3	511
20.0_stepping_down	52.3	511
5.00_stepping_down	51.5	32007
2.50_average_comp2	51.5	32009
2.50_rolling_ave_inv1	51.2	47661
5.00_new_above_old	51.1	86639
30.0_nino_nino_1	51.0	1568
5.00_red_snapper	50.9	2777
5.00_average_inter	50.8	1081
2.50_ski_jumping	50.6	1025
40.0_nino_nino_1	50.6	579
2.50_stepping_up	50.5	98101
20.0_new_above_old	50.5	6229
5.00_rolling_average2	50.4	12701
2.50_steady_rising2	50.2	21083
10.0_ski_jumping	50.0	4
2.50_flicking_up	49.9	92745
2.50_straddler_1	49.3	2600
2.50_steady_riser	48.9	25126
20.0_stepping_up	48.8	1720
2.50_rolling_average2	48.6	48499
2.50_roll_average	48.2	23059
2.50_new_above_old	47.9	156377
5.00_roll_average	47.7	4536
5.00_old_above_new	47.4	91584
2.50_koskosovich	46.7	5916
10.0_rolling_average2	46.6	2159
5.00_nino_nino_1	46.4	173411
2.50_flicking_down	45.8	101918
10.0_average_comp	45.2	1385
5.00_koskosovich	44.8	1711
30.0_new_above_old	44.8	2511
2.50_stepping_down	44.6	106435
2.50_red_snapper	43.5	3722
20.0_flicking_up	43.4	1590
2.50_nino_nino_1	43.1	338418
2.50_old_above_new	42.7	180067
20.0_straddler_2	41.6	7539
2.50_straddler_2	41.6	7539
10.0_straddler_2	41.6	7539
5.00_straddler_2	41.6	7539
30.0_straddler_2	41.6	7539
40.0_straddler_2	41.6	7539
10.0_koskosovich	40.6	392
40.0_rolling_ave_inv3	40.0	5
30.0_rolling_ave_inv3	40.0	5
10.0_roll_average	39.5	817
5.00_ski_jumping	39.1	64
20.0_roll_average	38.2	254
40.0_new_above_old	38.2	1435
20.0_rolling_average2	38.2	566
30.0_stepping_up	36.7	938
20.0_koskosovich	36.2	105
30.0_flicking_up	36.1	847
40.0_flicking_up	35.1	687
30.0_roll_average	34.3	137
20.0_average_comp	34.0	741
30.0_rolling_average2	34.0	347
30.0_average_comp	34.0	650
40.0_stepping_up	33.9	803
40.0_average_comp	32.6	585
10.0_average_inter	31.8	424
40.0_roll_average	31.7	126
40.0_rolling_average2	31.5	279
20.0_average_inter	30.4	339
30.0_koskosovich	30.3	33
40.0_average_inter	29.6	280
40.0_koskosovich	29.4	17
30.0_average_inter	28.9	315
</pre>
