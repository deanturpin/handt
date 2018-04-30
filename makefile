all: source stats \
	symbols.csv prices.csv \
	refresh.csv review.csv purge.csv prospects.csv consolidate.csv \
       	index.html endofsession \
	unittest

source:
	make --jobs 4 $(patsubst %.cpp, %.o, $(wildcard *.cpp))

CXX=clang++
flags=-g -O2 -Werror -Wall -Wextra -pedantic -std=gnu++14
%.o: %.cpp
	$(CXX) $(flags) -o $@ $<

timing=timing.txt

symbols.csv:
	date > $(timing)
	bin/symbols.py > $@
	date >> $(timing)
	@echo $@ >> $(timing)

prices.csv: symbols.csv
	bin/prices.py > $@
	date >> $(timing)
	@echo $@ >> $(timing)

%.csv : %.o
	./$< > $@
	date >> $(timing)
	@echo $@ >> $(timing)

index.html: index.o consolidate.csv review.csv
	./$< > $@
	date >> $(timing)
	@echo $@ >> $(timing)

endofsession:
	cp consolidate.csv positions.csv

update: clean
	rm -f timing.txt
	rm -f symbols.csv
	rm -f prices.csv
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
