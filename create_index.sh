#!/bin/bash

git="https://deanturpin.github.io/trading_strategies/"
date=$(date --utc)

cat <<!
<!DOCTYPE html>

<meta charset="UTF-8">
<meta name="robots" content="index,follow" />
<meta http-equiv="refresh" content="30" />
<link rel=icon href="favicon.ico" sizes="any">

<style>
body { font-family: sans-serif; }
</style>

<title>HANDT</title>
<h1>HAVE A NICE DAY TRADER</h1>

<p id="disclaimer">History is no indicator of future performance. Don't invest
what you can"t afford to lose. Prices fetched periodically from <a
href="https://www.cryptocompare.com/api/" target="blah">CryptoCompare</a>. See
the documentation on <a href="$git" target="blah">GitHub</a>.</p>

<h2>Summary</h2>
<pre>
$date
$(echo Index $(cat coinindex.txt) into $(cat coins.csv | wc -l) coins)
$(cat summary.csv)
</pre>

<h2>Coinbase</h2>
<pre>
$(grep -I -E '\<ETH\>|\<BTC\>|\<BCH\>|\<LTC\>' positions.csv || echo none)
</pre>

<h2>Poloniex</h2>
<pre>
$(grep -I -E '\<ETH\>|\<BTC\>|\<ETC\>|\<XRP\>|\<LTC\>|\<BCH\>|\<XMR\>|\<STR\>|\<NXT\>|\<ZEC\>|\<DASH\>|\<REP\>' positions.csv || echo none)
</pre>

<h2>Change log</h2>
<pre>
$(git log -n 5 --oneline)
</pre>

<h2>Positions</h2>
<pre>
$(cat -n positions.csv)
</pre>
!
