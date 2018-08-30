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

Thu 30 Aug 18:19:23 BST 2018 - 
00fa881 Use structured binding for name/result
# Recent recommendations
Potential trades from the top performing stategies below. See the [raw price data](prices.csv)
<pre>
From	To	Strategy		Exch	Spot
I GOT NOTHING :(
</pre>
# Strategy back-test performance
Strategies are back-tested and sorted by percentage of orders that returned a profit of at least 5 % within 48 hours. The more orders the greater the confidence in the result.
* 14 currency pairs polled
* 26992 opportunities to trade
* 20116 orders executed
<pre>
Strategy		%	Orders
20.000_red_snapper	100.0	7
10.000_straddler_1	100.0	7
20.000_nino_nino_1	78.9	71
20.000_old_above_new	78.7	61
10.000_stepping_down	71.9	89
5.0000_average_comp2	71.9	89
10.000_flicking_down	68.3	82
10.000_rolling_ave_inv1	66.7	9
10.000_koskosovich	66.7	3
20.000_stepping_up	63.6	11
10.000_roll_average	62.5	8
10.000_average_comp	60.0	5
10.000_rolling_average2	55.6	18
10.000_red_snapper	54.4	57
5.0000_steady_rising2	53.8	13
5.0000_rolling_ave_inv1	52.6	232
10.000_flicking_up	51.6	64
10.000_old_above_new	50.1	804
30.000_old_above_new	50.0	2
30.000_nino_nino_1	50.0	2
5.0000_average_inter	50.0	6
5.0000_straddler_1	50.0	74
20.000_new_above_old	49.2	59
10.000_nino_nino_1	48.8	1195
5.0000_average_comp	47.9	48
5.0000_rolling_ave_inv2	46.2	39
5.0000_flicking_down	45.2	1121
5.0000_stepping_down	44.8	1182
10.000_stepping_up	44.4	54
5.0000_steady_riser	41.2	17
5.0000_koskosovich	40.9	22
5.0000_stepping_up	39.9	591
10.000_new_above_old	36.5	375
5.0000_flicking_up	36.5	581
5.0000_old_above_new	35.5	3628
5.0000_new_above_old	35.1	2033
5.0000_rolling_average2	34.7	190
5.0000_red_snapper	34.5	139
5.0000_nino_nino_1	34.5	5548
20.000_flicking_down	33.3	3
5.0000_roll_average	32.8	67
5.0000_straddler_2	27.9	298
10.000_straddler_2	27.9	298
20.000_straddler_2	27.9	298
30.000_straddler_2	27.9	298
40.000_straddler_2	27.9	298
30.000_new_above_old	23.1	13
20.000_flicking_up	16.7	6
5.0000_ski_jumping	0.0	1
</pre>
