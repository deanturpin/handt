all: tmp prices.csv strategy.md

CXX = g++-8
cflags = -std=c++17 --all-warnings --extra-warnings -pedantic-errors \
	 -Wshadow -Wfloat-equal -Weffc++ -Wdelete-non-virtual-dtor \
	 -lstdc++fs -O3

%.o: %.cpp
	$(CXX) -o $@ $< $(cflags)

tmp:
	 mkdir $@

prices.csv:
	./get_prices.py > $@

readme = readme.md
strategy.md: strategy.o prices.csv
	cat template.md > $(readme)
	@echo '$(shell TZ=BST-1 date) - ' >> $(readme)
	@git log --oneline -1 >> $(readme)
	./$< >> $(readme)
	cat $(readme)

clean:
	rm -f prices.csv strategy.o
