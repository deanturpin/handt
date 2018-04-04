#!/bin/bash

cat <<!
<hr>
<h2>Balance</h2>
<pre>
$(cat balance.csv) USD
(Nominal initial balance of 1,000,000 USD and 1,000 USD trades)

Positions closed this period: $(grep false review.csv | wc -l)
</pre>

<h2>Change log</h2>
<pre>
$(git log -n 5 --oneline)
</pre>

<h2>Autotest</h2>
<pre>
$(test/check_autotest_results.sh)
</pre>
!
