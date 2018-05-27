<!-- If this is readme.md it will be overwritten by the build process -->

[![Build Status](https://travis-ci.org/deanturpin/handt.svg?branch=master)](https://travis-ci.org/deanturpin/handt)
[![codecov](https://codecov.io/gh/deanturpin/handt/branch/master/graph/badge.svg)](https://codecov.io/gh/deanturpin/handt)

**History is no indicator of future performance. Don't invest what you can't
afford to lose.**

*Have A Nice Day Trader* is an algorithmic trading platform. Prices are
requested for all currency pairs traded by Binance over the last 80 days. Then a
library of strategies is back-tested over the prices and a strategy summary is
generated. Prices are fetched using the [CryptoCompare
API](https://min-api.cryptocompare.com/).

See the [details](details.md).

---
Generated Sun 27 May 11:22:16 BST 2018

# What's popping, bro?
Recent recommendations by the top performing stategies below. See the [raw price data](prices.csv)

|Currency pair|Strategy|
|---|---|
|I GOT NOTHING|:(|

# Strategy performance
Strategies are sorted by percentage of orders that returned a profit of at least 6 % within 48 hours. The more orders the greater the confidence in the result.
* 315 tradable pairs
* 315 pairs processed
* 48 hours look ahead for order to mature
* 607320 x 24 hour periods processed
* 7731521 orders placed
<pre>
Strategy		%	Orders
30.0_ski_jumping	100.0	2
20.0_ski_jumping	100.0	2
40.0_straddler_1	100.0	1
30.0_rolling_ave_inv1	80.4	97
40.0_average_under	80.0	15
20.0_rolling_ave_inv2	79.0	138
20.0_rolling_ave_inv1	77.7	184
30.0_average_under	76.9	26
40.0_rolling_ave_inv2	76.9	13
10.0_rolling_ave_inv2	76.2	362
30.0_straddler_1	75.0	8
10.0_average_under	74.1	81
10.0_rolling_ave_inv1	69.5	1061
20.0_average_under	69.2	39
30.0_rolling_ave_inv2	67.6	34
30.0_flicking_down	67.0	209
40.0_rolling_ave_inv1	66.0	53
5.00_rolling_ave_inv2	64.2	2598
10.0_flicking_down	63.7	4518
40.0_flicking_down	62.5	144
10.0_rolling_ave_inv3	62.4	101
10.0_straddler_1	60.8	250
20.0_average_comp2	59.8	92
40.0_stepping_down	59.8	92
20.0_flicking_down	59.6	520
2.50_steady_down	58.9	151
2.50_rolling_ave_inv3	58.5	3017
5.00_rolling_ave_inv3	58.5	342
10.0_red_snapper	58.1	904
5.00_rolling_ave_inv1	57.6	8850
2.50_average_under	56.3	3932
5.00_average_comp2	56.2	4427
10.0_stepping_down	56.2	4427
20.0_red_snapper	55.6	225
20.0_old_above_new	55.5	3231
5.00_straddler_1	54.1	969
30.0_average_comp2	54.1	74
20.0_nino_nino_1	52.7	6415
5.00_average_comp	52.1	7182
5.00_average_under	51.9	540
10.0_stepping_up	51.8	8136
2.50_average_inter	51.7	6306
30.0_stepping_down	51.7	149
2.50_rolling_ave_inv2	51.6	20386
5.00_steady_rising2	51.3	456
5.00_steady_riser	51.0	480
10.0_old_above_new	51.0	24865
40.0_average_comp2	50.8	63
10.0_ski_jumping	50.0	4
2.50_average_comp	49.7	35203
5.00_stepping_up	49.5	36877
5.00_flicking_down	48.8	31908
10.0_new_above_old	48.1	29458
40.0_old_above_new	47.9	286
10.0_nino_nino_1	47.8	47571
5.00_flicking_up	47.5	34646
10.0_flicking_up	47.2	7815
30.0_old_above_new	47.2	816
5.00_red_snapper	47.2	2019
2.50_steady_rising2	46.7	19114
20.0_straddler_1	45.7	35
2.50_steady_riser	45.7	22512
5.00_new_above_old	45.7	84724
5.00_rolling_average2	45.6	13060
5.00_roll_average	45.6	13060
2.50_average_comp2	45.6	33850
5.00_stepping_down	45.6	33848
20.0_new_above_old	45.6	6597
2.50_ski_jumping	45.6	1137
2.50_straddler_1	45.5	1838
2.50_rolling_ave_inv1	45.3	49524
2.50_stepping_up	45.1	95901
5.00_average_inter	44.9	1173
2.50_flicking_up	44.7	90558
20.0_stepping_down	44.2	482
10.0_average_comp2	44.2	482
40.0_nino_nino_1	44.1	621
30.0_nino_nino_1	43.6	1660
2.50_roll_average	43.5	48681
2.50_rolling_average2	43.5	48681
2.50_new_above_old	42.7	150188
20.0_stepping_up	42.7	1866
2.50_koskosovich	42.0	5919
2.50_red_snapper	41.8	2541
10.0_roll_average	41.5	2325
10.0_rolling_average2	41.5	2325
5.00_old_above_new	41.2	93987
5.00_koskosovich	40.8	1766
5.00_nino_nino_1	40.2	178320
2.50_flicking_down	39.9	103828
30.0_straddler_2	39.4	4937
2.50_straddler_2	39.4	4937
5.00_straddler_2	39.4	4937
10.0_straddler_2	39.4	4937
40.0_straddler_2	39.4	4937
20.0_straddler_2	39.4	4937
10.0_average_comp	39.3	1505
30.0_new_above_old	39.1	2696
2.50_stepping_down	38.9	108307
20.0_flicking_up	38.3	1688
10.0_koskosovich	37.6	425
2.50_nino_nino_1	37.5	335711
2.50_old_above_new	37.2	179552
40.0_roll_average3	36.8	471797
20.0_roll_average3	36.8	476406
30.0_roll_average3	36.8	474583
5.00_roll_average3	36.8	479821
2.50_roll_average3	36.8	480332
10.0_roll_average3	36.7	478749
40.0_roll_average4	36.7	455680
30.0_roll_average4	36.7	456200
20.0_roll_average4	36.7	457262
10.0_roll_average4	36.6	458439
5.00_roll_average4	36.6	458975
2.50_roll_average4	36.6	459307
20.0_rolling_ave_inv3	36.4	11
30.0_red_snapper	35.6	59
5.00_ski_jumping	35.1	77
20.0_roll_average	32.8	595
20.0_rolling_average2	32.8	595
40.0_new_above_old	32.3	1522
30.0_stepping_up	32.1	1006
30.0_flicking_up	30.4	879
20.0_koskosovich	29.8	114
40.0_flicking_up	29.2	699
40.0_stepping_up	28.7	818
20.0_average_comp	28.7	745
30.0_average_comp	28.3	650
30.0_roll_average	27.8	356
30.0_rolling_average2	27.8	356
40.0_average_comp	26.7	585
10.0_average_inter	25.8	434
40.0_roll_average	25.3	285
40.0_rolling_average2	25.3	285
20.0_average_inter	24.2	339
30.0_koskosovich	23.8	42
40.0_average_inter	23.2	280
30.0_average_inter	22.2	315
40.0_koskosovich	21.7	23
40.0_red_snapper	7.7	13
40.0_rolling_ave_inv3	0.0	4
30.0_rolling_ave_inv3	0.0	4
</pre>
