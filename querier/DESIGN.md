# Querier Design Spec
## Wesley Thompson


# Requirements spec
The querier shall:

1. Run from the command line with using the syntax:

~~~
./querier pageDirectory indexFilename
~~~

        * pageDirectory is a directory produced by compiling/running crawler.c 
        * indexFilename is an index file produced by compiling/running indexer.c

2. Use index.c to load the index specified by indexFilename into an index data structure.

3. Read search queries from stdin, until EOF or ^C.
	* Parse the query and print the resultant query 
	* Return the documents that match the query
	* Else no documents matched
	* Lastly rank the documents based on their query score and print them in decreasing order 


## Design Spec 
1. Parse the arguments then check to make sure the are indeed valid
        * pageDirectory is a directory produced by the crawler.c
        * indexFilename is an index file produced by the indexer.c

2. Next, Load the index from indexFile into an index data structure 

3. Receive input fron stdin and parse it. 
        * Check to make sure the query text is valid
        * If it is we can run the query function 


4. Validate query input checking that: 
        * the literal ‘and’ the literal ‘or’ are between andsequences
        * and/or are not at the beginning/end or adajcent to one another
	* characters that are not letters are not allowed

5. Run the querier
        * load the index making use of index.c
        * initialize andMatch to keep trach of and operation
        * initialize orMatch to keep track of or operation
	* scan the query, if it or is found we must update orMatch and resent andMatch to null

6. Sort the querier
        * Call counters_iterate with a counters_count function  to count the number of items
	* Add pointers to the individual elements to the array
        * Lastly, sort the array according to each items query score and print out the result for the user

7. Cleanup and Free Appropriately 
