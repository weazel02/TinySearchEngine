/* indexertest.c 
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
#include "../libcs50/hashtable.h"
#include "../libcs50/counters.h"
#include "../common/pagedir.h"
#include "../libcs50/freadline.h"
#include "../common/index.h"

FILE *fp;
char *curLine;
#define MAXLINES 1000
int lastLine = 0;
#define MAXLENGTH 250
char indexLines[MAXLINES][MAXLENGTH];
hashtable_t *index;
void OutputIndex(hashtable_t *table, char *file_name);
void printWord(void *arg, const char *key, void *item);
int main(int argc, char** argv){

	index = hashtable_new(MAXLINES * 10);
	fp = fopen(argv[1], "r");
	if (!fp) {
		printf("failed to open file\n");
		exit(1);
	}

	for (int n = 0; n < MAXLINES && !feof(fp); ) {
		if (freadLine(fp, indexLines[n], MAXLENGTH)) {
			n++; // only increment if no error
			printf("%s", indexLines[n]);
		}
	}
	for (int i = 0; i < MAXLENGTH; i++) {
		char curLine[strlen(indexLines[i])];
		strcpy(curLine, indexLines[i]);
		char *values[strlen(curLine)];
		/*
		   for (int i = 0; i < strlen(curLine); i++) {
		   values[i] = malloc(strlen(curLine));
		   memset(values[i], 0, strlen(curLine));
		   }
		   */
		char *curWord = malloc(strlen(curLine));
		char *key = malloc(strlen(curLine));
		int firstspace = 0;

		int word_idx = 0;
		for(int z = 0; z < strlen(curLine); z++){
			if(curLine[z] == ' '){
				if(firstspace == 1){
					char *newWord = malloc(strlen(curWord + 1));
					newWord[strlen(curWord)] = '\0';
					strcpy(newWord, curWord);
					values[word_idx++] = newWord;
					memset(curWord,0,strlen(curLine));
				}else{
					strcpy(key, curWord);
					counters_t *c_set = counters_new();
					hashtable_insert(index, key, c_set);
					memset(curWord,0,strlen(curLine));
				}
				firstspace = 1;
			} else{
				curWord = strncat(curWord, &curLine[z], 1);
			}
		}
		for( int c = 0; c < word_idx; c = c + 2) {
			
			counters_t *c_st = hashtable_find(index,key);
			
			for (int j = 0; j < atoi(values[c+1]); j++) {
				counters_add(c_st, atoi(values[c]));
			}
		}
	}
	OutputIndex(index, argv[2]);

}


