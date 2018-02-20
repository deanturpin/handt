#!/bin/bash

git="https://github.com/deanturpin/trading_strategies"
date=$(date --utc)

cat <<!
<!DOCTYPE html>

<meta charset="UTF-8">
<meta name="robots" content="index,follow" />
<meta http-equiv="refresh" content="60" />
<link rel=icon href="favicon.ico" sizes="any">

<style>
body { font-family: sans-serif; }
p#disclaimer { width: 50%; }
</style>

<title>LFT</title>
<p id="disclaimer">History is no indicator of future performance. Don"t invest
what you can"t afford to lose. Prices fetched periodically from <a
href="https://www.cryptocompare.com/api/" target="blah">CryptoCompare</a>.
</p>

<p id="pagegen">Page generated $date. </p>

<h2>Summary</h2>
<pre>
$(file=summary.csv; [[ -e $file ]] && cat $file)
</pre>

<h2>Buy</h2>
<pre>
$(file=buys.csv; [[ -e $file ]] && cat -n $file)
</pre>

<h2>Sell</h2>
<pre>
$(file=sells.csv; [[ -e $file ]] && cat -n $file)
</pre>

<h2>git log</h2>
<pre>
$(git log -n 5 --oneline)
</pre>
!
