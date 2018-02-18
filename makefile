all: source prices trades index

# All the C++ source files
source: $(patsubst %.cpp, %.o, $(wildcard *.cpp))

# Fetch the prices from the exchanges
prices: prices.csv
prices.csv: coins.csv
	./exchange.py

trades: trade.o prices
	./$<

index: index.html
index.html: trades
	./create_index.sh > index.html

cc=g++
%.o: %.cpp
	$(cc) -Wall -Wextra -pedantic -std=c++14 -o $@ $<

clean:
	rm -f prices.csv *.o

cron:
	while :; do make clean all; sleep 2m; done
