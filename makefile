all: tmp analysis tmp/haveanicedaytrader

CXX = g++-8
cflags = --std=c++17 --all-warnings --extra-warnings --pedantic-errors \
	 -Werror -Wshadow -Wfloat-equal -Weffc++ -Wdelete-non-virtual-dtor \
	 -O3

tmp/%.o: %.cpp
	$(CXX) -c -o $@ $< $(cflags)

tmp:
	 mkdir -p $@
	./get_prices.py

analysis:
	 mkdir -p $@

objects:
	make -j $(shell nproc) tmp/trade.o tmp/backtest.o tmp/report.o \
	tmp/main.o tmp/perms.o tmp/detailed_report.o

# Generate documentation
readme = readme.md
tmp/haveanicedaytrader: objects
	$(CXX) -o $@ tmp/*.o -lstdc++fs
	cat template.md > $(readme)
	echo Generated $(shell TZ=GMT-1 date) >> $(readme)
	./$@ | head -100 >> $(readme)
	head -60 readme.md

# All intermediate files are stored in tmp and analysis, so just remove them
clean:
	rm -rf tmp analysis

cleanobjects:
	rm -rf tmp/*.o
