all: source \
	symbols.csv prices.csv \
	refresh.csv review.csv purge.csv prospects.csv consolidate.csv \
       	stats index.html endofsession \
	unit_test

JOBS=4
CXX=clang++
flags=-g -O2 -Werror -Wall -Wextra -pedantic -pedantic-errors -std=gnu++14
%.o: %.cpp
	$(CXX) $(flags) -o $@ $<

# Don't let make remove intermediate files
objects = $(patsubst %.cpp, %.o, $(wildcard *.cpp))
.PRECIOUS: $(objects)

source:
	make --jobs $(JOBS) $(objects)

symbols.csv:
	bin/symbols.py > $@

prices.csv: symbols.csv
	bin/prices.py > $@

%.csv: %.o
	./$< > $@

.PHONY: refresh.csv review.csv purge.csv prospects.csv consolidate.csv index.html

refresh.csv: refresh.o prices.csv
	./$< > $@

review.csv: review.o refresh.o
	./$< > $@

purge.csv: purge.o review.csv
	./$< > $@

consolidate.csv: consolidate.o purge.csv prospects.csv
	./$< > $@

prospects.csv: prospects.o prices.csv
	./$< > $@

index.html: index.o consolidate.csv review.csv
	./$< > $@

endofsession:
	cp consolidate.csv positions.csv

update:
	rm -f symbols.csv prices.csv
	make

stats:
	bin/generate_stats.sh

gitpull:
	git pull --quiet

clean:
	rm -f *.o index.html

cron:
	watch -d -n 60 make update

docs:
	dot -T svg doc/handt.dot > doc/handt.svg

format:
	clang-format -i include/*.h *.cpp

unit_test: source
	make --silent --directory test
