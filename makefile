all: source stats \
	review.csv purge.csv prospects.csv consolidate.csv \
       	index.html endofsession \
	unittest

source:
	make --jobs 4 $(patsubst %.cpp, %.o, $(wildcard *.cpp))

CXX=clang++
flags=-g -Werror -Wall -Wextra -pedantic -std=gnu++14
%.o: %.cpp
	$(CXX) $(flags) -o $@ $<

symbols.csv:
	bin/symbols.py > $@

prices.csv: symbols.csv
	bin/prices.py > $@

refresh.csv: refresh.o prices.csv
	./$< > $@

review.csv: review.o refresh.csv
	./$< > $@

purge.csv: purge.o review.o review.csv
	./$< > $@

prospects.csv: prospects.o prices.csv
	./$< > $@

consolidate.csv: consolidate.o review.csv prospects.csv
	./$< > $@

endofsession:
	cp consolidate.csv positions.csv

update:
	rm -f prices.csv
	make

stats:
	bin/generate_stats.sh

index.html: index.o consolidate.csv review.csv
	./$< > $@

gitpull:
	git pull --quiet

clean:
	rm -f *.o index.html

cron:
	watch -d -n 60 make --silent update

docs:
	dot -T svg doc/handt.dot > doc/handt.svg

coverage:
	bin/kcov.sh

format:
	clang-format -i include/*.h *.cpp

unittest:
	make --silent --directory test
