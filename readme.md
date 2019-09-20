[![Build Status](https://travis-ci.org/deanturpin/handt.svg?branch=master)](https://travis-ci.org/deanturpin/handt)

**History is no indicator of future performance. Don't invest what you can't
afford to lose.**

*Have A Nice Day Trader* is an algorithmic trading platform that uses patterns
in historic prices to influence future trades. 80 days of prices are requested
for hundreds of currency pairs, then a library of strategies is backtested and
a summary is generated.

Run in Docker:
```bash
docker run deanturpin/handt
```

Prices are fetched using the [CryptoCompare
API](https://min-api.cryptocompare.com/). See the entry point in
[main.cpp](https://github.com/deanturpin/handt/blob/master/main.cpp) and [all
exchanges](https://min-api.cryptocompare.com/data/all/exchanges). The
strategies are defined in the
[low_frequency_trader.cpp](low_frequency_trader.cpp), the permutations and
thresholds are generated in [strategy.cpp](strategy.cpp).

Exchanges in use: Coinbase Binance
```
eb15dd7 Merge branch 'master' of https://github.com/deanturpin/handt
```
Generated Fri Sep 20 18:39:47 2019

* 2 threads
* 651 currency pairs
* 2,250 strategies
* 2,662,959,583 backtests

# Current prospects

Strategy|Pair|Exchange|Perf|Spot|Jitter %
---|---|---|---|---
Indifferent-Pomeranian-10|[RCN-BTC](https://www.cryptocompare.com/coins/RCN)|Binance|8/1|2.27e-06|1.06307
Indifferent-Pomeranian-7|[ZRX-EUR](https://www.cryptocompare.com/coins/ZRX)|Coinbase|7/0|0.2122|0.768323
Indifferent-Basenji-5|[RCN-BNB](https://www.cryptocompare.com/coins/RCN)|Binance|14/2|0.001092|1.09882
Darting-Pekingese-6|[SNM-BTC](https://www.cryptocompare.com/coins/SNM)|Binance|6/0|9.8e-07|1.01486
Leaping-Munchkin-3|[CONT-USDT](https://www.cryptocompare.com/coins/CONT)|Binance|5/0|0.02166|1.5285
Darting-Pomeranian-6|[ZRX-USDT](https://www.cryptocompare.com/coins/ZRX)|Binance|5/0|0.244|0.685066
Indifferent-Havanese-12|[YOYOW-ETH](https://www.cryptocompare.com/coins/YOYOW)|Binance|11/2|8.494e-05|1.02509
Indifferent-Pomeranian-8|[ZRX-EUR](https://www.cryptocompare.com/coins/ZRX)|Coinbase|5/1|0.2122|0.768323
Darting-Havanese-13|[DLT-ETH](https://www.cryptocompare.com/coins/DLT)|Binance|5/1|0.0002237|1.10467
Darting-Norrbottenspets-3|[ANKR-USDC](https://www.cryptocompare.com/coins/ANKR)|Binance|5/1|0.00294|1.21555
Leaping-Basenji-5|[FUEL-ETH](https://www.cryptocompare.com/coins/FUEL)|Binance|5/1|2.485e-05|1.28699

# 80-day backtest

Strategy|Pair|Exchange|Perf|Spot|Jitter %
---|---|---|---|---
Slouching-Norrbottenspets-17|[BTT-BTC](https://www.cryptocompare.com/coins/BTT)|Binance|15/1|6e-08|5.91851
Slouching-Xoloitzcuintli-14|[BTT-BTC](https://www.cryptocompare.com/coins/BTT)|Binance|13/1|6e-08|5.91851
Slouching-Xoloitzcuintli-15|[BTT-BTC](https://www.cryptocompare.com/coins/BTT)|Binance|13/1|6e-08|5.91851
Slouching-Xoloitzcuintli-16|[BTT-BTC](https://www.cryptocompare.com/coins/BTT)|Binance|12/1|6e-08|5.91851
Indifferent-Havanese-13|[YOYOW-ETH](https://www.cryptocompare.com/coins/YOYOW)|Binance|10/0|8.494e-05|1.02509
Indifferent-Xoloitzcuintli-11|[PHB-USDC](https://www.cryptocompare.com/coins/PHB)|Binance|10/0|0.00744|0.998845
Indifferent-Xoloitzcuintli-12|[PHB-USDC](https://www.cryptocompare.com/coins/PHB)|Binance|10/0|0.00744|0.998845
Slouching-Pekingese-11|[PHB-USDC](https://www.cryptocompare.com/coins/PHB)|Binance|10/0|0.00744|0.998845
Slouching-Pekingese-12|[PHB-USDC](https://www.cryptocompare.com/coins/PHB)|Binance|10/0|0.00744|0.998845
Slouching-Xoloitzcuintli-11|[PHB-USDC](https://www.cryptocompare.com/coins/PHB)|Binance|10/0|0.00744|0.998845
Slouching-Xoloitzcuintli-12|[PHB-USDC](https://www.cryptocompare.com/coins/PHB)|Binance|10/0|0.00744|0.998845
Indifferent-Cricket-13|[DOCK-BTC](https://www.cryptocompare.com/coins/DOCK)|Binance|11/1|1.05e-06|1.56111
Indifferent-Pomeranian-8|[YOYOW-ETH](https://www.cryptocompare.com/coins/YOYOW)|Binance|11/1|8.494e-05|1.02509
Slouching-Pekingese-17|[BTT-BTC](https://www.cryptocompare.com/coins/BTT)|Binance|11/1|6e-08|5.91851
Slouching-Xoloitzcuintli-17|[BTT-BTC](https://www.cryptocompare.com/coins/BTT)|Binance|11/1|6e-08|5.91851
Indifferent-Xoloitzcuintli-10|[PHB-USDC](https://www.cryptocompare.com/coins/PHB)|Binance|11/1|0.00744|0.998845
Slouching-Xoloitzcuintli-10|[PHB-USDC](https://www.cryptocompare.com/coins/PHB)|Binance|11/1|0.00744|0.998845
Slouching-Axolotl-6|[DUSK-BNB](https://www.cryptocompare.com/coins/DUSK)|Binance|11/1|0.00442|1.8013
Supine-Norrbottenspets-13|[WABI-BNB](https://www.cryptocompare.com/coins/WABI)|Binance|10/1|0.00671|1.21534
Darting-Axolotl-13|[DOCK-BTC](https://www.cryptocompare.com/coins/DOCK)|Binance|9/0|1.05e-06|1.56111
Darting-Jagdterrier-11|[DOCK-BTC](https://www.cryptocompare.com/coins/DOCK)|Binance|9/0|1.05e-06|1.56111

# Overall strategy performance
150 strategies

Darting-Bichon Frise|0/0
Darting-Lowchen|0/0
Darting-Mink|0/0
Darting-Narwahl|0/0
Darting-Ocelot|0/0
Darting-Papillon|0/0
Darting-Shih Tzu|0/0
Indifferent-Bichon Frise|0/0
Indifferent-Lowchen|0/0
Indifferent-Mink|0/0
Indifferent-Narwahl|0/0
Indifferent-Ocelot|0/0
Indifferent-Papillon|0/0
Indifferent-Shih Tzu|0/0
Leaping-Bichon Frise|0/0
Leaping-Lowchen|0/0
Leaping-Mink|0/0
Leaping-Narwahl|0/0
Leaping-Ocelot|0/0
Leaping-Papillon|0/0
Leaping-Shih Tzu|0/0
Slouching-Bichon Frise|0/0
Slouching-Lowchen|0/0
Slouching-Mink|0/0
Slouching-Narwahl|0/0
Slouching-Ocelot|0/0
Slouching-Papillon|0/0
Slouching-Shih Tzu|0/0
Straddling-Bichon Frise|0/0
Straddling-Lowchen|0/0
Straddling-Mink|0/0
Straddling-Narwahl|0/0
Straddling-Ocelot|0/0
Straddling-Papillon|0/0
Straddling-Shih Tzu|0/0
Supine-Bichon Frise|0/0
Supine-Lowchen|0/0
Supine-Mink|0/0
Supine-Narwahl|0/0
Supine-Ocelot|0/0
Supine-Papillon|0/0
Supine-Shih Tzu|0/0
Darting-Badger|272/336
Darting-Sphynx|4130/5550
Slouching-Bandicoot|37/53
Darting-Norrbottenspets|5996/8672
Darting-Xoloitzcuintli|4394/6542
Darting-Capybara|1485/2291
Slouching-Affenpinscher|1294/2083
Slouching-Munchkin|316/517
Slouching-Basenji|1650/2924
Supine-Bandicoot|651/1389
Supine-Affenpinscher|2054/4493
Slouching-Jagdterrier|1111/2675
Supine-Munchkin|2401/6600
Leaping-Bandicoot|1775/5264
Leaping-Badger|124/375
Supine-Basenji|2609/8258
Supine-Jagdterrier|3342/11032
Leaping-Sphynx|1056/3571
Darting-Shiba Inu|20080/70108
Leaping-Affenpinscher|8195/30862
Supine-Axolotl|8502/33386
Indifferent-Affenpinscher|22773/89997
Darting-Affenpinscher|22601/89458
Leaping-Xoloitzcuintli|775/3189
Leaping-Capybara|870/3613
Supine-Badger|2691/11344
Straddling-Badger|341/1491
Slouching-Axolotl|15639/68433
Leaping-Basenji|7334/32573
Darting-Griffon|26165/120172
Indifferent-Basenji|19583/90450
Darting-Basenji|19319/89360
Slouching-Cricket|19394/91457
Supine-Cricket|11511/54490
Straddling-Affenpinscher|821/3914
Leaping-Norrbottenspets|1725/8229
Indifferent-Badger|5032/24158
Leaping-Munchkin|6425/31336
Slouching-Badger|4846/23921
Leaping-Griffon|7088/35381
Leaping-Shiba Inu|5559/27914
Supine-Sphynx|13835/70747
Indifferent-Bandicoot|4992/25896
Darting-Bandicoot|4986/25865
Supine-Xoloitzcuintli|14549/76902
Indifferent-Sphynx|29690/162324
Darting-Munchkin|16751/93075
Indifferent-Munchkin|16778/93352
Indifferent-Xoloitzcuintli|30083/169346
Leaping-Pekingese|8805/49973
Leaping-Pomeranian|10845/61963
Straddling-Xoloitzcuintli|1768/10114
Slouching-Sphynx|27709/159436
Slouching-Xoloitzcuintli|28027/165851
Leaping-Jagdterrier|15215/90875
Indifferent-Jagdterrier|35452/215606
Darting-Jagdterrier|35357/215105
Darting-Pekingese|22488/140141
Straddling-Sphynx|1310/8208
Supine-Capybara|11301/73469
Straddling-Basenji|684/4550
Supine-Pekingese|17264/115086
Supine-Pomeranian|17553/117627
Leaping-Axolotl|17641/118874
Straddling-Capybara|1306/8979
Straddling-Bandicoot|171/1217
Darting-Pomeranian|28539/203903
Leaping-Cricket|18693/136258
Darting-Axolotl|43758/320976
Straddling-Pekingese|2247/16605
Indifferent-Axolotl|47501/351372
Straddling-Pomeranian|1961/14769
Indifferent-Capybara|21924/166407
Supine-Norrbottenspets|30723/238077
Slouching-Capybara|21185/165174
Straddling-Munchkin|563/4402
Straddling-Axolotl|1747/13750
Indifferent-Pekingese|41830/331806
Straddling-Norrbottenspets|3233/26395
Indifferent-Cricket|52104/432969
Indifferent-Pomeranian|46214/384478
Darting-Cricket|47321/394205
Slouching-Pekingese|30048/256190
Slouching-Pomeranian|30708/265503
Supine-Shiba Inu|34229/298004
Leaping-Havanese|21963/192860
Supine-Griffon|35520/312349
Straddling-Griffon|3564/31451
Indifferent-Norrbottenspets|59382/524276
Straddling-Jagdterrier|1358/12062
Slouching-Norrbottenspets|56509/518953
Straddling-Shiba Inu|3440/31830
Straddling-Cricket|1669/16788
Supine-Havanese|39361/396463
Indifferent-Shiba Inu|69472/735531
Straddling-Havanese|4358/46807
Indifferent-Griffon|72595/783821
Darting-Havanese|52732/574643
Slouching-Shiba Inu|64024/710057
Slouching-Griffon|65009/731719
Slouching-Havanese|68525/968066
Indifferent-Havanese|88841/1269816
Leaping-Lundehund|49140/791505
Supine-Lundehund|78255/1477785
Straddling-Lundehund|7695/177915
Slouching-Lundehund|148320/4312830
Darting-Lundehund|118590/5185125
Indifferent-Lundehund|164910/8679195

# sloccount
```
Have a non-directory at the top, so creating directory top_dir
Adding /home/travis/build/deanturpin/handt/backtest.h to top_dir
Adding /home/travis/build/deanturpin/handt/detailed_report.h to top_dir
Adding /home/travis/build/deanturpin/handt/low_frequency_trader.h to top_dir
Adding /home/travis/build/deanturpin/handt/parallel.h to top_dir
Adding /home/travis/build/deanturpin/handt/report.h to top_dir
Adding /home/travis/build/deanturpin/handt/strategy.h to top_dir
Adding /home/travis/build/deanturpin/handt/strategy_report.h to top_dir
Adding /home/travis/build/deanturpin/handt/trade.h to top_dir
Adding /home/travis/build/deanturpin/handt/backtest.cpp to top_dir
Adding /home/travis/build/deanturpin/handt/detailed_report.cpp to top_dir
Adding /home/travis/build/deanturpin/handt/low_frequency_trader.cpp to top_dir
Adding /home/travis/build/deanturpin/handt/main.cpp to top_dir
Adding /home/travis/build/deanturpin/handt/report.cpp to top_dir
Adding /home/travis/build/deanturpin/handt/strategy.cpp to top_dir
Adding /home/travis/build/deanturpin/handt/strategy_report.cpp to top_dir
Adding /home/travis/build/deanturpin/handt/trade.cpp to top_dir
Adding /home/travis/build/deanturpin/handt/get_all_coins.py to top_dir
Adding /home/travis/build/deanturpin/handt/get_coins.py to top_dir
Adding /home/travis/build/deanturpin/handt/get_prices.py to top_dir
Categorizing files.
Finding a working MD5 command....
Found a working MD5 command.
Computing results.


SLOC	Directory	SLOC-by-Language (Sorted)
627     top_dir         cpp=558,python=69


Totals grouped by language (dominant language first):
cpp:            558 (89.00%)
python:          69 (11.00%)




Total Physical Source Lines of Code (SLOC)                = 627
Development Effort Estimate, Person-Years (Person-Months) = 0.12 (1.47)
 (Basic COCOMO model, Person-Months = 2.4 * (KSLOC**1.05))
Schedule Estimate, Years (Months)                         = 0.24 (2.89)
 (Basic COCOMO model, Months = 2.5 * (person-months**0.38))
Estimated Average Number of Developers (Effort/Schedule)  = 0.51
Total Estimated Cost to Develop                           = $ 16,549
 (average salary = $56,286/year, overhead = 2.40).
SLOCCount, Copyright (C) 2001-2004 David A. Wheeler
SLOCCount is Open Source Software/Free Software, licensed under the GNU GPL.
SLOCCount comes with ABSOLUTELY NO WARRANTY, and you are welcome to
redistribute it under certain conditions as specified by the GNU GPL license;
see the documentation for details.
Please credit this data as "generated using David A. Wheeler's 'SLOCCount'."
```


