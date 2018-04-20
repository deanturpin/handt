#!/bin/bash

make clean
make cc=clang++ source

results_dir=kcov_results
flags='--exclude-path=/usr/include/c++/ --exclude-path=/usr/include/'

for obj in *.o; do
  kcov $flags $results_dir ./$obj
done
