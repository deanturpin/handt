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

Wed 29 Aug 17:29:20 BST 2018 - 
af7b8d8 Don't keep history
# Recent recommendations
Potential trades from the top performing stategies below. See the [raw price data](prices.csv)
<pre>
From	To	Strategy		Exch	Spot
I GOT NOTHING :(
</pre>
# Strategy back-test performance
Strategies are back-tested and sorted by percentage of orders that returned a profit of at least 4.723 % within 48 hours. The more orders the greater the confidence in the result.
* 325 currency pairs polled
* 626600 opportunities to trade
* 649319 orders executed
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
4.9870_rolling_ave_inv1	57.5	7465
4.9870_average_comp	56.9	3329
9.8870_stepping_up	56.6	4007
9.8870_old_above_new	53.1	24727
4.9870_stepping_up	51.9	25216
9.8870_nino_nino_1	51.5	44399
4.9870_flicking_down	51.1	32774
4.9870_average_under	50.5	93
9.8870_flicking_up	50.1	4151
9.8870_new_above_old	50.0	19076
39.009_average_under	50.0	2
39.009_flicking_down	50.0	4
4.9870_steady_rising2	49.6	1143
19.567_stepping_up	49.3	537
4.9870_stepping_down	48.9	34162
4.9870_flicking_up	48.6	23929
19.567_new_above_old	48.4	2961
9.8870_average_comp	47.4	430
4.9870_new_above_old	46.6	65158
9.8870_red_snapper	46.3	855
4.9870_straddler_1	46.1	1078
4.9870_rolling_average2	45.5	8583
27.123_new_above_old	45.1	1074
4.9870_steady_riser	44.9	1401
19.567_rolling_ave_inv1	44.1	34
4.9870_average_inter	44.0	375
9.8870_rolling_ave_inv3	43.3	30
27.123_stepping_up	43.3	268
4.9870_old_above_new	43.2	101760
4.9870_nino_nino_1	42.9	174681
4.9870_roll_average	41.2	3178
39.009_rolling_ave_inv1	40.0	15
9.8870_rolling_average2	39.7	1190
4.9870_red_snapper	39.3	2606
9.8870_koskosovich	38.5	309
4.9870_koskosovich	37.8	1241
19.567_flicking_up	37.3	483
19.567_stepping_down	37.0	108
9.8870_average_comp2	35.9	103
9.8870_average_under	35.3	17
39.009_old_above_new	35.3	51
9.8870_roll_average	34.1	484
27.123_rolling_ave_inv1	33.3	21
39.009_new_above_old	33.0	373
19.567_koskosovich	32.1	56
27.123_koskosovich	31.0	29
27.123_straddler_2	30.8	6796
4.9870_straddler_2	30.8	6796
39.009_straddler_2	30.8	6796
19.567_straddler_2	30.8	6796
9.8870_straddler_2	30.8	6796
4.9870_ski_jumping	29.4	34
19.567_rolling_average2	28.8	160
39.009_nino_nino_1	28.1	292
19.567_roll_average	27.4	73
27.123_average_under	27.3	11
27.123_flicking_up	27.3	198
27.123_flicking_down	27.1	48
39.009_koskosovich	26.3	19
19.567_average_comp	25.7	113
39.009_stepping_up	25.6	125
9.8870_average_inter	25.0	84
19.567_average_under	25.0	12
27.123_rolling_average2	24.1	79
27.123_stepping_down	23.1	39
27.123_rolling_ave_inv2	22.2	9
39.009_rolling_ave_inv2	22.2	9
27.123_average_comp	22.1	77
39.009_roll_average	19.2	26
19.567_rolling_ave_inv2	17.6	17
27.123_roll_average	15.8	38
39.009_rolling_average2	14.5	55
19.567_average_inter	11.8	34
39.009_flicking_up	11.3	97
39.009_average_comp	0.0	34
19.567_rolling_ave_inv3	0.0	5
39.009_average_inter	0.0	16
27.123_average_inter	0.0	18
39.009_rolling_ave_inv3	0.0	5
19.567_average_comp2	0.0	21
39.009_stepping_down	0.0	21
27.123_average_comp2	0.0	9
27.123_rolling_ave_inv3	0.0	5
</pre>
