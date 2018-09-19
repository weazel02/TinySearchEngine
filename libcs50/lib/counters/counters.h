//
//  counters.h
//  lab3
//
//  
//
#include <stdlib.h>
#ifndef counters_h
#define counters_h


#endif /* counters_h */
/**************** local types ****************/
typedef struct counter_node counter_node_t;

/**************** global types ****************/
typedef struct counters counters_t;


/**************** global functions ****************/
/**************** counters_new() ****************/
/*create a new counters data structure, initialize it to empty*/
counters_t *counters_new(void);

/**************** global functions ****************/
/**************** counters_add() ****************/
/*if key already exists, increment its counter; if not, add the key and set its counter to 1*/
void counters_add(counters_t *ctrs, int key);

/**************** global functions ****************/
/**************** counters_get() ****************/
/*get the counter of key; if the key doesn't exist, return 0*/
int counters_get(counters_t *ctrs, int key);

/**************** global functions ****************/
/**************** counters_delete() ****************/
/*delete the whole counters data structure*/
void counters_delete(counters_t *ctrs);


/* Set value of the counter indicated by key.
 * If the key does not yet exist, create a counter for it
 * and initialize its counter value to 'count'.
 * NULL counters is ignored.
 */
void counters_set(counters_t *ctrs, int key, int count);



/* Iterate over all counters in the set (in undefined order):
 * call itemfunc for each item, with (arg, key, count).
 */
int counters_iterate(counters_t *ctrs,
					  void (*itemfunc)(void *arg, const int key, int count),
					  void *arg);
counters_t *
counters_intersect(counters_t *countersA, counters_t *countersB);

void
counters_union(counters_t *countersA, counters_t *countersB);

void counters_sort(counters_t *ctrs, char*page_directory);
