all: source trades index.html

# All the C++ source files
source: $(patsubst %.cpp, %.o, $(wildcard *.cpp))

# Fetch the prices from the exchanges
prices.csv: coins.csv
	./exchange.py

trades: trade.o prices.csv
	./$<

index.html: trades
	./create_index.sh > index.html

cc=g++
%.o: %.cpp
	$(cc) -g -Wall -Wextra -pedantic -std=gnu++14 -o $@ $<

clean:
	rm -f prices.csv *.o

cron:
	while :; do make clean all; sleep 2m; done

clear:
	rm -r buys.csv sells.csv
