#!/usr/bin/python3

import json
import requests

batch_size = 10
index = 0

try:
    coinindex = open("coinindex.txt")
    index = int(coinindex.read())
    coinindex.close();
except Exception as e:
    do = "nothing"

# Get the list of coins we're interested in
coins = []
c = open("symbols.csv")
for coin in c:
    coins.append(coin.rstrip())

if index > len(coins):
    index = 0

# Put a subset of coins in the wallet
wallet = []
if len(coins):
    for x in range(0, batch_size):
        wallet.append(coins[index])
        index += 1
        if index >= len(coins):
            index = 0

# Write the index back
# coinindex = open("coinindex.txt", "w")
# coinindex.write(str(index))

# Fetch prices for each coin
for coin in wallet:

    # Construct URL
    url = ("https://min-api.cryptocompare.com/data/histohour?fsym="
        + coin + "&tsym=USD&limit=168&aggregate=1&e=CCCAGG")

    try:
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

    except Exception:
        do = "nothing"
