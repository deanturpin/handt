all: prices.csv prospects.csv

CXX=clang++
debug=-O3
flags=-std=c++14 -Weffc++ -Wall -Wextra -pedantic -pedantic-errors

%.o: %.cpp
	$(CXX) -o $@ $< $(flags) $(debug)

prices.csv: pairs.csv pairs_short.csv
	./prices.py > $@

prospects.csv: prospects.o prices.csv
	time ./$<

clean:
	rm -f *.o
	rm -f prices.csv
