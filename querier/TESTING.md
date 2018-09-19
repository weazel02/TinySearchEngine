# TESTING for querier

## 1.Test argument checks

~~~~
Empty Query: ./querier
Error: Please enter the correct number of arguments (2).
Incorrect PageDirectory: ./querier test ./ 
Error: The entered directory needs to be one produced by the crawler.
Incorrect Index Directory: ./querier ../data/crawlerDirectory test
Error: The entered index directory cannot be written to.
~~~~

## 2. Test for invalid query

~~~~
./querier ../data/crawlerDirectory ../data/crawlerDirectory/index

Try entering:
" " (just spaces) Error: Empty query. Must enter valid query input.
1234 (just numbers) Error: The character '1'is not allowed in the query.
how are you? (input with punctuation) Error: The character '?'is not allowed in the query.
and resources (and first) Error: 'and' cannot be the first entered word.
or resources (or first) Error: 'or' cannot be the first entered word.
hello and or(and/or next to each other) Error: 'and' and 'or' cannot be next to one another.

## 3. Test for valid query

./querier ../data/crawlerDirectory ../data/crawlerDirectory/index

dartmouth and resources 

Result Query:
dartmouth and resources 
Matches 9 documents (ranked):
score   3 docID     6 : http://old-www.cs.dartmouth.edu/~cs50/Resources/
score   1 docID     1 : http://old-www.cs.dartmouth.edu/~cs50/index.html
score   1 docID     3 : http://old-www.cs.dartmouth.edu/~cs50/Labs/Lab0-Preliminaries.html
score   1 docID     4 : http://old-www.cs.dartmouth.edu/~cs50/Project/
score   1 docID     5 : http://old-www.cs.dartmouth.edu/~cs50/Labs/
score   1 docID     7 : http://old-www.cs.dartmouth.edu/~cs50/Logistics/
score   1 docID     8 : http://old-www.cs.dartmouth.edu/~cs50/Reading/
score   1 docID     9 : http://old-www.cs.dartmouth.edu/~cs50/Lectures/
score   1 docID    10 : http://old-www.cs.dartmouth.edu/~cs50/
-------------------------------------------------------------------------
dartmouth or resources 

Result Query:
dartmouth or resources 
Matches 10 documents (ranked):
score  12 docID     7 : http://old-www.cs.dartmouth.edu/~cs50/Logistics/
score   9 docID     6 : http://old-www.cs.dartmouth.edu/~cs50/Resources/
score   7 docID     2 : http://old-www.cs.dartmouth.edu/~xia/
score   2 docID     1 : http://old-www.cs.dartmouth.edu/~cs50/index.html
score   2 docID     3 : http://old-www.cs.dartmouth.edu/~cs50/Labs/Lab0-Preliminaries.html
score   2 docID     4 : http://old-www.cs.dartmouth.edu/~cs50/Project/
score   2 docID     5 : http://old-www.cs.dartmouth.edu/~cs50/Labs/
score   2 docID     8 : http://old-www.cs.dartmouth.edu/~cs50/Reading/
score   2 docID     9 : http://old-www.cs.dartmouth.edu/~cs50/Lectures/
score   2 docID    10 : http://old-www.cs.dartmouth.edu/~cs50/
------------------------------------------------------------------------

computer science or dartmouth
Result Query:
computer science or dartmouth 
Matches 10 documents (ranked):
score  12 docID     7 : http://old-www.cs.dartmouth.edu/~cs50/Logistics/
score   9 docID     2 : http://old-www.cs.dartmouth.edu/~xia/
score   3 docID     6 : http://old-www.cs.dartmouth.edu/~cs50/Resources/
score   2 docID     1 : http://old-www.cs.dartmouth.edu/~cs50/index.html
score   2 docID    10 : http://old-www.cs.dartmouth.edu/~cs50/
score   1 docID     3 : http://old-www.cs.dartmouth.edu/~cs50/Labs/Lab0-Preliminaries.html
score   1 docID     4 : http://old-www.cs.dartmouth.edu/~cs50/Project/
score   1 docID     5 : http://old-www.cs.dartmouth.edu/~cs50/Labs/
score   1 docID     8 : http://old-www.cs.dartmouth.edu/~cs50/Reading/
score   1 docID     9 : http://old-www.cs.dartmouth.edu/~cs50/Lectures/
--------------------------------------------------------------------------

computer science     
Result Query:
computer science 
Matches 4 documents (ranked):
score   2 docID     2 : http://old-www.cs.dartmouth.edu/~xia/
score   1 docID     1 : http://old-www.cs.dartmouth.edu/~cs50/index.html
score   1 docID     7 : http://old-www.cs.dartmouth.edu/~cs50/Logistics/
score   1 docID    10 : http://old-www.cs.dartmouth.edu/~cs50/
-------------------------------------------------------------------------
