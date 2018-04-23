all: source \
	review.csv purge.csv prospects.csv consolidate.csv \
       	index.html endofsession \
	autotest

source:
	make --jobs 4 $(patsubst %.cpp, %.o, $(wildcard *.cpp))
	# make --silent --jobs 4 $(patsubst %.cpp, %.o, $(wildcard *.cpp))

CXX=clang++
flags=-g -O0 -Wall -Werror -Wextra -pedantic -std=gnu++14 -I include
%.o: %.cpp
	$(CXX) $(flags) -o $@ $<

symbols.csv: symbols.py
	./$< > $@

prices.csv: prices.py symbols.csv
	./$< > $@

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

index.html: index.o consolidate.csv review.csv
	./$< > $@
	./create_index.sh >> $@

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

autotest:
	make --silent --directory test
