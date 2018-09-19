# Makefile for 'tse' module
#


MAKE = make
#C = common
#L = lib

all:
	$(MAKE) -C libcs50
	$(MAKE) -C common
#	$(MAKE) -C crawler
#	$(MAKE) all -C indexer
	$(MAKE) -C querier

.PHONY: clean
	
clean:
	rm -f *~
	$(MAKE) -C libcs50 clean
	$(MAKE) -C common clean
#	$(MAKE) -C crawler clean
#	$(MAKE) -C indexer clean
	$(MAKE) -C querier clean
