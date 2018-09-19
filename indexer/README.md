In order to compile run make all from inside the indexer directory.

In order to use the indexer use a command of the form:

./indexer pageDirectory indexFilename

where pageDirectory is the output of the crawler program and index filename is the file inwhich to store the new index.

In order to use the indextest program use a command of the form: 

./indextest oldIndexFilename newIndexFilename

where oldIndexFilename is the output of the indexer.c program and the newIndexFileName is where to store the recreated index file.
