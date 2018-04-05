#!/bin/bash

TZ=HANDT-1 date

pushd test >& /dev/null

diff refresh.csv refresh2.csv && echo -e $'refresh\tpass' || echo $'refresh\tfail'
diff review.csv review2.csv && echo $'review\tpass' || echo $'review\tfail'
diff purge.csv purge2.csv && echo $'purge\tpass' || echo $'purge\tfail'
diff prospects1.csv prospects2.csv && echo $'prospec\tpass' || echo $'prospec\tfail'
diff consolidate.csv consolidate2.csv && echo $'consol\tpass' || echo $'consol\tfail'
diff balance1.csv balance2.csv && echo -e $'balance\tpass' || echo $'balance\tfail'

popd >& /dev/null
