#!/bin/bash

cat <<!
<h1>Change log</h1>
<pre>
$(git log -n 5 --oneline)
</pre>

<h1>Autotest</h1>
<pre>
$(test/check_autotest_results.sh)
</pre>

!

# Update closed positions
grep false review.csv >> closed.csv

exit 0
