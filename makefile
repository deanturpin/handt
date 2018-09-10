all: tmp handt

CXX = g++-8
cflags = -std=c++17 --all-warnings --extra-warnings -pedantic-errors \
	 -Wshadow -Wfloat-equal -Weffc++ -Wdelete-non-virtual-dtor \
	 -lstdc++fs

%.o: %.cpp
	$(CXX) -o $@ $< $(cflags)

tmp:
	 mkdir $@
	./get_prices.py

handt: handt.o
	./$^

# readme = readme.md
# strategy.md: strategy.o prices.csv
# 	cat template.md > $(readme)
# 	@echo '$(shell TZ=BST-1 date) - ' >> $(readme)
# 	@git log --oneline -1 >> $(readme)
# 	./$< >> $(readme)
# 	cat $(readme)

clean:
	rm -f *.o
	rm -rf tmp
