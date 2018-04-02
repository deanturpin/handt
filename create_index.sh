#!/bin/bash

cat <<!
<pre>
$(date --utc)
$(echo Index $(cat coinindex.txt) into $(grep -v '#' symbols.csv | wc -l) tradable coins)
</pre>

<h2>Change log</h2>
<pre>
$(git log -n 5 --oneline)
$(git branch --list --all)
</pre>
!
