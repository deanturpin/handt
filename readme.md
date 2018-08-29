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

Wed 29 Aug 17:35:16 BST 2018 - 
4c43ac2 Move to gcc 8
# Recent recommendations
Potential trades from the top performing stategies below. See the [raw price data](prices.csv)
<pre>
From	To	Strategy		Exch	Spot
I GOT NOTHING :(
</pre>
# Strategy back-test performance
Strategies are back-tested and sorted by percentage of orders that returned a profit of at least 4.723 % within 48 hours. The more orders the greater the confidence in the result.
* 328 currency pairs polled
* 632384 opportunities to trade
* 651191 orders executed
<pre>
Strategy		%	Orders
27.123_red_snapper	100.0	11
27.123_straddler_1	100.0	1
19.567_straddler_1	100.0	2
19.567_red_snapper	93.3	75
9.8870_straddler_1	80.6	93
19.567_old_above_new	73.9	2058
9.8870_rolling_ave_inv1	71.7	378
27.123_old_above_new	67.9	436
9.8870_rolling_ave_inv2	65.4	104
19.567_nino_nino_1	65.3	4119
9.8870_flicking_down	64.9	3006
19.567_flicking_down	62.3	138
4.9870_rolling_ave_inv2	62.2	1687
4.9870_rolling_ave_inv3	61.3	212
27.123_nino_nino_1	61.0	1095
4.9870_average_comp2	59.7	3033
9.8870_stepping_down	59.5	3142
4.9870_rolling_ave_inv1	57.5	7467
4.9870_average_comp	55.8	3395
9.8870_stepping_up	55.7	4073
9.8870_old_above_new	53.1	24727
4.9870_stepping_up	51.8	25283
9.8870_nino_nino_1	51.5	44399
4.9870_flicking_down	51.1	32774
4.9870_average_under	50.5	93
39.009_flicking_down	50.0	4
39.009_average_under	50.0	2
9.8870_new_above_old	49.9	19145
4.9870_steady_rising2	49.6	1143
9.8870_flicking_up	49.4	4212
4.9870_stepping_down	48.9	34169
4.9870_flicking_up	48.4	23994
19.567_new_above_old	47.3	3030
4.9870_new_above_old	46.5	65227
9.8870_red_snapper	46.3	855
4.9870_straddler_1	46.1	1078
4.9870_rolling_average2	45.3	8610
4.9870_steady_riser	44.9	1401
19.567_stepping_up	44.2	600
19.567_rolling_ave_inv1	44.1	34
9.8870_rolling_ave_inv3	43.3	30
4.9870_old_above_new	43.2	101785
4.9870_nino_nino_1	42.9	174721
27.123_new_above_old	42.3	1143
9.8870_average_comp	41.4	493
4.9870_roll_average	41.0	3190
4.9870_average_inter	40.4	408
39.009_rolling_ave_inv1	40.0	15
4.9870_red_snapper	39.3	2606
9.8870_rolling_average2	38.9	1217
9.8870_koskosovich	38.3	311
4.9870_koskosovich	37.7	1243
19.567_stepping_down	37.0	108
9.8870_average_comp2	35.9	103
9.8870_average_under	35.3	17
39.009_old_above_new	35.3	51
27.123_stepping_up	35.0	331
19.567_flicking_up	33.5	538
27.123_rolling_ave_inv1	33.3	21
9.8870_roll_average	33.3	496
19.567_koskosovich	31.0	58
27.123_straddler_2	30.6	6842
19.567_straddler_2	30.6	6842
4.9870_straddler_2	30.6	6842
9.8870_straddler_2	30.6	6842
39.009_straddler_2	30.6	6842
4.9870_ski_jumping	29.4	34
27.123_koskosovich	29.0	31
39.009_nino_nino_1	28.1	292
39.009_new_above_old	27.8	442
27.123_average_under	27.3	11
27.123_flicking_down	27.1	48
19.567_rolling_average2	25.0	184
19.567_average_under	25.0	12
39.009_koskosovich	23.8	21
19.567_roll_average	23.5	85
27.123_stepping_down	23.1	39
27.123_rolling_ave_inv2	22.2	9
39.009_rolling_ave_inv2	22.2	9
27.123_flicking_up	21.4	252
27.123_rolling_average2	19.0	100
9.8870_average_inter	18.4	114
19.567_rolling_ave_inv2	17.6	17
39.009_stepping_up	17.3	185
19.567_average_comp	17.0	171
39.009_roll_average	14.3	35
27.123_average_comp	13.0	131
27.123_roll_average	12.8	47
39.009_rolling_average2	10.5	76
39.009_flicking_up	7.5	146
19.567_average_inter	6.2	64
27.123_average_inter	0.0	45
39.009_average_inter	0.0	40
39.009_average_comp	0.0	85
19.567_rolling_ave_inv3	0.0	5
27.123_rolling_ave_inv3	0.0	5
19.567_average_comp2	0.0	21
39.009_stepping_down	0.0	21
27.123_average_comp2	0.0	9
39.009_rolling_ave_inv3	0.0	5
</pre>
