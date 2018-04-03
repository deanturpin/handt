#!/bin/bash

TZ=HANDT-1 date

pushd test >& /dev/null

diff refresh.csv refresh2.csv >& /dev/null && \
  echo -e $'refresh\tpass' || echo $'refresh\tfail'
diff review.csv review2.csv >& /dev/null && \
  echo $'review\tpass' || echo $'review\tfail'
diff prospects1.csv prospects2.csv >& /dev/null && \
  echo $'prospec\tpass' || echo $'prospec\tfail'
diff consolidate.csv consolidate2.csv >& /dev/null && \
  echo $'consol\tpass' || echo $'consol\tfail'
diff index.html index2.html >& /dev/null && \
  echo $'index\tpass' || echo $'index\tfail'

../alert.o && echo $'alert\tpass' || echo $'alert\tfail'

popd >& /dev/null
