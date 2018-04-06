#!/bin/bash

cat <<!
<hr>
<pre>
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

# Update close positions
grep false review.csv >> closed.csv
