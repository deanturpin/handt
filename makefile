all: source prices trades

# All the C++ source files
source: $(patsubst %.cpp, %.o, $(wildcard *.cpp))

# Fetch the prices from the exchanges
prices: prices.csv
prices.csv: coins.csv
	./exchange.py

trades: trade.o prices
	./$<

cc=g++
%.o: %.cpp
	$(cc) -Wall -Wextra -pedantic -std=c++14 -o $@ $<

clean:
	rm -f prices.csv *.o
