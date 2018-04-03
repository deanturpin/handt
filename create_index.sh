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
<pre>
$(diff --brief test/refresh.csv test/refresh2.csv && echo -e $'refresh\tpass' || echo $'refresh\tfail')
$(diff --brief test/review.csv test/review2.csv && echo $'review\tpass' || echo $'review\tfail')
$(diff --brief test/prospects1.csv test/prospects2.csv && echo $'prospec\tpass' || echo $'prospec\tfail')
$(diff --brief test/consolidate.csv test/consolidate2.csv && echo $'consol\tpass' || echo $'consol\tfail')
$(diff --brief test/index.html test/index2.html && echo $'index\tpass' || echo $'index\tfail')
</pre>
!
