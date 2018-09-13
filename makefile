all: tmp handt

CXX = g++-8
cflags = -std=c++17 --all-warnings --extra-warnings -pedantic-errors \
	 -Wshadow -Wfloat-equal -Weffc++ -Wdelete-non-virtual-dtor \
	 -lstdc++fs -O3

tmp/%.o: %.cpp
	$(CXX) -o $@ $< $(cflags)

tmp:
	 mkdir $@
	./get_prices.py

# Generate documentation
readme = readme.md
handt: tmp/handt.o
	./$^ | tee tmp/strategy.txt
	cat template.md > $(readme)
	echo Generated $(shell date) >> $(readme)
	cat tmp/strategy.txt >> $(readme)

# All intermediate files are stored in tmp, so just remove it
clean:
	rm -rf tmp
