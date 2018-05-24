all: prices.csv prospects.csv

CXX = clang++
debug = -O3
cflags = -std=c++14 --all-warnings --extra-warnings -pedantic-errors \
	 -Wshadow -Wfloat-equal -Weffc++ -Wdelete-non-virtual-dtor

%.o: %.cpp
	$(CXX) -o $@ $< $(cflags) $(debug)

prices.csv: pairs.csv pairs_short.csv
	./prices.py > $@

readme = readme.md
prospects.csv: prospects.o prices.csv
	cat template.md > $(readme)
	@echo Generated $(shell TZ=BST-1 date) >> $(readme)
	time ./$< >> $(readme)
	cat $(readme)

clean:
	rm -f *.o
	rm -f prices.csv
