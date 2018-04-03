all:
	../refresh.o > refresh2.csv
	diff refresh.csv refresh2.csv || echo FAIL
