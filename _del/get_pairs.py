#!/usr/bin/env python3

import sys
import json
import requests
from collections import deque

# Get the list of coins we're interested in
f = open("pairs2.csv")
tokens = deque(f.read().split())

while tokens:

    from_symbol = tokens.popleft()
    to_symbol = tokens.popleft()
    exchange = tokens.popleft()

    # Crypto compare counts start at zero
    total_prices = 1999

    # Construct URL
    url = ("https://min-api.cryptocompare.com/data/histohour?fsym="
        + from_symbol + "&tsym=" + to_symbol + "&limit=" + str(total_prices)
        + "&extraParams=brightcoin.uk&e=" + exchange + "&tryConversion=false")

    try:
        # Check the response is a good one
        r = requests.get(url)
        prices = r.json();

        if prices:
            if prices["Response"] != "Error":

                series = []
                for spot in prices["Data"]:

                    # Just use the close price
                    pivot = float(spot["close"])
                    series.append(pivot)

                print(from_symbol)
                print(to_symbol)
                print(exchange)

                for val in series:
                    print(val)

            else:
                print("# " + from_symbol + " error: " + r)

    except Exception as e:
        print("#", from_symbol, "generated exception")
