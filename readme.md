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

Tue 29 May 11:23:35 BST 2018 - 
5d9ca00 Reword headings [skip ci]

# Recent recommendations
Potential trades from the top performing stategies below. See the [raw price data](prices.csv)
<pre>
From	To		Strategy	Exch	Spot
I GOT NOTHING :(
</pre>

# Strategy performance
Strategies are sorted by percentage of orders that returned a profit of at least 4.5 % within 48 hours. The more orders the greater the confidence in the result.
* 328 currency pairs polled
* 48-hour trade window
* 632384 opportunities to trade
* 2137607 orders executed
<pre>
Strategy		%	Orders
30.0_ski_jumping	100.0	2
20.0_ski_jumping	100.0	2
30.0_straddler_1	100.0	22
40.0_straddler_1	100.0	14
40.0_rolling_ave_inv2	88.2	17
20.0_rolling_ave_inv2	85.6	139
30.0_rolling_ave_inv1	83.3	102
20.0_rolling_ave_inv1	82.6	184
10.0_rolling_ave_inv2	81.8	351
40.0_average_under	80.0	15
30.0_average_under	77.8	27
10.0_average_under	76.4	89
10.0_rolling_ave_inv1	76.2	1024
30.0_rolling_ave_inv2	75.8	33
10.0_rolling_ave_inv3	74.7	95
5.00_rolling_ave_inv2	73.1	2448
30.0_flicking_down	72.5	229
10.0_flicking_down	72.5	4452
10.0_straddler_1	72.4	301
20.0_average_under	72.1	43
40.0_rolling_ave_inv1	70.7	58
20.0_straddler_1	70.0	50
20.0_flicking_down	69.7	544
20.0_red_snapper	68.7	262
10.0_red_snapper	68.2	1274
5.00_rolling_ave_inv1	67.8	8543
40.0_flicking_down	67.3	162
2.50_rolling_ave_inv3	66.8	2907
40.0_red_snapper	66.7	36
2.50_average_under	66.3	3786
5.00_rolling_ave_inv3	65.6	323
20.0_average_comp2	65.4	107
40.0_stepping_down	65.4	107
20.0_old_above_new	65.0	3272
5.00_average_comp2	64.5	4399
10.0_stepping_down	64.5	4399
5.00_straddler_1	64.1	1377
20.0_rolling_ave_inv3	62.5	8
5.00_steady_rising2	62.0	497
30.0_stepping_down	61.8	170
2.50_rolling_ave_inv2	61.6	20101
20.0_nino_nino_1	61.6	6329
10.0_old_above_new	61.2	24796
5.00_average_comp	61.1	7075
30.0_red_snapper	61.0	82
5.00_steady_riser	60.9	535
2.50_steady_down	60.9	156
10.0_stepping_up	60.8	8029
30.0_old_above_new	60.3	856
5.00_average_under	59.9	551
2.50_average_inter	59.8	6242
40.0_old_above_new	59.3	322
5.00_flicking_down	59.3	31482
2.50_average_comp	58.7	35770
30.0_average_comp2	58.5	82
5.00_stepping_up	58.4	37480
10.0_nino_nino_1	58.0	46960
5.00_red_snapper	57.1	2986
10.0_new_above_old	56.5	29868
5.00_stepping_down	55.9	33772
2.50_average_comp2	55.9	33774
5.00_flicking_up	55.8	35111
2.50_rolling_ave_inv1	55.8	49278
2.50_straddler_1	54.7	2756
20.0_stepping_down	54.6	511
10.0_average_comp2	54.6	511
10.0_flicking_up	54.5	7709
5.00_new_above_old	54.0	87104
2.50_steady_rising2	54.0	20640
30.0_nino_nino_1	53.8	1644
40.0_average_comp2	53.7	67
2.50_stepping_up	53.7	98800
2.50_ski_jumping	53.6	1137
20.0_new_above_old	53.2	6449
2.50_flicking_up	53.1	93107
5.00_rolling_average2	53.0	13061
2.50_steady_riser	52.7	24486
5.00_average_inter	51.8	1114
2.50_rolling_average2	51.6	49425
40.0_nino_nino_1	51.4	622
5.00_old_above_new	51.3	93905
2.50_new_above_old	51.3	155701
2.50_roll_average	51.1	23759
20.0_stepping_up	50.7	1789
5.00_nino_nino_1	50.3	178755
5.00_roll_average	50.0	4740
10.0_ski_jumping	50.0	4
2.50_flicking_down	49.9	103851
2.50_red_snapper	49.8	3934
2.50_koskosovich	49.3	5975
2.50_stepping_down	48.6	108805
10.0_rolling_average2	47.5	2258
10.0_average_comp	47.3	1447
5.00_koskosovich	47.1	1738
2.50_nino_nino_1	46.7	342641
2.50_old_above_new	46.6	182369
30.0_straddler_2	46.4	7946
2.50_straddler_2	46.4	7946
5.00_straddler_2	46.4	7946
10.0_straddler_2	46.4	7946
20.0_straddler_2	46.4	7946
40.0_straddler_2	46.4	7946
30.0_new_above_old	46.3	2604
20.0_flicking_up	44.9	1636
10.0_koskosovich	41.0	407
30.0_stepping_up	40.2	963
10.0_roll_average	40.0	854
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
