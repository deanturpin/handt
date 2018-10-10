#!/usr/bin/env python3

import sys
import json
import requests

try:
    url = "https://min-api.cryptocompare.com/data/all/exchanges"

    r = requests.get(url)
    exchanges = r.json();

    for exchange in exchanges:
        if exchange == "Coinbase" or exchange == "Kraken":
            for from_symbol in exchanges[exchange]:
                for to_symbol in exchanges[exchange][from_symbol]:
                    print(from_symbol, "\t", to_symbol, "\t", exchange)

except Exception as e:
    print("#", from_symbol, "generated exception: " + str(e))
