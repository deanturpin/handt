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

Wed 20 Jun 16:25:11 BST 2018 - 
2b63f03 Use constructor not copy
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
* 634665 orders executed
<pre>
Strategy		%	Orders
39.009_straddler_1	100.0	13
27.123_straddler_1	100.0	15
27.123_ski_jumping	100.0	2
19.567_ski_jumping	100.0	2
19.567_straddler_1	100.0	21
27.123_red_snapper	96.7	30
39.009_red_snapper	95.8	24
19.567_red_snapper	95.2	83
9.8870_straddler_1	90.5	95
39.009_rolling_ave_inv2	88.2	17
9.8870_rolling_ave_inv1	81.2	649
9.8870_rolling_ave_inv2	80.3	244
39.009_average_under	80.0	15
9.8870_average_under	79.2	77
27.123_average_under	78.6	28
27.123_rolling_ave_inv1	78.2	78
19.567_rolling_ave_inv1	76.8	95
19.567_flicking_down	75.1	313
9.8870_flicking_down	74.6	2571
19.567_rolling_ave_inv2	74.2	62
19.567_average_under	72.7	44
19.567_old_above_new	71.5	1662
9.8870_rolling_ave_inv3	71.4	49
39.009_rolling_ave_inv1	69.6	56
4.9870_rolling_ave_inv2	69.1	1674
27.123_flicking_down	67.5	197
9.8870_stepping_down	66.6	2455
4.9870_average_comp2	66.3	2380
4.9870_average_under	66.1	289
39.009_stepping_down	65.7	108
19.567_average_comp2	65.7	108
39.009_flicking_down	65.6	157
27.123_old_above_new	64.6	514
27.123_stepping_down	64.3	182
9.8870_red_snapper	64.1	672
27.123_rolling_ave_inv2	63.9	36
19.567_stepping_down	63.3	251
4.9870_rolling_ave_inv3	63.1	198
4.9870_rolling_ave_inv1	63.0	6102
9.8870_average_comp2	63.0	246
19.567_nino_nino_1	60.6	3854
27.123_average_comp2	58.3	84
39.009_old_above_new	58.0	264
9.8870_old_above_new	56.7	19941
4.9870_average_comp	55.2	4756
9.8870_stepping_up	54.9	5560
4.9870_straddler_1	53.8	785
4.9870_steady_rising2	53.3	1671
4.9870_flicking_down	52.7	26344
27.123_nino_nino_1	52.6	1159
4.9870_stepping_up	52.4	28602
39.009_average_comp2	52.2	69
9.8870_nino_nino_1	51.7	37475
9.8870_new_above_old	51.4	22333
9.8870_flicking_up	50.8	5272
4.9870_flicking_up	50.7	26798
4.9870_steady_riser	50.4	2049
9.8870_ski_jumping	50.0	4
19.567_rolling_ave_inv3	50.0	10
4.9870_stepping_down	49.7	27742
19.567_new_above_old	48.2	4407
4.9870_rolling_average2	48.1	9463
4.9870_new_above_old	48.0	71758
39.009_nino_nino_1	46.8	468
4.9870_red_snapper	46.6	2238
4.9870_roll_average	45.7	3237
4.9870_old_above_new	44.1	91586
4.9870_ski_jumping	43.8	32
9.8870_rolling_average2	43.7	1450
4.9870_average_inter	43.6	699
19.567_stepping_up	43.3	1112
27.123_new_above_old	43.1	2041
4.9870_nino_nino_1	42.8	165681
4.9870_koskosovich	42.7	1238
4.9870_straddler_2	40.0	6650
9.8870_straddler_2	40.0	6650
19.567_straddler_2	40.0	6650
27.123_straddler_2	40.0	6650
39.009_straddler_2	40.0	6650
27.123_rolling_ave_inv3	40.0	5
39.009_rolling_ave_inv3	40.0	5
9.8870_average_comp	39.0	880
19.567_flicking_up	36.7	1033
9.8870_koskosovich	36.6	254
9.8870_roll_average	33.1	532
19.567_roll_average	30.4	181
27.123_stepping_up	30.2	662
27.123_flicking_up	29.5	614
39.009_new_above_old	29.4	955
19.567_koskosovich	29.4	85
19.567_rolling_average2	28.5	383
27.123_average_comp	28.3	420
39.009_flicking_up	27.9	451
27.123_rolling_average2	27.9	247
27.123_koskosovich	27.8	36
39.009_average_comp	27.4	391
27.123_roll_average	26.5	98
19.567_average_comp	26.5	483
39.009_stepping_up	25.8	520
19.567_average_inter	25.6	238
39.009_roll_average	25.6	90
39.009_average_inter	23.9	184
9.8870_average_inter	23.5	268
39.009_rolling_average2	23.1	182
27.123_average_inter	22.7	207
39.009_koskosovich	20.0	15
</pre>
