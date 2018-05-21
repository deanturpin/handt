#!/usr/bin/env python3

import json
import requests
from collections import deque

batch_size = 60
index = 0

# Get the list of coins we're interested in
f = open("pairs.csv")
tokens = deque(f.read().split())

while tokens:

    from_symbol = tokens.popleft()
    to_symbol = tokens.popleft()

    # Construct URL
    url = ("https://min-api.cryptocompare.com/data/histohour?fsym="
    + from_symbol + "&tsym=" + to_symbol + "&limit=2000&extraParams=brightcoin.uk"
    + "&e=Binance&tryConversion=false")

    print("#", url)
    try:
        # Check the response is a good one
        r = requests.get(url)
        prices = r.json();

        if prices:
            if prices["Response"] != "Error":

                series = []
                for spot in prices["Data"]:

                    # The pivot is the average of three of the prices
                    # https://en.wikipedia.org/wiki/Pivot_point_(technical_analysis)
                    pivot = (float(spot["low"])
                        + float(spot["close"])
                        + float(spot["high"])) / 3

                    series.append(pivot)

                print(from_symbol, to_symbol, end=" ")
                for val in series:
                    print(val, end=" ")
                print("")

            else:
                print("# " + from_symbol + " error: " + r)

    except Exception:
        do = "nothing"
