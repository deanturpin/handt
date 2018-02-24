#!/usr/bin/python3

import json
import requests

url = "https://min-api.cryptocompare.com/data/all/coinlist"
r = requests.get(url)
prices = r.json();

for c in prices["Data"]:
    print(c)
