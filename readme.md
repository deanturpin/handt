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

Tue 29 May 08:04:41 BST 2018 - 
9be1616 Report exchange

# Recent recommendations
Potential trades from the top performing stategies below. See the [raw price data](prices.csv)

Exchange|From|To|Strategy
---|---|---|---
I|GOT|NOTHING|:(

# Strategy performance
Strategies are sorted by percentage of orders that returned a profit of at least 4.5 % within 48 hours. The more orders the greater the confidence in the result.
* 3 currency pairs polled
* 48-hour trade window
* 5784 opportunities to trade
* 16659 orders executed
<pre>
Strategy		%	Orders
10.0_flicking_down	100.0	3
20.0_nino_nino_1	100.0	1
10.0_rolling_ave_inv1	100.0	1
2.50_rolling_ave_inv3	66.7	6
2.50_koskosovich	58.3	36
5.00_new_above_old	55.9	666
2.50_rolling_ave_inv2	55.6	133
5.00_rolling_ave_inv1	52.5	40
2.50_rolling_average2	52.4	368
2.50_flicking_up	52.3	753
2.50_stepping_up	52.2	809
2.50_new_above_old	51.1	1432
2.50_roll_average	50.6	158
5.00_flicking_up	49.3	209
2.50_average_comp	48.5	204
5.00_stepping_up	48.4	215
2.50_rolling_ave_inv1	45.3	404
5.00_flicking_down	44.6	233
2.50_steady_rising2	43.0	244
10.0_nino_nino_1	42.1	285
5.00_old_above_new	40.9	777
5.00_nino_nino_1	40.5	1483
5.00_stepping_down	40.3	253
2.50_average_comp2	40.3	253
10.0_new_above_old	40.2	107
5.00_koskosovich	40.0	5
2.50_nino_nino_1	39.8	3215
10.0_old_above_new	39.0	154
2.50_flicking_down	38.4	961
5.00_rolling_average2	38.2	68
2.50_steady_riser	38.1	299
2.50_old_above_new	37.2	1780
2.50_stepping_down	35.7	1021
5.00_rolling_ave_inv2	33.3	6
5.00_roll_average	27.8	18
2.50_average_under	22.2	9
2.50_ski_jumping	20.0	5
2.50_average_inter	16.7	12
10.0_flicking_up	0.0	9
5.00_average_comp2	0.0	4
10.0_stepping_down	0.0	4
5.00_steady_rising2	0.0	3
5.00_steady_riser	0.0	3
10.0_rolling_average2	0.0	1
10.0_stepping_up	0.0	5
5.00_average_comp	0.0	4
</pre>
