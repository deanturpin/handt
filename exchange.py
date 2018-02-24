#!/usr/bin/python3

import json
import requests

# batch_size = 20
# index = open("index.txt")

# Get the list of coins we're interested in
coins = []
c = open("coins.csv")
for coin in c:
    coins.append(coin.rstrip())

# Fetch prices for each coin
for coin in coins:
    url = ("https://min-api.cryptocompare.com/data/histohour?fsym="
        + coin + "&tsym=USD&limit=168&aggregate=1&e=CCCAGG")

    # Check the response is a good one
    r = requests.get(url)
    prices = r.json();
    if prices:

        # Check the reply was good and extract the prices
        if prices["Response"] != "Error":
            series = []
            for spot in prices["Data"]:

                # The pivot is the average of three of the prices
                # https://en.wikipedia.org/wiki/Pivot_point_(technical_analysis)
                pivot = (float(spot["low"])
                    + float(spot["close"])
                    + float(spot["high"])) / 3

                series.append(pivot)

            print(coin, end=" ")
            for val in series:
                print(val, end=" ")
            print()
