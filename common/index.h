/* 
 * index - a set of functions for creating, saving, loading the index
 * Created By: Wesley Thompson 
 * 
 */

#ifndef __INDEX_H
#define __INDEX_H

#include <stdio.h>
#include <stdbool.h>
#include "../libcs50/lib/hashtable/hashtable.h"
#include "../libcs50/lib/counters/counters.h"

/**************** global types ****************/
typedef hashtable_t index_t;


/******************* global function **********************/
/*index_new*/
/*create a new index_t data structure*/
index_t *index_new(const int num_slots,
				   void(*itemdelete)(void *data),
				   void(*itemprint)(FILE *fp, char *key, void *data));


/*index_find()*/
/*search given key in the hashtable,
 return data for the given key, or NULL if not found*/
counters_t *index_find(index_t *index, char *key);


/*insert given key and data in the hashtable,
 return true if sucessfully inserted, otherwise return false */
bool index_insert(index_t *index, char* key, counters_t *ctrs);


/*from an external index file to an index_t data structure in memory*/
index_t *index_load(index_t *index, char *oldIndexFilename);

/*save from an index_t data structure in memory to an external index file*/
void index_save(char * indexFilename, index_t *index);


/* delete index*/
void index_delete(index_t *index);


#endif // __INDEX_H
