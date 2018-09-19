/* indexer.c 
 *
 *
 *
 * Created By: Wesley Thompson
 *
 *
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../libcs50/file.h"
#include "../libcs50/hashtable/hashtable.h"
#include "../libcs50/counters/counters.h"
#include "../common/pagedir.h"
#include "../common/index.h"

int numOfSlots = 400;
FILE *fp;
char* LoadFile(char *dir, char *file_name);

int main(int argc, char** argv) {
	if(argc < 3){
		printf("Enter the crawler output directory and the file to store the index. 2 Arguments total.\n");
		exit(1);
	}
	hashtable_t *index = hashtable_new(numOfSlots);
	// load all documents in target directory
	char **file_names;
	char *doc_text, *curWord;
	int pos, doc_id;
	int num_files = GetFilenamesInDir(argv[1], &file_names);
	counters_t *temp_cset = counters_new();
	for (int i = 0; i < num_files; i++) {

		doc_text = LoadFile(argv[1], file_names[i]);
		doc_id = atoi(file_names[i]);

		pos = 0;
		while ((pos = GetNextWord(doc_text, pos, &curWord)) > 0) {
			if(strlen(curWord) > 3){
				NormalizeWord(curWord);
				//If the word is not contained in the hashtable, create a counter set and add it
				counters_t *value = (counters_t *) hashtable_find(index, curWord);

				if(!value){	
					counters_t *c_set = counters_new();
					counters_add(c_set, doc_id);
					hashtable_insert(index, curWord, c_set);
				}else{
					//If the word is already in the hashtable, retrieve the associated counter set and increment the appropriate count
					temp_cset = hashtable_find(index,curWord);
					counters_add(temp_cset,doc_id);
				}
			}


		}
		free(doc_text);
	}
  	OutputIndex(index, argv[2]);
}


char* LoadFile(char *dir, char *file_name) {
	FILE *file;
	char *content;			
	
	// Build the path string
	int path_len = strlen(dir) + strlen(file_name) + 2;
	char *path = malloc(path_len);
	memset(path, 0, path_len);
	strcat(path, dir);
	strcat(path, "/");
	strcat(path, file_name);
	path[path_len] = '\0';
	
	file = fopen(path, "r");
	content = malloc(sizeof(file));
	content = readfilep(file);
	fclose(file);
	free(path);

	return content;
}

