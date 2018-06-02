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

Sat  2 Jun 18:26:17 BST 2018 - 
a3ea0cb Use iterators and init lists to assign series

# Recent recommendations
Potential trades from the top performing stategies below. See the [raw price data](prices.csv)
<pre>
From	To	Strategy		Exch	Spot
I GOT NOTHING :(
</pre>

# Strategy performance
Strategies are sorted by percentage of orders that returned a profit of at least 6 % within 48 hours. The more orders the greater the confidence in the result.
* 3 currency pairs polled
* 48-hour trade window
* 5784 opportunities to trade
* 16099 orders executed
<pre>
Strategy		%	Orders
20.0_nino_nino_1	100.0	1
10.0_rolling_ave_inv1	100.0	1
10.0_flicking_down	66.7	3
2.50_rolling_ave_inv3	50.0	6
5.00_new_above_old	46.4	668
2.50_koskosovich	45.9	37
2.50_rolling_ave_inv2	44.9	118
2.50_stepping_up	43.5	791
2.50_new_above_old	43.4	1424
2.50_flicking_up	42.8	750
5.00_rolling_ave_inv1	40.0	40
2.50_roll_average	40.0	160
2.50_rolling_average2	39.9	361
5.00_stepping_up	36.8	212
5.00_flicking_up	36.5	208
2.50_average_comp	36.3	201
5.00_rolling_ave_inv2	33.3	6
5.00_flicking_down	33.2	211
2.50_rolling_ave_inv1	33.1	384
2.50_steady_rising2	32.6	239
10.0_new_above_old	29.8	104
2.50_nino_nino_1	29.7	3171
5.00_rolling_average2	29.4	68
5.00_stepping_down	29.2	216
2.50_average_comp2	29.2	216
2.50_steady_riser	27.9	297
5.00_nino_nino_1	27.9	1426
5.00_old_above_new	27.9	728
10.0_nino_nino_1	27.8	248
10.0_old_above_new	27.1	140
2.50_flicking_down	26.7	911
2.50_old_above_new	25.9	1713
5.00_roll_average	23.5	17
2.50_stepping_down	22.8	959
5.00_koskosovich	20.0	5
2.50_average_under	11.1	9
2.50_average_inter	8.3	12
2.50_ski_jumping	0.0	5
10.0_flicking_up	0.0	9
5.00_average_comp2	0.0	4
10.0_stepping_down	0.0	4
5.00_steady_rising2	0.0	3
5.00_steady_riser	0.0	3
10.0_rolling_average2	0.0	1
10.0_stepping_up	0.0	5
5.00_average_comp	0.0	4
</pre>
