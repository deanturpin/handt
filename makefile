all: tmp prices.csv tmp/strategy.md

quick_run=
CXX = g++-6
cflags = -std=c++14 --all-warnings --extra-warnings -pedantic-errors \
	 -Wshadow -Wfloat-equal -Weffc++ -Wdelete-non-virtual-dtor

# Override to '-g --coverage' on the command line to generate codecov data
debug = -O3

tmp/%.o: %.cpp tmp
	$(CXX) -o $@ $< $(cflags) $(debug)

tmp:
	mkdir -p $@

prices.csv: tmp
	./get_prices.py $(quick_run) > $@

readme = readme.md
tmp/strategy.md: tmp/strategy.o prices.csv
	cat template.md > $(readme)
	@echo Generated $(shell TZ=BST-1 date) >> $(readme)
	time ./$< >> $(readme)
	cat $(readme)

clean:
	rm -rf tmp prices.csv
