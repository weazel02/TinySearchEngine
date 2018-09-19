# README. md for querier module
# Created By: Wesley Thompson
# Compiling 
In order to compile:
1. `make clean; make` at tse top level directory to compile all files associated with TSE or
2. `make clean; make` at querier direcotry to compile all files associated with querier.c

# Querier

The TSE querier reads queries from stdin and searches in the index file produced by the TSE indexer. 
The query then ranks and returns the results to the user. 


# Assumptions 

1.Inputs
* PageDirectory has files named 1, 2, 3, …, without gaps.
* The content of document files in pageDirectory is produced by crawler.c 
* The content of the file named by indexFilename is produced by indexer.c

2.Invalid Queries 
* ‘and’ comes between words, and ‘or’ must come between andsequences
* (‘and’ & ‘or’) cannot be adjacent
* characters other than letters or spaces are disallowed.

3.Query Score
* The query score for a document satisfying a conjunction wordA and wordB is 
 the minimum of the score for wordA and the score for wordB on this document.
* The query score for a document satisfying a disjunction wordA or wordB is the sum of the score for wordA and 
 the score for wordB on this document. 
