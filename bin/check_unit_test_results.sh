#!/bin/bash

pushd test >& /dev/null

# Simple tests
diff --brief refresh.csv refresh2.csv && echo -e $'refresh\tpass' || echo $'refresh\tfail'
diff --brief review.csv review2.csv && echo $'review\tpass' || echo $'review\tfail'
diff --brief purge.csv purge2.csv && echo $'purge\tpass' || echo $'purge\tfail'

# Tests that need two results files
diff --brief prospects1.csv prospects2.csv && echo $'prospec\tpass' || echo $'prospec\tfail'

# Only check Line counts as timestamps differ
linecoun11=$(cat consolidate.csv | wc -l)
linecount2=$(cat consolidate2.csv | wc -l)
[[ $linecoun11 == $linecount2 ]] && echo $'consol\tpass' || echo $'consol\tfail'

popd >& /dev/null

