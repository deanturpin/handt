#!/bin/bash

TZ=BST date

diff test/refresh.csv test/refresh2.csv >& /dev/null && echo -e $'refresh\tpass' || echo $'refresh\tfail'
diff test/review.csv test/review2.csv >& /dev/null && echo $'review\tpass' || echo $'review\tfail'
diff test/prospects1.csv test/prospects2.csv >& /dev/null && echo $'prospec\tpass' || echo $'prospec\tfail'
diff test/consolidate.csv test/consolidate2.csv >& /dev/null && echo $'consol\tpass' || echo $'consol\tfail'
diff test/index.html test/index2.html >& /dev/null && echo $'index\tpass' || echo $'index\tfail'
