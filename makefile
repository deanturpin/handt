all: tmp tmp/haveanicedaytrader

CXX = g++-8
cflags = --std=c++17 --all-warnings --extra-warnings --pedantic-errors \
	 -Werror -Wshadow -Wfloat-equal -Weffc++ -Wdelete-non-virtual-dtor \
	 -O3

tmp/%.o: %.cpp
	$(CXX) -c -o $@ $< $(cflags)

tmp:
	 mkdir $@
	./get_prices.py

# Generate documentation
readme = readme.md
tmp/haveanicedaytrader: tmp/prices.o tmp/backtest.o tmp/report.o tmp/main.o tmp/perms.o
	$(CXX) -o $@ $^ -lstdc++fs
	./$@ > tmp/strategy.txt
	cat template.md > $(readme)
	echo Generated $(shell TZ=GMT-1 date) >> $(readme)
	head -200 tmp/strategy.txt >> $(readme)
	head -60 readme.md

# All intermediate files are stored in tmp, so just remove it
clean:
	rm -rf tmp

cleanobjects:
	rm -rf tmp/*.o
