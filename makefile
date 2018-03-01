# all: coins.csv source trades summary.csv index.html
all: symbols.csv prices.csv prospects.csv

# All the C++ source files
source:
	make -j 4 $(patsubst %.cpp, %.o, $(wildcard *.cpp))

# Get the currency list
symbols.csv: symbols.py
	./$< > $@

# Fetch the prices from the exchanges
prices.csv: prices.py symbols.csv
	./$< > $@

prospects.csv: prospects.o prices.csv
	./$< > $@

# Update existing positions
update.csv: update.o prices.csv
	./$< > $@

# trades: trade.o prices.csv
# 	./$<
# 
# summary.csv: summary.o trades
# 	./$< > $@
# 
# index.html: trades
# 	./create_index.sh > index.html

cc=g++
%.o: %.cpp
	$(cc) -Wall -Werror -Wextra -pedantic -std=gnu++14 -o $@ $<

clean:
	rm -f prices.csv *.o
	echo 0 > coinindex.txt

cron:
	while :; do make tidy all; sleep 1m; done

autotest: test.o
	./$< > results2.txt
	@diff results.txt results2.txt

tidy:
	rm -f coins.csv
