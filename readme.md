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
Generated Sat 26 May 10:34:27 BST 2018

# What's popping, bro?
Recent recommendations by the top performing stategies below. See the [raw price data](tmp/prices.csv)

|Currency pair|Strategy|
|---|---|
|[ARN_ETH](https://www.binance.com/trade.html?symbol=ARN_ETH)|20.0_old_above_new|
|[ARN_BTC](https://www.binance.com/trade.html?symbol=ARN_BTC)|20.0_old_above_new|

# Strategy performance
Strategies are sorted by percentage of orders that returned a profit of at least 5 % within 48 hours. The more orders the greater the confidence in the result.
* 315 pairs
* 315 series of prices
* 24 hours window size
* 48 hours look ahead
* 607320 periods processed
* 5396671 orders placed

|Strategy|%|Orders|
|---|---|---|
|30.0_ski_jumping|100.0|2|
|20.0_ski_jumping|100.0|2|
|30.0_average_under|76.9|26|
|30.0_straddler_1|75.0|8|
|10.0_average_under|74.1|81|
|20.0_average_under|69.2|39|
|10.0_flicking_down|68.8|4524|
|30.0_flicking_down|67.9|209|
|10.0_straddler_1|65.6|250|
|20.0_flicking_down|64.6|520|
|10.0_red_snapper|64.1|902|
|20.0_old_above_new|60.8|3231|
|5.00_straddler_1|60.7|967|
|10.0_stepping_down|60.6|4427|
|20.0_red_snapper|60.0|225|
|5.00_steady_rising2|59.1|450|
|5.00_steady_riser|58.6|473|
|20.0_ninonino_1|57.8|6419|
|5.00_average_comp|57.1|7202|
|10.0_old_above_new|56.9|24916|
|10.0_stepping_up|56.8|8158|
|5.00_average_under|55.9|540|
|5.00_stepping_up|55.3|36882|
|30.0_stepping_down|55.0|149|
|5.00_flicking_down|55.0|32044|
|5.00_red_snapper|54.0|2011|
|10.0_ninonino_1|53.9|47754|
|30.0_old_above_new|53.3|816|
|10.0_new_above_old|53.2|29471|
|5.00_flicking_up|52.9|34658|
|5.00_stepping_down|51.7|33983|
|5.00_new_above_old|51.6|84217|
|10.0_flicking_up|51.5|7845|
|5.00_roll_average|50.2|13080|
|10.0_ski_jumping|50.0|4|
|20.0_new_above_old|49.8|6602|
|20.0_stepping_down|49.4|482|
|5.00_average_inter|49.2|1181|
|30.0_ninonino_1|48.9|1660|
|20.0_straddler_1|48.6|35|
|5.00_old_above_new|47.4|94584|
|20.0_stepping_up|46.8|1870|
|5.00_ninonino_1|46.6|179309|
|30.0_straddler_2|45.7|4918|
|20.0_straddler_2|45.7|4918|
|5.00_straddler_2|45.7|4918|
|10.0_straddler_2|45.7|4918|
|10.0_roll_average|45.3|2341|
|5.00_koskosovich|44.0|1773|
|10.0_average_comp|43.7|1508|
|30.0_new_above_old|42.7|2699|
|20.0_flicking_up|42.0|1697|
|30.0_rolling_average2|42.0|387832|
|20.0_roll_average3|41.9|386747|
|20.0_roll_average4|41.9|390557|
|30.0_roll_average4|41.9|389124|
|30.0_roll_average3|41.9|384141|
|5.00_roll_average3|41.9|392290|
|5.00_rolling_average2|41.9|394375|
|10.0_rolling_average2|41.8|393717|
|10.0_roll_average3|41.8|391097|
|20.0_rolling_average2|41.8|391333|
|5.00_roll_average4|41.8|394099|
|10.0_roll_average4|41.8|393400|
|30.0_red_snapper|40.7|59|
|10.0_koskosovich|39.8|427|
|5.00_ski_jumping|37.7|77|
|20.0_roll_average|36.9|601|
|30.0_stepping_up|36.6|1006|
|30.0_flicking_up|34.6|887|
|30.0_average_comp|34.0|650|
|20.0_average_comp|33.8|745|
|20.0_koskosovich|33.0|115|
|30.0_roll_average|32.8|360|
|10.0_average_inter|31.0|436|
|20.0_average_inter|30.4|339|
|30.0_average_inter|28.9|315|
|30.0_koskosovich|22.7|44|
