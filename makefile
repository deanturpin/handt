all: prices.csv prospects.csv

CXX=clang++
debug=
flags=-std=c++14 -Weffc++ -Wall -Wextra -pedantic -pedantic-errors

%.o: %.cpp
	$(CXX) -o $@ $< $(flags) $(debug)

prices.csv: pairs.csv pairs_short.csv
	bin/prices2.py > $@

prospects.csv: prospects.o prices.csv
	time ./$<

clean:
	rm -f *.o
	rm -f prices.csv
