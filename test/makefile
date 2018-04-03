all: source
	../refresh.o > refresh2.csv
	diff refresh.csv refresh2.csv || echo FAIL
	../review.o > review2.csv
	diff review.csv review2.csv || echo FAIL

source:
	make -C ../ $@
