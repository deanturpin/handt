all: source trades summary.csv index.html

# All the C++ source files
source:
	make -j 4 $(patsubst %.cpp, %.o, $(wildcard *.cpp))

# Fetch the prices from the exchanges
prices.csv: coins.csv
	./exchange.py > $@

summary.csv: summary.o trades
	./$< > $@

trades: trade.o prices.csv
	./$<

index.html: trades
	./create_index.sh > index.html

alert: alert.o
	./$<

cc=g++
%.o: %.cpp
	$(cc) -O3 -Wall -Wextra -pedantic -std=gnu++14 -o $@ $<

clean:
	rm -f prices.csv *.o

cron:
	while :; do make tidy all alert; sleep 2m; done

tidy:
	rm -f prices.csv
