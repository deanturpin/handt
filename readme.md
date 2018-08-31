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

Fri 31 Aug 13:21:24 BST 2018 - 
b13cdf2 Merge pull request #232 from deanturpin/gcc_8_migration
# Recent recommendations
Potential trades from the top performing stategies below. See the [raw price data](prices.csv)
<pre>
From	To	Strategy		Exch	Spot
I GOT NOTHING :(
</pre>
# Strategy back-test performance
Strategies are back-tested and sorted by percentage of orders that returned a profit of at least 5 % within 48 hours. The more orders the greater the confidence in the result.
* 328 currency pairs polled
* 632384 opportunities to trade
* 648146 orders executed
<pre>
Strategy		%	Orders
30.000_red_snapper	100.0	4
20.000_straddler_1	100.0	2
20.000_red_snapper	90.9	66
10.000_straddler_1	78.2	87
20.000_old_above_new	72.0	1881
10.000_rolling_ave_inv1	67.7	362
10.000_flicking_down	62.6	2876
20.000_nino_nino_1	62.3	3866
5.0000_rolling_ave_inv2	60.0	1681
30.000_old_above_new	59.1	237
10.000_rolling_ave_inv2	58.8	102
20.000_flicking_down	58.6	128
10.000_stepping_down	58.3	3014
5.0000_average_comp2	58.3	3015
5.0000_rolling_ave_inv3	57.9	214
5.0000_rolling_ave_inv1	55.4	7426
10.000_stepping_up	53.0	4152
5.0000_average_comp	52.8	3545
10.000_old_above_new	51.2	23957
10.000_nino_nino_1	49.6	43273
5.0000_stepping_up	49.5	26065
5.0000_flicking_down	49.3	32588
30.000_nino_nino_1	49.1	737
10.000_new_above_old	47.9	19390
10.000_flicking_up	47.4	4250
5.0000_stepping_down	47.0	34029
5.0000_steady_rising2	47.0	283
5.0000_flicking_up	46.6	24726
5.0000_straddler_1	45.1	1068
10.000_red_snapper	45.1	831
5.0000_average_under	44.7	94
5.0000_new_above_old	44.4	67556
20.000_new_above_old	44.3	2955
5.0000_rolling_average2	43.7	8829
5.0000_steady_riser	41.9	322
5.0000_old_above_new	41.5	100635
5.0000_nino_nino_1	41.2	173785
20.000_stepping_up	40.9	584
5.0000_roll_average	39.5	3259
5.0000_average_inter	39.4	411
10.000_koskosovich	38.4	318
5.0000_red_snapper	37.9	2588
10.000_average_comp	37.9	478
10.000_rolling_ave_inv3	37.5	32
10.000_rolling_average2	37.1	1208
5.0000_koskosovich	35.9	1273
30.000_new_above_old	35.4	888
40.000_old_above_new	33.3	45
10.000_roll_average	31.8	493
20.000_stepping_down	31.3	99
10.000_average_comp2	31.3	99
20.000_flicking_up	30.7	521
5.0000_ski_jumping	29.4	34
30.000_stepping_up	28.9	280
5.0000_straddler_2	28.7	6958
40.000_straddler_2	28.7	6958
30.000_straddler_2	28.7	6958
20.000_straddler_2	28.7	6958
10.000_straddler_2	28.7	6958
30.000_koskosovich	26.7	30
40.000_koskosovich	26.3	19
40.000_new_above_old	24.6	423
20.000_koskosovich	24.6	57
20.000_rolling_ave_inv1	23.5	34
20.000_rolling_average2	23.1	173
30.000_flicking_down	22.2	27
20.000_roll_average	22.0	82
40.000_nino_nino_1	20.9	278
30.000_flicking_up	18.9	217
10.000_average_under	17.6	17
30.000_stepping_down	15.6	32
30.000_rolling_average2	15.6	96
40.000_roll_average	14.3	35
10.000_average_inter	13.3	113
30.000_roll_average	11.9	42
40.000_stepping_up	11.5	182
20.000_average_comp	10.3	165
40.000_rolling_average2	9.6	73
40.000_flicking_up	7.5	146
20.000_rolling_ave_inv2	6.2	16
30.000_average_comp	1.0	98
30.000_average_comp2	0.0	2
40.000_flicking_down	0.0	2
40.000_stepping_down	0.0	21
20.000_average_comp2	0.0	21
40.000_average_under	0.0	2
30.000_average_under	0.0	8
20.000_average_under	0.0	12
40.000_rolling_ave_inv1	0.0	14
30.000_rolling_ave_inv1	0.0	21
40.000_rolling_ave_inv2	0.0	9
30.000_rolling_ave_inv2	0.0	9
20.000_average_inter	0.0	54
30.000_average_inter	0.0	45
40.000_average_inter	0.0	40
40.000_rolling_ave_inv3	0.0	5
30.000_rolling_ave_inv3	0.0	5
20.000_rolling_ave_inv3	0.0	5
40.000_average_comp	0.0	85
</pre>
