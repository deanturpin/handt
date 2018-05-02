all: source \
	symbols.csv prices.csv \
	refresh.csv review.csv purge.csv prospects.csv consolidate.csv \
       	stats index.html endofsession \
	unittest

# Don't let make remove intermediate files
objects = $(patsubst %.cpp, %.o, $(wildcard *.cpp))
.PRECIOUS: $(objects)

source:
	make --jobs 4 $(objects)

CXX=clang++
flags=-g -O2 -Werror -Wall -Wextra -pedantic -std=gnu++14
%.o: %.cpp
	$(CXX) $(flags) -o $@ $<

symbols.csv:
	bin/symbols.py > $@

prices.csv: symbols.csv
	bin/prices.py > $@

%.csv : %.o
	./$< > $@

index.html: index.o consolidate.csv review.csv
	./$< > $@

endofsession:
	cp consolidate.csv positions.csv

update:
	rm -f prospects.csv refresh.csv symbols.csv
	rm -f consolidate.csv prices.csv purge.csv review.csv
	make

stats:
	bin/generate_stats.sh

gitpull:
	git pull --quiet

clean:
	rm -f *.o index.html

cron:
	watch -d -n 60 make --silent update

docs:
	dot -T svg doc/handt.dot > doc/handt.svg

format:
	clang-format -i include/*.h *.cpp

unittest:
	make --silent --directory test
