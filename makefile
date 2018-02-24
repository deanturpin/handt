all: coins.csv source trades summary.csv index.html

# All the C++ source files
source:
	make -j 4 $(patsubst %.cpp, %.o, $(wildcard *.cpp))

# Fetch the prices from the exchanges
prices.csv: coins.csv
	./exchange.py > $@

coins.csv:
	./all_coins.py > $@

summary.csv: summary.o trades
	./$< > $@

trades: trade.o prices.csv
	./$<

index.html: trades
	./create_index.sh > index.html

cc=g++
%.o: %.cpp
	$(cc) -O3 -Wall -Wextra -pedantic -std=gnu++14 -o $@ $<

clean:
	rm -f prices.csv *.o
	echo 0 > coinindex.txt

cron:
	while :; do make tidy all; sleep 20s; done

tidy:
	rm -f coins.csv
