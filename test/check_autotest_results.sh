#!/bin/bash

TZ=HANDT-1 date

pushd test >& /dev/null

# Clear down previous results
rm -f balance.csv

# Simple tests
diff --brief refresh.csv refresh2.csv && echo -e $'refresh\tpass' || echo $'refresh\tfail'
diff --brief review.csv review2.csv && echo $'review\tpass' || echo $'review\tfail'
diff --brief purge.csv purge2.csv && echo $'purge\tpass' || echo $'purge\tfail'

# Tests that need two results files
diff --brief prospects1.csv prospects2.csv && echo $'prospec\tpass' || echo $'prospec\tfail'
diff --brief balance1.csv balance2.csv && echo -e $'balance\tpass' || echo $'balance\tfail'

# Only check Line counts as timestamps differ
linecoun11=$(cat consolidate.csv | wc -l)
linecount2=$(cat consolidate2.csv | wc -l)
[[ $linecoun11 == $linecount2 ]] && echo $'consol\tpass' || echo $'consol\tfail'

popd >& /dev/null

