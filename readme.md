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

Tue 29 May 10:52:12 BST 2018 - 
66ad6a4 Merge pull request #223 from deanturpin/add_exchange_name_to_price_report

# Recent recommendations
Potential trades from the top performing stategies below. See the [raw price data](prices.csv)
<pre>
From	To	Spot	Strategy		Exchange
EOS	BTC	5.00_flicking_down	Binance	0.001552
EOS	ETH	5.00_flicking_down	Binance	0.02115
REQ	ETH	2.50_rolling_ave_inv2	Binance	0.0002472
REQ	ETH	10.0_nino_nino_1	Binance	0.0002472
REQ	BTC	2.50_rolling_ave_inv2	Binance	1.812e-05
REQ	BTC	10.0_nino_nino_1	Binance	1.812e-05
RLC	BNB	2.50_average_comp2	Binance	0.1531
RLC	BTC	2.50_average_comp2	Binance	0.0002575
RLC	ETH	2.50_average_comp2	Binance	0.003519
STEEM	ETH	2.50_average_comp2	Binance	0.004158
STEEM	BTC	2.50_average_comp2	Binance	0.0003052
CMT*	BTC	2.50_average_comp	Binance	5.633e-05
CMT*	BTC	5.00_average_comp	Binance	5.633e-05
CMT*	BTC	10.0_stepping_up	Binance	5.633e-05
CMT*	BNB	2.50_average_comp	Binance	0.03371
CMT*	BNB	5.00_average_comp	Binance	0.03371
CMT*	BNB	10.0_stepping_up	Binance	0.03371
CMT*	ETH	2.50_average_comp	Binance	0.0007672
CMT*	ETH	5.00_average_comp	Binance	0.0007672
CMT*	ETH	10.0_stepping_up	Binance	0.0007672
TRX	BTC	2.50_average_comp2	Binance	8.19e-06
TRX	ETH	2.50_average_comp2	Binance	0.0001117
MTL	ETH	2.50_average_comp2	Binance	0.004849
MTL	BTC	2.50_average_comp2	Binance	0.0003552
YOYO	ETH	2.50_average_inter	Binance	0.000245
YOYO	ETH	2.50_average_comp	Binance	0.000245
YOYO	ETH	5.00_average_comp	Binance	0.000245
YOYO	ETH	10.0_stepping_up	Binance	0.000245
IOTA	ETH	2.50_average_inter	Binance	0.001495
IOTA	ETH	2.50_average_comp	Binance	0.001495
IOTA	ETH	5.00_average_comp	Binance	0.001495
IOTA	ETH	10.0_stepping_up	Binance	0.001495
IOTA	BTC	2.50_average_inter	Binance	7.254e-05
IOTA	BTC	2.50_average_comp	Binance	7.254e-05
IOTA	BTC	5.00_average_comp	Binance	7.254e-05
IOTA	BTC	10.0_stepping_up	Binance	7.254e-05
GXS	BTC	2.50_average_comp	Binance	0.0004254
GXS	ETH	2.50_average_comp	Binance	0.005816
</pre>

# Strategy performance
Strategies are sorted by percentage of orders that returned a profit of at least 3.5 % within 48 hours. The more orders the greater the confidence in the result.
* 328 currency pairs polled
* 48-hour trade window
* 632384 opportunities to trade
* 2137607 orders executed
<pre>
Strategy		%	Orders
30.0_ski_jumping	100.0	2
30.0_straddler_1	100.0	22
20.0_ski_jumping	100.0	2
40.0_straddler_1	100.0	14
40.0_rolling_ave_inv2	94.1	17
20.0_rolling_ave_inv2	89.9	139
20.0_rolling_ave_inv1	87.0	184
40.0_average_under	86.7	15
10.0_rolling_ave_inv2	85.8	351
30.0_rolling_ave_inv1	85.3	102
30.0_rolling_ave_inv2	81.8	33
30.0_average_under	81.5	27
10.0_rolling_ave_inv1	81.2	1024
10.0_rolling_ave_inv3	81.1	95
5.00_rolling_ave_inv2	78.7	2448
10.0_flicking_down	78.4	4452
10.0_straddler_1	77.7	301
10.0_average_under	77.5	89
10.0_red_snapper	75.6	1274
30.0_flicking_down	75.5	229
20.0_rolling_ave_inv3	75.0	8
5.00_rolling_ave_inv1	74.5	8543
20.0_red_snapper	74.4	262
20.0_average_under	74.4	43
40.0_rolling_ave_inv1	74.1	58
20.0_flicking_down	73.7	544
2.50_rolling_ave_inv3	72.8	2907
2.50_average_under	71.9	3786
20.0_old_above_new	71.4	3272
5.00_straddler_1	71.2	1377
5.00_rolling_ave_inv3	71.2	323
5.00_average_comp2	70.1	4399
10.0_stepping_down	70.1	4399
20.0_straddler_1	70.0	50
40.0_flicking_down	69.8	162
2.50_rolling_ave_inv2	69.2	20101
2.50_steady_down	68.6	156
10.0_old_above_new	68.5	24796
20.0_nino_nino_1	67.7	6329
5.00_average_comp	67.4	7075
20.0_average_comp2	67.3	107
40.0_stepping_down	67.3	107
5.00_flicking_down	67.2	31482
10.0_stepping_up	67.1	8029
30.0_old_above_new	66.8	856
40.0_red_snapper	66.7	36
5.00_steady_rising2	66.6	497
30.0_red_snapper	65.9	82
2.50_average_inter	65.5	6242
10.0_nino_nino_1	65.3	46960
5.00_red_snapper	65.2	2986
5.00_steady_riser	65.2	535
2.50_average_comp	65.0	35770
5.00_stepping_up	64.8	37480
5.00_average_under	64.4	551
30.0_stepping_down	64.1	170
2.50_rolling_ave_inv1	63.8	49278
40.0_old_above_new	63.7	322
5.00_stepping_down	63.3	33772
2.50_average_comp2	63.3	33774
2.50_straddler_1	62.8	2756
10.0_new_above_old	62.4	29868
20.0_stepping_down	62.0	511
10.0_average_comp2	62.0	511
5.00_flicking_up	61.9	35111
30.0_average_comp2	61.0	82
5.00_new_above_old	60.6	87104
2.50_stepping_up	60.6	98800
30.0_nino_nino_1	60.5	1644
2.50_steady_rising2	60.3	20640
10.0_flicking_up	60.1	7709
30.0_rolling_ave_inv3	60.0	5
40.0_rolling_ave_inv3	60.0	5
2.50_flicking_up	59.8	93107
2.50_ski_jumping	59.8	1137
5.00_old_above_new	59.3	93905
2.50_steady_riser	59.0	24486
20.0_new_above_old	58.8	6449
5.00_rolling_average2	58.6	13061
2.50_new_above_old	58.3	155701
2.50_red_snapper	58.2	3934
5.00_nino_nino_1	58.2	178755
2.50_rolling_average2	58.1	49425
2.50_flicking_down	58.1	103851
20.0_stepping_up	57.6	1789
5.00_average_inter	57.5	1114
2.50_roll_average	57.3	23759
2.50_stepping_down	56.7	108805
40.0_nino_nino_1	56.4	622
5.00_roll_average	55.7	4740
2.50_koskosovich	55.4	5975
10.0_average_comp	54.5	1447
2.50_nino_nino_1	54.5	342641
2.50_old_above_new	54.5	182369
40.0_straddler_2	54.4	7946
2.50_straddler_2	54.4	7946
5.00_straddler_2	54.4	7946
10.0_straddler_2	54.4	7946
20.0_straddler_2	54.4	7946
30.0_straddler_2	54.4	7946
40.0_average_comp2	53.7	67
10.0_rolling_average2	53.0	2258
5.00_koskosovich	52.6	1738
30.0_new_above_old	52.5	2604
20.0_flicking_up	51.6	1636
10.0_ski_jumping	50.0	4
30.0_stepping_up	49.0	963
30.0_average_comp	48.8	650
20.0_average_comp	47.9	741
40.0_average_comp	47.9	585
40.0_stepping_up	47.4	803
40.0_flicking_up	47.2	690
30.0_flicking_up	47.0	861
40.0_new_above_old	46.9	1480
10.0_roll_average	45.4	854
30.0_roll_average	45.3	137
20.0_rolling_average2	45.2	580
20.0_roll_average	44.8	259
40.0_roll_average	43.7	126
10.0_koskosovich	43.5	407
5.00_ski_jumping	43.4	76
40.0_rolling_average2	43.4	279
30.0_rolling_average2	43.1	350
20.0_average_inter	43.1	339
40.0_average_inter	42.5	280
10.0_average_inter	42.2	424
30.0_average_inter	41.6	315
20.0_koskosovich	35.2	108
40.0_koskosovich	29.4	17
30.0_koskosovich	27.8	36
</pre>
