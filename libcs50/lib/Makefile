#   Builds and compiles all the data structures into a library.
#   Updated Makefile for lab6

OBJS = bag/bag.o set/set.o hashtable/hashtable.o memory/memory.o hashtable/jhash.o counters/counters.o ../../common/file.o
LIB = cs50ds.a

CFLAGS = -Wall -pedantic -std=c11 -ggdb
CC = gcc
MAKE = make

$(LIB): $(OBJS)
	ar cr $@ $^

# add other targets for the other .o files

memory/memory.o: memory/memory.c memory/memory.h
	cd memory; $(MAKE) memory.o
bag/bag.o:bag/bag.c bag/bag.h
	cd bag;	$(MAKE) bag.o
set/set.o:set/set.c set/set.h
	cd set; $(MAKE) set.o
counters/counters.o:counters/counters.c counters/counters.h ../../common/file.o
	cd counters; $(MAKE) counters.o
hashtable/hahstable.o:hashtable/hashtable.c hashtable/hashtable.h hashtable/jhash.h
	cd hashtable; $(MAKE) hashtable.o

# add cleanup commands for other subdirectories
.PHONY: clean
	
clean:
	rm -f *~
	rm -f *.o
	rm -f $(LIB)
	cd memory; $(MAKE) $@
	cd bag; $(MAKE) $@
	cd set; $(MAKE) $@
	cd hashtable; $(MAKE) $@
	cd counters; $(MAKE) $@
