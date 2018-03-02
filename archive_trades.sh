#!/bin/bash

dir=archive

mkdir -p $dir

for file in *.csv; do
  date=$(date --utc | tr ' ' '-')
  newfile=$dir/$date-$file
  mv $file $newfile
done
