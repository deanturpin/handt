#!/usr/bin/python3

import json
import requests

# Get coins
coins = []
c = open("coins.csv")
for coin in c:
    coins.append(coin.rstrip())

p = open("prices.csv", "w")
for coin in coins:
    url = ("https://min-api.cryptocompare.com/data/histohour?fsym="
        + coin + "&tsym=USD&limit=168&aggregate=1&e=CCCAGG")

    prices = requests.get(url).json();

    if prices:
        if prices["Response"] != "Error":
            series = []
            for spot in prices["Data"]:

                pivot = (float(spot["low"])
                    + float(spot["close"])
                    + float(spot["high"])) / 3

                series.append(pivot)

            p.write(coin + " ")
            for val in series:
                p.write("%f " % val)
            p.write("\n")
