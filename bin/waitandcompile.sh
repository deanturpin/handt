#!/bin/bash

# Script to compile and run a C++ file when it is saved

[[ $# == 0 ]] && echo "Usage: $0 <file to watch>" && exit -1

echo Wait for $1

base=${1%.*}

echo Using standard ${std:-c++14}

while :; do
	
	inotifywait -qe modify $base.cpp -qe modify include/*.h
	clear

	g++ -I include -Wall -std=${std:-c++1y} -o $base.o $base.cpp && echo && sleep .1 && ./$base.o
done
