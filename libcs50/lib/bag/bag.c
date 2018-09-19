//
//  bag.c
//
//
//
//

#include <stdio.h>
#include <stdlib.h>




/**************** local types ****************/
typedef struct bagitem{
    void *data;//pointer to data for this item
    void *next;
} bagitem_t;

/**************** global variables ****************/
typedef struct bag{
    struct bagitem *head;//pointer to data for this item
    void (*itemdelete)(void*data);
} bag_t;



/**************** global functions ****************/
/* that is, visible outside this file */
/**************** bag_new() ****************/
/*create a new empty bag data structure, return NULL if error*/

bag_t *bag_new(void(*itemdelete)(void *data)){
    bag_t *bag=malloc(sizeof(bag_t));
    
    if (bag==NULL){
        return NULL;
    } else {
        //initialize contents of tree structure
        bag->head=NULL;
        bag->itemdelete=itemdelete;
        return bag;
    }
}


/**************** local functions ****************/
/* not visible outside this file */
static bagitem_t *
bagitem_new(void *data){
    bagitem_t *item=malloc(sizeof(bagitem_t));
    if (item==NULL)
        return NULL;
    else{
        item->data=data;
        item->next=NULL;
        return item;
    }
    
}

/**************** global functions ****************/
/*add a new item to the bag*/
void bag_insert(bag_t *bag,void *data){
    bagitem_t *new_item=bagitem_new(data);
    
    if (bag==NULL){// if the bag is new, create a new bag and a new bag item, bag head pointers points to this new bag item
        return ;
        //bag=bag_new(data);
        //bag->head=new_item;
        //bag->head->next=NULL;
    }
    
    
    if (bag->head==NULL){//if head pointer is null, put it pointing to this new bag item
        bag->head=new_item;
        bag->head->next=NULL;
    }
    else{
        new_item ->next=bag->head;//set the next pointer of this new item pointing to the head pointer
        bag->head=new_item; ////put the head pointer pointing to the new bag item, and
}
}
/**************** global functions ****************/
/*remove any item from the bag*/
void *bag_extract(bag_t *bag){
    
    if (bag==NULL){ // if the bag is empty, return NULL
        return NULL;}
    else{ //remove any item from the bag and return it to the caller
        if (bag->head==NULL){
            return NULL;
        }
        
        bagitem_t *item=bag->head;
        void *data=item->data;
        bag->head=bag->head->next;
        free(item);
        return data;}
}

void bag_delete(bag_t *bag){
    if(bag!=NULL){
        for (bagitem_t*item=bag->head; item!=NULL;){
            if(bag->itemdelete!=NULL){
                (*bag->itemdelete)(item->data);
                bagitem_t *next=item->next;
                free(item);
                item=next;
                }
        }
    }
    free (bag);
    
}

/*bag iterate*/
void bag_iterate(bag_t *bag, void(* itemfunc)(void* arg, void*data), void *arg)
{
	if (bag==NULL || itemfunc ==NULL)
		return;
	
	for (bagitem_t *node=bag->head; node!=NULL; node=node->next)
		(*itemfunc)(arg,node->data);
	
}




