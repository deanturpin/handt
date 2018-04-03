#!/bin/bash

cat <<!
<pre>
$(date --utc)
$(echo Index $(cat coinindex.txt) into $(grep -v '#' symbols.csv | wc -l) tradable coins)
</pre>

<h2>Change log</h2>
<pre>
$(git log -n 5 --oneline)
</pre>

<h2>Autotest</h2>
$(diff test/refresh.csv test/refresh2.csv && echo "refresh\tpass" || echo "refresh\tfail")
$(diff test/review.csv test/review2.csv && echo "review\tpass" || echo "review\tfail")
!
