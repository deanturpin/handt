#!/bin/bash

git="https://github.com/deanturpin/trading_strategies"
date=$(date --utc)
coins=$(cat coins.csv | wc -l)

cat <<!
<!DOCTYPE html>

<meta charset="UTF-8">
<meta name="robots" content="index,follow" />
<meta http-equiv="refresh" content="60" />
<link rel=icon href="favicon.ico" sizes="any">

<style>
body { font-family: sans-serif; }
</style>

<title>LFT</title>
<p id="disclaimer">History is no indicator of future performance. Don"t invest
what you can"t afford to lose. Prices fetched periodically from <a
href="https://www.cryptocompare.com/api/" target="blah">CryptoCompare</a>. See
the source on <a href="$git" target="blah">GitHub</a>.</p>

<p id="pagegen">Processed $coins coins. Page generated $date. </p>

<h2>Open</h2>
<pre>
$(cat buys.csv)
</pre>

<h2>Closed</h2>
<pre>
$(cat sells.csv)
</pre>

<h2>git log</h2>
<pre>
$(git log -n 5 --oneline)
</pre>
!
