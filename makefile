all: source
chain: review.csv prospects.csv consolidate.csv index.html endofsession

source:
	touch $@
	make -j 4 $(patsubst %.cpp, %.o, $(wildcard *.cpp))
	make chain

cc=g++
flags=-Wall -Werror -Wextra -pedantic -std=gnu++14
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
	$(shell grep true consolidate.csv > open.csv)
	$(shell grep false consolidate.csv > closed.csv)
	cp consolidate.csv positions.csv
	rm -f source

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

cron:
	watch -d -n 60 make --silent update

docs:
	dot -T svg doc/handt.dot > doc/handt.svg

closeall:
	./archive_trades.sh
