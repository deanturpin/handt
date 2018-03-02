all: review.csv prospects.csv consolidate.csv stats

# All the C++ source files
source:
	make -j 4 $(patsubst %.cpp, %.o, $(wildcard *.cpp))

symbols.csv: symbols.py
	./$< > $@

prices.csv: prices.py symbols.csv
	./$< > $@

refresh.csv: refresh.o prices.csv
	./$< > $@

review.csv: review.o refresh.csv
	./$< > $@

prospects.csv: prospects.o prices.csv
	./$< > $@

consolidate.csv: consolidate.o review.csv prospects.csv
	./$< > $@

stats:
	@wc -l *.csv

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
