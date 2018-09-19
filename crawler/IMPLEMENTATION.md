Crawler.c 

##Implemenation

getLinks():
1. Check to see if eneter URL is valid
2. If the URL is valid, get the html links on the page. Loop through them while some still remain.
3. If valid, insert to hashtable to and continue traversing.
4. If we have no visited the link before, add it to the set of pages so we can print them to a file later
5. Free all used temporary variables

main():

1. Validate command line arguments
2. Initialize seed page
3. Open the first file to write to
4. Call getLinks() to fill set of pages
5. While there are still some in the set, print the html each to a unique document.

P.S.: Due to memory errors I restricted the depth the crawler could crawl.
