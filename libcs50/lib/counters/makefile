#Mkefile for ‘counters’ module
#

CC = gcc
CFLAGS = -Wall -pedantic -std=c11 -ggdb
PROG = counterstest
OBJS = counterstest.o counters.o ../../../common/file.o
LIBS =

$(PROG): $(OBJS)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

counterstest.o: counters.h
counters.o: counters.h ../../../common/file.h
file.o: ../../../common/file.h
clean:
	rm -f *~
	rm -f *.o
	rm -rf $(PROG).dSYM
	rm -f $(PROG)

