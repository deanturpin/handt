#!/bin/bash

results_dir=coverage
flags='--exclude-path=/usr/include/c++/ --exclude-path=/usr/include/'
coveralls="--coveralls-id=$COVERALLS_ID"

for obj in ../*.o; do
  kcov $coveralls $flags $results_dir ./$obj
done
