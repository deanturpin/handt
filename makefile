all: source \
	review.csv prospects.csv consolidate.csv index.html endofsession \
	autotest alert

source:
	make --silent -j 4 $(patsubst %.cpp, %.o, $(wildcard *.cpp))

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

prospects.csv: prospects.o prices.csv
	./$< > $@

consolidate.csv: consolidate.o review.csv prospects.csv
	./$< > $@

endofsession:
	cp consolidate.csv positions.csv

update:
	rm -f prices.csv
	make

index.html: index.o consolidate.csv
	./$< > $@
	./create_index.sh >> $@

gitpull:
	git pull --quiet

clean:
	rm -f *.o
	rm -f alert

cron:
	watch -d -n 60 make --silent update

docs:
	dot -T svg doc/handt.dot > doc/handt.svg

alert: consolidate.csv alert.o
	./alert.sh

autotest:
	make -C test

closeall: clean
	./archive_trades.sh
	rm -f _*.csv
