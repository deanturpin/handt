all: prices analysis tmp/haveanicedaytrader

CXX = g++-8
cflags = --std=c++17 --all-warnings --extra-warnings --pedantic-errors \
	 -Werror -Wshadow -Wfloat-equal -Weffc++ -Wdelete-non-virtual-dtor \
	 -O1 -mtune=native

tmp/%.o: %.cpp
	$(CXX) -c -o $@ $< $(cflags)

tmp:
	mkdir -p $@
	./get_coins.py > tmp/coins.txt

tmp/coins.txt: tmp
	./get_coins.py > $@

prices: tmp tmp/coins.txt
	./get_prices.py

analysis:
	 mkdir -p $@

objects: tmp
	@echo Using $(shell nproc) CPUs
	make -j $(shell nproc) tmp/trade.o tmp/backtest.o tmp/report.o \
	tmp/main.o tmp/strategy.o tmp/detailed_report.o tmp/strategy_report.o \
	tmp/low_frequency_trader.o

# Generate documentation
readme = tmp/readme.md
tmp/haveanicedaytrader: objects
	$(CXX) -o $@ tmp/*.o -lstdc++fs -lpthread -pg --coverage
	cat readme.md > $(readme)
	echo Exchanges in use\: $(shell cat exchanges.txt) >> $(readme)
	echo '```' >> $(readme)
	git log --pretty=oneline --abbrev-commit -n 1 >> $(readme)
	echo '```' >> $(readme)
	./$@ >> $(readme)
	echo '# sloccount' >> $(readme)
	echo '```' >> $(readme)
	sloccount *.h *.cpp *.py >> $(readme)
	echo '```' >> $(readme)
	head -60 $(readme)

# All intermediate files are stored in tmp and analysis, so just remove them
clean:
	rm -rf tmp analysis

cleanobjects:
	rm -rf tmp/*.o

profile: all
	gprof tmp/haveanicedaytrader | head -25
	gprof -l tmp/haveanicedaytrader | head -25
