#!/bin/bash

TZ=HANDT-1 date

pushd test >& /dev/null

diff refresh.csv refresh2.csv >& /dev/null && \
  echo -e $'refresh\tpass' || echo $'refresh\tfail'
diff review.csv review2.csv >& /dev/null && \
  echo $'review\tpass' || echo $'review\tfail'
diff purge.csv purge2.csv >& /dev/null && \
  echo $'purge\tpass' || echo $'purge\tfail'
diff prospects1.csv prospects2.csv >& /dev/null && \
  echo $'prospec\tpass' || echo $'prospec\tfail'
diff consolidate.csv consolidate2.csv >& /dev/null && \
  echo $'consol\tpass' || echo $'consol\tfail'
diff balance.csv balance2.csv >& /dev/null && \
  echo -e $'balance\tpass' || echo $'balance\tfail'

popd >& /dev/null
