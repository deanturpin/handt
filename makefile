all: source \
	review.csv purge.csv prospects.csv consolidate.csv \
       	balance.csv index.html endofsession \
	autotest

source:
	make --silent --jobs 4 $(patsubst %.cpp, %.o, $(wildcard *.cpp))

cc=g++
flags=-g -Wall -Werror -Wextra -pedantic -std=gnu++14 -I include
%.o: %.cpp
	$(cc) $(flags) -o $@ $<

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

balance.csv: balance.o review.csv
	./$<

endofsession:
	cp consolidate.csv positions.csv

update:
	rm -f prices.csv
	make

index.html: index.o consolidate.csv balance.csv review.csv
	./$< > $@
	./create_index.sh >> $@

gitpull:
	git pull --quiet

clean:
	rm -f *.o

cron:
	watch -d -n 60 make --silent update

docs:
	dot -T svg doc/handt.dot > doc/handt.svg

autotest:
	make --silent --directory test
	test/check_autotest_results.sh
