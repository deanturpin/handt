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
</style>

<h1>Have a nice day trader</h1>
<p id="disclaimer">History is no indicator of future performance. Don't invest
what you can"t afford to lose. Prices fetched periodically from <a
href="https://www.cryptocompare.com/api/" target="blah">CryptoCompare</a>.</p>

<h2>Summary</h2>
<pre>
$date
$(file=summary.csv; [[ -e $file ]] && cat $file)
</pre>

<h2>Coinbase</h2>
<pre>
$(grep -h -E '\<ETH\>|\<BTC\>|\<BCH\>|\<LTC\>' positions.csv || echo none)
</pre>

<h2>Poloniex</h2>
<pre>
$(grep -h -E '\<ETH\>|\<BTC\>|\<ETC\>|\<XRP\>|\<LTC\>|\<BCH\>|\<XMR\>|\<STR\>|\<NXT\>|\<ZEC\>|\<DASH\>|\<REP\>' positions.csv || echo none)
</pre>

<h2>Change log</h2>
<pre>
$(git log -n 5 --oneline)
</pre>

<h2>Positions</h2>
<pre>
$(file=positions.csv; [[ -e $file ]] && cat -n $file)
</pre>
!
