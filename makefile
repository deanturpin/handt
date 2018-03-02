all: review.csv prospects.csv consolidate.csv stats positions.csv

# All the C++ source files
source:
	make -j 4 $(patsubst %.cpp, %.o, $(wildcard *.cpp))

symbols.csv: symbols.py
	./$< > $@

prices.csv: prices.py symbols.csv
	./$< > $@

refresh.csv: refresh.o prices.csv
	./$< > $@
	rm -f positions.csv

review.csv: review.o refresh.csv
	./$< > $@

prospects.csv: prospects.o prices.csv
	./$< > $@

consolidate.csv: consolidate.o review.csv prospects.csv
	./$< > $@

stats:
	@wc -l *.csv

positions.csv:
	cp consolidate.csv positions.csv

# summary.csv: summary.o trades
# 	./$< > $@
# 
# index.html: trades
# 	./create_index.sh > index.html

cc=clang++
%.o: %.cpp
	$(cc) -Wall -Werror -Wextra -pedantic -std=gnu++14 -o $@ $<

clean:
	rm -f *.csv *.o

cron:
	while :; do make tidy all; sleep 1m; done

tidy:
	rm -f coins.csv
