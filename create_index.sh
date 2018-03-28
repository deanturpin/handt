#!/bin/bash

cat <<!
<pre>
$(date --utc)
$(echo Index $(cat coinindex.txt) into $(grep -v '#' symbols.csv | wc -l) coins)
</pre>

<h2>Change log</h2>
<pre>
$(git log -n 5 --oneline)
</pre>
!
