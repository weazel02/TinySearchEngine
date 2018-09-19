CC = gcc
CFLAGS = -Wall -pedantic -std=c11 -ggdb

indexer:  indexer.o ../libcs50/hashtable.o ../libcs50/jhash.o ../libcs50/memory.o ../common/pagedir.o ../libcs50/file.o ../libcs50/counters.o ../common/index.o
	$(CC) $(CFLAGS) -o indexer indexer.o ../libcs50/hashtable.o ../libcs50/jhash.o ../libcs50/memory.o ../common/pagedir.c ../libcs50/file.o ../libcs50/counters.o ../common/index.o
indexer.o: indexer.c ../libcs50/hashtable.h ../libcs50/jhash.h ../libcs50/memory.h ../common/pagedir.h ../libcs50/file.h ../libcs50/counters.h ../common/index.h
	$(CC) $(CFLAGS) -c indexer.c 

indextest: indextest.o ../libcs50/hashtable.o ../libcs50/jhash.o ../libcs50/memory.o ../common/pagedir.o ../libcs50/file.o ../libcs50/counters.o ../libcs50/freadline.o ../common/index.o
	$(CC) $(CFLAGS) -o indextest indextest.o ../libcs50/hashtable.o ../libcs50/jhash.o ../libcs50/memory.o ../common/pagedir.c ../libcs50/file.o ../libcs50/counters.o ../libcs50/freadline.o ../common/index.o

indextest.o: indextest.c ../libcs50/hashtable.h ../libcs50/jhash.h ../libcs50/memory.h ../common/pagedir.h ../libcs50/file.h ../libcs50/counters.h ../libcs50/freadline.h ../common/index.h
	$(CC) $(CFLAGS) -c indextest.c

#list.o: list.c list.h common.h
#		$(CC) $(CFLAGS) -c list.c

#hashtable.o: hashtable.c common.h
#		$(CC) $(CFLAGS) -c hashtable.c

#web.o: ../libcs50/web.c ../libcs50/web.h 
#		$(CC) $(CFLAGS) -c ../libcs50/web.c

clean:
	rm indexer.o
	rm indextest.o

all: indexer indextest
