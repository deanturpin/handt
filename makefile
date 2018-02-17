all: source prices

# All the C++ source files
source: $(patsubst %.cpp, %.o, $(wildcard *.cpp))

# Fetch the prices from the exchanges
prices: prices.csv
	./exchange.py

cc=g++

%.o: %.cpp
	$(cc) -Wall -Wextra -pedantic -std=c++14 -o $@ $<

clean:
	rm -f buys.txt
	rm *.o
