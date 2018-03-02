all: source review.csv prospects.csv consolidate.csv stats positions.csv index.html

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
	$(shell grep false consolidate.csv > closed.csv)

stats:
	wc -l *.csv

positions.csv:
	cp consolidate.csv positions.csv

update:
	rm -f prices.csv
	make

summary.csv: summary.o consolidate.csv
	./$< > $@

index.html: summary.csv
	./create_index.sh > index.html

cc=clang++
%.o: %.cpp
	$(cc) -I include -Wall -Werror -Wextra -pedantic -std=gnu++14 -o $@ $<

clean:
	rm -f *.o

cron:
	watch -d -n 60 make --silent update
