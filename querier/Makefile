# Makefile for ‘querier’ module
# Wesley Thompson

PROG = querier
OBJS = querier.o
LIBS = -lcurl
LLIBS = ../libcs50/lib/cs50ds.a ../common/common.a

CFLAGS = -Wall -pedantic -std=c11 -ggdb -D_POSIX_SOURCE
CC = gcc
MAKE = make


# build the indexer
	
$(PROG): $(OBJS) $(LLIBS)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

# build the library
../lib/cs50ds.a:
	cd ..;cd libcs50;cd lib; $(MAKE)

../common/common.a:
	cd ..;cd common; $(MAKE)







# crawler source dependencies; add others as needed
#crawler.o: ../common/web.h ../lib/memory/memory.h ../lib/bag/bag.h ../lib/hashtable/#hashtable.h
#web.o: web.h



.PHONY: clean
	
clean:
	rm -f *~
	rm -f *.o
	rm -f $(PROG)
	#cd ..;	cd lib; $(MAKE) clean
	#cd ..; 	cd common; $(MAKE) clean
