all: review.csv prospects.csv stats

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

# consolidate.csv: consolidate.o review.csv prospects.csv
	# ./$< > $@
	#

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
	# echo 0 > coinindex.txt

cron:
	while :; do make tidy all; sleep 1m; done

autotest: test.o
	./$< > results2.txt
	@diff results.txt results2.txt

tidy:
	rm -f coins.csv
