all: tmp tmp/prices.csv tmp/strategy.md

CXX = g++-6
cflags = -std=c++14 --all-warnings --extra-warnings -pedantic-errors \
	 -Wshadow -Wfloat-equal -Weffc++ -Wdelete-non-virtual-dtor

# Override to '-g --coverage' on the command line to generate codecov data
debug = -O3

tmp/%.o: %.cpp tmp
	$(CXX) -o $@ $< $(cflags) $(debug)

tmp:
	mkdir -p $@

tmp/prices.csv: pairs.csv
	./prices.py > $@

readme = readme.md
tmp/strategy.md: tmp/strategy.o tmp/prices.csv
	cat template.md > $(readme)
	@echo Generated $(shell TZ=BST-1 date) >> $(readme)
	time ./$< >> $(readme)
	cat $(readme)

clean:
	rm -rf tmp
