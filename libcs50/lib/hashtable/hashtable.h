//
//  hashtable.h
//  lab3
//
//

#ifndef hashtable_h
#define hashtable_h


#endif /* hashtable_h */

/**************** global types ****************/
typedef struct hashtable hashtable_t;

/**************** global function ****************/
/* create a new empty hash table data structure */

hashtable_t* hashtable_new(const int num_slots,
						   void(*itemdelete)(void*data),
						   void(*itemprint)(FILE *fp, char *key, void *data));

/**************** global function ****************/
/*seach given key in the hashtable, return data for the given key, or NULL if not found */
void *hashtable_find(hashtable_t *ht, char *key);

/**************** global function ****************/
/*insert given key and data in the hashtable, return true if sucessfully inserted, otherwise return false */
bool hashtable_insert(hashtable_t *ht, char *key, void *data);

void hashtable_delete(hashtable_t *ht);

/*
 hashtable_print
 adapted according to solution code for lab3
 */
void *hashtable_print(FILE *fp, hashtable_t *ht);


void hashtable_iterate(hashtable_t *ht, void(*itemfunc)(void *arg, const char *key, void *data), void *arg);

