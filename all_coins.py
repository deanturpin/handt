#!/usr/bin/python3

import json
import requests

url = "https://min-api.cryptocompare.com/data/all/coinlist"
r = requests.get(url)
prices = r.json();

for coin in prices["Data"]:
    if prices["Data"][coin]["IsTrading"] == True:
        print(coin)
