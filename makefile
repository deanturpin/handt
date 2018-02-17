
all: source
source: $(patsubst %.cpp, %.o, $(wildcard *.cpp))

cc=g++

%.o: %.cpp
	$(cc) -Wall -Wextra -pedantic -std=c++14 -o $@ $<

clean:
	rm -f buys.txt
	rm *.o
