#!/bin/bash

cat <<!

<h1>Autotest</h1>
<pre>
$(test/check_autotest_results.sh)
</pre>

!

# Git log summary
git log -n 1 --oneline > gitlog.txt

# Update closed positions
grep false review.csv >> closed.csv

exit 0
