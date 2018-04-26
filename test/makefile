
all: unit_test

unit_test: source
	echo 10 > stats.txt
	../refresh.o > refresh2.csv
	../review.o > review2.csv
	../purge.o > purge2.csv
	../prospects.o > prospects2.csv
	../consolidate.o > consolidate2.csv

source:
	make -C ../ $@

coverage:
	../bin/kcov.sh
