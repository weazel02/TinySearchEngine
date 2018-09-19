//
//  set.h
//  lab3
//
//
//

#include <stdbool.h>

#ifndef set_h
#define set_h


#endif /* set_h */
/**************** local types ****************/
typedef struct set_node setnode_t;


/**************** global types ****************/
typedef struct set set_t;


/**************** global functions ****************/
/*create a new empty set data structure*/
set_t *set_new(void(*itemdelete)(void*data));


/**************** global functions ****************/
/*return data for the given key, or NULL if key is not found.*/
void *set_find(set_t *set, char *key);



/**************** global functions ****************/
/* return false if key already exists
 return true if new item was inserted
 return NULL if set is empty
 return false if other errors incurred*/
bool set_insert(set_t *set, char *key, void *data);

/*set_print
 adapted according to lab 3 solution code */
void set_print(FILE *fp, set_t *set);

/*delete the whole set*/
void set_delete(set_t *set);

/*set iterate*/
void set_iterate(set_t *set, void(*itemfunc)(void *arg, const char *key, void *data), void *arg);

