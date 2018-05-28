all: prices.csv strategy.md

quick_run =
CXX = g++-6
cflags = -std=c++14 --all-warnings --extra-warnings -pedantic-errors \
	 -Wshadow -Wfloat-equal -Weffc++ -Wdelete-non-virtual-dtor

# Override to '-g --coverage' on the command line to generate codecov data
debug = -O3

%.o: %.cpp
	$(CXX) -o $@ $< $(cflags) $(debug)

prices.csv:
	./get_prices.py $(quick_run) > $@

readme = readme.md
strategy.md: strategy.o prices.csv
	cat template.md > $(readme)
	@echo '$(shell TZ=BST-1 date) - ' >> $(readme)
	@git log --oneline -1 >> $(readme)
	time ./$< >> $(readme)
	cat $(readme)

clean:
	rm -f prices.csv strategy.o
