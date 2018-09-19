//
//  bag.h
//  lab3
//
//

#ifndef bag_h
#define bag_h


#endif /* bag_h */

/**************** local types ****************/
typedef struct bagitem bagitem_t;

/**************** global variables ****************/
typedef struct bag bag_t;

/**************** global functions ****************/
/*create a new empty bag data structure, return NULL if error*/
bag_t *bag_new(void(*itemdelete)(void *data));


/**************** global functions ****************/
/*add a new item to the bag*/
void bag_insert(bag_t *bag,void *data);


/**************** global functions ****************/
/*remove any item from the bag and return the item to the caller
if the bag is empty, return NULL*/
void *bag_extract(bag_t *bag);

void bag_delete(bag_t *bag);

/*bag iterate*/
void bag_iterate(bag_t *bag, void(* itemfunc)(void* arg, void*data), void *arg);
