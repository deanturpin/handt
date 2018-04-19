#!/bin/bash

make clean
make cc=clang++ source

for obj in *.o; do kcov --exclude-path=/usr/include/ results ./$obj; done
