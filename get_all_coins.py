#!/usr/bin/env python3

import json
import requests
from collections import deque

f = open("exchanges.txt")
exchange_names = deque(f.read().split())

try:
    url = "https://min-api.cryptocompare.com/data/all/coinlist"

    r = requests.get(url)
    coins = r.json();

    for coin in coins["Data"]:
        print(coin, coins["Data"][coin]["IsTrading"])

    # for exchange in exchanges:
    #     if exchange in exchange_names:
    #         for from_symbol in exchanges[exchange]:
    #             for to_symbol in exchanges[exchange][from_symbol]:
    #                 print(from_symbol, "\t", to_symbol, "\t", exchange)

except Exception as e:
    print("#", from_symbol, "generated exception: " + str(e))
