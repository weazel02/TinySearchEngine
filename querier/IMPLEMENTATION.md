# Querier Design Spec
## Wesley Thompson


## Implementation Spec 
1. Parse the arguments then check to make sure the are indeed valid
        * pageDirectory is a directory produced by the crawler.c (Inititalize char* to pageDirectory)
        * indexFilename is an index file produced by the indexer.c (Initialize char* to indexFilename)

2. Next, Load the index from indexFile into an index data structure (Index data structure is a hashtable of countersets)

3. Receive input fron stdin and parse it. 
        * Check to make sure the query text is valid (isValidQuery())
        * If it is we can run the query function  (queryStart())


4. Validate query input checking that (What isValidQuery checks for): 
        * the literal ‘and’ the literal ‘or’ are between andsequences
        * and/or are not at the beginning/end or adajcent to one another
	* characters that are not letters are not allowed

5. Run the querier (queryRun):
        * load the index making use of index.c
        * initialize andMatch to keep trach of and operation (Initialize char* andMatch)
        * initialize orMatch to keep track of or operation (Initialize char* orMatch)
	* scan the query (Loop through with for loop), if it or is found we must update orMatch and resent andMatch to null

6. Sort the querier
        * Call counters_iterate with a counters_count function  to count the number of items (counters_iterate(), counters_count())
	* Add pointers to the individual elements to the array 
        * Lastly, sort the array according to each items query score and print out the result for the user (sort array using counters_sort)

7. Cleanup and Free Appropriately (conditionalFree())

# Testing Spec

1.Check whether the arguments are valid or not
2.Test empty query
3.Test invalid query
4.Test valid query
