/* set.c - Unordered collection of key value pairs 
 *
 * Created By: Wesley Thompson 
 * Date: 4/21/2017
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "set.h"
#include "memory.h"
/*
************ LOCAL TYPES *************
typedef struct setnode {
	const char *key;
	void *item;
	struct setnode *next;	
} setnode_t;
************ GLOBAL TYPES ************
typedef struct set {
	struct setnode *head;
} set_t;
*/
char *curKey;
static setnode_t *setnode_new(void *item, const char *key);

/************ set_new() ***************/
set_t *set_new(void){
	set_t *set = count_malloc(sizeof(set_t));
	
	//If the set is null and error has occurred 
	if (set == NULL){
		return NULL;
	}else {
	//Initialize the set structure by setting header node to null
		set->head = NULL;
		return set;
	}
}

/************ set_insert() **************/
bool set_insert(set_t *set, const char *key, void *item){
	//Check to see if the set,item,and key are all initialized
	if(set != NULL && item != NULL && key != NULL){
		//If they are, loop through the set to see if the key already appears in the set
		 for (setnode_t *node = set->head; node != NULL; node = node->next) {
			curKey = node->key;
			int ret = strcmp(curKey, key);
			//If the key is already in the set, return false
			if(ret == 0){
				return false;
			}
   		 }
		setnode_t *new = setnode_new(item,key);
		if (new != NULL) {
			new->next = set->head;
			set->head = new;
			return true;
		}
	}else {
		return false;	
	}
#ifdef MEMTEST
  count_report(stdout, "After set_insert");
#endif
}
/********* setnode_new() ***************/

static setnode_t * setnode_new(void *item, const char *key){
	setnode_t *node = count_malloc(sizeof(setnode_t));

	if(node == NULL) {
		return NULL;
	}else {
		node->item = item;
		node->key = key;
		node->next = NULL;
		return node;
	}
}

/************ set_iterate() ***************/

void set_iterate(set_t *set, void *arg, void (*itemfunc)(void *arg,const char *key, void *item)){
  if (set != NULL && itemfunc != NULL) {
    // call itemfunc with arg, on each item
    for (setnode_t *node = set->head; node != NULL; node = node->next) {
      (*itemfunc)(arg,node ->key, node->item);
    }
  }
}

/************ set_find() ****************/
void *set_find(set_t *set, const char *key){
	if (set != NULL && key != NULL){
		for (setnode_t *node = set->head; node != NULL; node = node->next) {
			if(strcmp(node->key,key)){
				return node->item;
			}
		}
		return NULL;
	}
	else {
		return NULL;
	}
}

/************** set_print() **************/
void set_print(set_t *set, FILE *fp,void (*itemprint)(FILE *fp, const char *key, void *item) ){
	if (fp != NULL) {
		if (set != NULL) {
			fputc('{', fp);
			for (setnode_t *node = set->head; node != NULL; node = node->next) {
			// print this node
				if (itemprint != NULL) {  // print the node's item 
	  				(*itemprint)(fp, node->key, node->item);
					fputc(',', fp);
				}
			}
			fputc('}', fp);
    		} 
		else {
			fputs("(null)", fp);
		}
      	}
}
/*************** set_delete() ***************/
void set_delete(set_t *set, void (*itemdelete)(void *item) ){
	if (set != NULL) {
		for (setnode_t *node = set->head; node != NULL; ) {
      			if (itemdelete != NULL) {		    // if possible...
        			(*itemdelete)(node->item);	    // delete node's item
      			}
      			setnode_t *next = node->next;	    // remember what comes next
      			count_free(node);			    // free the node
      			node = next;			    // and move on to next
    		}
    		count_free(set);
	}
	memset((void *)set, 0, sizeof(set_t));
}
setnode_t *set_getfirst(set_t *set){
	if (set->head != NULL) {
		setnode_t *temp = set->head;
		if (set->head->next != NULL) {
			set->head = set->head->next;
		}
		else {
			set->head = NULL;
		}
		return temp;
	}
	return NULL;
}




