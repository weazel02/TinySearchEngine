Indexer Design:

The indexer.c file takes in as input a file produced my the crawler program. Each file contains html data from the crawled pages.
The indexer takes the pages and reads each word (with some preprocessing).Each word is stored into hashtable along with a corresponding counter set.
The counter set maintains docid as keys and the frequency of the word in the docuemnt as the items. The indexer builds the hashtables and then prints in to a file making use of index.c.


IndexTest Design:

The indextest.c file takes in as input the output of the indexer.c. The indextest reads in each line individually and parse them around white spaces. The first word on each line is stored back into the hashtable and the rest of the values are later used to update the counterset corresponding with the current word. The indextest.c file then reprints the index to a new file.
