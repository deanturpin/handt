#!/bin/bash

cat <<!
<hr>
<h2>Change log</h2>
<pre>
$(git log -n 5 --oneline)
</pre>

<h2>Autotest</h2>
<pre>
$(test/check_autotest_results.sh)
</pre>
!
