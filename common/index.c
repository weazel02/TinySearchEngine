/* 
 * index - a set of functions for creating, saving, loading the index
 * Created by: Wesley Thompson 
 * 
 */


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../libcs50/lib/hashtable/hashtable.h"
#include "../libcs50/lib/hashtable/jhash.h"
#include "../libcs50/lib/counters/counters.h"
#include "../common/file.h"
#include "index.h"


/*prototypes*/

static void save_word(void* arg, const char *key, void*data);
static void counters_func(void *arg, const int key, int count);

/******************* global function **********************/
/*index_new*/
/*create a new index_t data structure*/
index_t *index_new(const int num_slots,
				   void(*itemdelete)(void *data),
				   void(*itemprint)(FILE *fp, char *key, void *data))
{
	index_t *index=hashtable_new(num_slots,itemdelete,itemprint);

	return index;
}


/*index_find()*/
/*search given key in the hashtable, 
 return data for the given key, or NULL if not found*/
counters_t *index_find(index_t *index, char *key){
	if(index==NULL){
		return NULL;
	}

	else{
		return hashtable_find(index,key);
		
	}
}


/*insert given key and data in the hashtable, 
 return true if sucessfully inserted, otherwise return false */
bool index_insert(index_t *index, char* key, counters_t *ctrs){
	if(index==NULL){
		return false;
	}
	
	else{
		return hashtable_insert(index, key, ctrs);
		
	}
	
}


/*save from an index_t data structure in memory to an external index file*/
void index_save(char * indexFilename, index_t *index){
	//1.check parameters
	if(index==NULL ||indexFilename==NULL){
	 printf("error");
		return;
	 }
	
	FILE *fp=fopen(indexFilename, "w");
	if(fp==NULL){
		perror("error in open indexFilename.\n");
		return;
	}
	
	if(index==NULL){
		perror("error: index pointer is null.\n");
		return;
	}
	
	
	hashtable_iterate(index, save_word, fp);
	
	fclose(fp);
}



/*local function*/
/*operate on each hashtable set*/
static void save_word(void* arg, const char *key, void*data){
	FILE *fp=arg;

	
	if(fp!=NULL&&data!=NULL){
		fprintf(fp,"%s",key);
		counters_iterate((counters_t*)data,counters_func,fp);
		fprintf(fp,"\n");}

}


static void counters_func(void *arg, const int key, int count){
	FILE*fp=arg;
	if(fp!=NULL){
		fprintf(fp, " %d %d",key,count);}
}


/*load from an external index file to an index_t data structure in memory*/
index_t *index_load(index_t *index, char *oldIndexFilename){
	
	FILE *fp;
	fp=fopen(oldIndexFilename,"r");
	if(fp==NULL){
		printf("error");
		fclose(fp);
		return NULL;
	}
	
	
	 //or could use lines_in_file(fp) to get word count
	 //hashtable_t *index=index_new(wordcount);
	 
	char *word;
	
	/*read by word from oldIndexFilename*/
	while( (word=readword(fp)) !=NULL){
	/*create a word counters to store docID and count*/
	counters_t *word_count = counters_new();
		
		
		int docID;
		int count;
		/*get(docID,count)pairs*/
		while(fscanf(fp, "%d %d ", &docID, &count)==2){
			/*set the count according to (docID, count)pairs*/
			counters_set(word_count, docID,count);}

		
		/*update index data structure*/
		index_insert(index,word,word_count);
		free(word);

		}
	
		fclose(fp);
	
	return index;
	
}


/*delete index*/
void index_delete(index_t *index){
	if (index==NULL){
		return ;
	}
	
	else{
		hashtable_delete(index);
	}
	
}
