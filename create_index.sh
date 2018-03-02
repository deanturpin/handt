#!/bin/bash

cat <<!
<pre>
$(date --utc)
$(echo Index $(cat coinindex.txt) into $(cat symbols.csv | wc -l) coins)

$(ls -rt *.csv | while read file; do wc -l $file; done)
</pre>

<h2>Change log</h2>
<pre>
$(git log -n 5 --oneline)
</pre>

<h2>Coinbase / Poloniex</h2>
<pre>
$(grep -I -E '\<ETH\>|\<BTC\>|\<BCH\>|\<ETC\>|\<XRP\>|\<LTC\>|\<BCH\>|\<XMR\>|\<STR\>|\<NXT\>|\<ZEC\>|\<DASH\>|\<REP\>' positions.csv)
</pre>
!
