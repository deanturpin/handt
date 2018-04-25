#!/bin/bash

TZ=HANDT-1 date > date.txt

# Autotest results
bin/check_unit_test_results.sh > unit_test.txt

# Git log summary
git log -n 1 --oneline > gitlog.txt

# Update closed positions
grep false review.csv >> closed.csv

exit 0
