#!/usr/bin/python3

import json
import requests

# Get coins
coins = []
c = open("coins.csv")
for coin in c:
    coins.append(coin.rstrip())

for coin in coins:
    url = ("https://min-api.cryptocompare.com/data/histohour?fsym="
        + coin + "&tsym=USD&limit=168&aggregate=1&e=CCCAGG")

    prices = requests.get(url).json();

    if prices:
        if prices["Response"] == "Error":
            print("0 0 0 0")
        else:
            p = []
            for spot in prices["Data"]:

                pivot = (float(spot["low"])
                    + float(spot["close"])
                    + float(spot["high"])) / 3

                p.append(pivot)

            print(coin, end=" ")
            for val in p:
                print(val, end=" ")
            print()
