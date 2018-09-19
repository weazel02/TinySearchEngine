CC = gcc
CFLAGS = -Wall -pedantic -std=c11 -ggdb

crawler:  crawler.o ../libcs50/hashtable.o ../libcs50/set.o ../libcs50/webpage.o ../libcs50/webpage_fetch.o ../libcs50/jhash.o ../libcs50/memory.o
		$(CC) $(CFLAGS) -o crawler  ../libcs50/hashtable.o ../libcs50/set.o ../libcs50/webpage.o ../libcs50/webpage_fetch.o ../libcs50/jhash.o ../libcs50/memory.o crawler.o -l curl

crawler.o: crawler.c   ../libcs50/set.h ../libcs50/hashtable.h ../libcs50/webpage.h ../libcs50/webpage_fetch.h ../libcs50/jhash.h ../libcs50/memory.h ../libcs50/webpage_internal.h
		$(CC) $(CFLAGS) -c crawler.c 

#list.o: list.c list.h common.h
#		$(CC) $(CFLAGS) -c list.c

#hashtable.o: hashtable.c common.h
#		$(CC) $(CFLAGS) -c hashtable.c

#web.o: ../libcs50/web.c ../libcs50/web.h 
#		$(CC) $(CFLAGS) -c ../libcs50/web.c

clean:
	rm -f *~ *.o
