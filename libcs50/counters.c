/* counters.c - Unordered collection of key value pairs 
 *
 * Created By: Wesley Thompson 
 * Date: 4/21/2017
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "counters.h"
#include "memory.h"

/************ LOCAL TYPES *************/
typedef struct countersnode {
	int key;
	int *item;
	struct countersnode *next;	
} countersnode_t;
/************ GLOBAL TYPES ************/
typedef struct counters {
	struct countersnode *head;
} counters_t;
int curKey;
static countersnode_t *countersnode_new(const int key);

/************ counters_new() ***************/
counters_t *counters_new(void){
	counters_t *counters = count_malloc(sizeof(counters_t));
	
	//If the counters is null and error has occurred 
	if (counters == NULL){
		return NULL;
	}else {
	//Initialize the counters structure by countersting header node to null
		counters->head = NULL;
		return counters;
	}
}

/************ counters_insert() **************/
void counters_add(counters_t *counters, const int key){
	int isDuplicate = 0;
	//Check to see if the counters,item,and key are all initialized
	if(counters != NULL && key >= 0){
		//If they are, loop through the counters to see if the key already appears in the counters
		 for (countersnode_t *node = counters->head; node != NULL; node = node->next) {
			curKey = node->key;
			if(curKey == key){
				//If the key is already contained in the set, increments its corresponding counter value by one 
				*(node->item) = *(node->item) + 1;
				isDuplicate = 1;
			}
		 }
		 if(isDuplicate == 0){
			countersnode_t *new = countersnode_new(key);
			if (new != NULL) {
				new->next = counters->head;
				counters->head = new;
			}	
		}
	}
#ifdef MEMTEST
  count_report(stdout, "After counters_insert");
#endif
}
/********* countersnode_new() ***************/

static countersnode_t * countersnode_new(const int key){
	countersnode_t *node = count_malloc(sizeof(countersnode_t));

	if(node == NULL) {
		return NULL;
	}else {
		node->item = count_malloc(sizeof(int));
		*(node->item) = 1;
		node->key = key;
		node->next = NULL;
		return node;
	}
}

/************ counters_iterate() ***************/
void counters_iterate(counters_t *counters, void *arg, void (*itemfunc)(void *arg, const int key, int count)){
	if (counters != NULL && itemfunc != NULL) {
	      	// call itemfunc with arg, on each item
    		for (countersnode_t *node = counters->head; node != NULL; node = node->next) {
      			(*itemfunc)(arg,node->key,*(node->item));
    }
  }
}

/************ counters_get() ****************/
int counters_get(counters_t *counters, const int key){
	if (counters != NULL && key >= 0){
		for (countersnode_t *node = counters->head; node != NULL; node = node->next) {
			if(node->key == key){
				return *(node->item);
			}
		}
		return 0;
	}
	else {
		return 0;
	}
}
/************** counters_set ****************/
void counters_set(counters_t *counters, const int key, int count){
	 if (counters != NULL && key >= 0){
		for (countersnode_t *node = counters->head; node != NULL; node = node->next) {
                        if(node->key == key){
				*(node->item) = count;
                        }
                }
	}
}
/************** counters_print() **************/
void counters_print(counters_t *counters, FILE *fp ){
	if (fp != NULL) {
		if (counters != NULL) {
			//fputc('{', fp);
			for (countersnode_t *node = counters->head; node != NULL; node = node->next) {
				// print this node
				if(node->next == NULL){
					fprintf(fp,"%i %i ",node->key,*(node->item));
				}else{
					fprintf(fp,"%i %i ",node->key,*(node->item));
				}	
			}

			//fputc('}', fp);
    		} 
		else {
			//fputs("(null)", fp);
		}
      	}
}
/*************** counters_delete() ***************/
void counters_delete(counters_t *counters){
	if (counters != NULL) {
		for (countersnode_t *node = counters->head; node != NULL; ) {
			if(node->item){
				count_free(node->item);
			}
			countersnode_t *next = node->next;	    // remember what comes next
			count_free(node);			    // free the node
			node = next;			    // and move on to next
		}
		count_free(counters);
	}
	memset((void *)counters, 0, sizeof(counters_t));
}

/************** counters_printf() **************/
void counters_printf(counters_t *counters){
                if (counters != NULL) {
                        //fputc('{', fp);i
                        //printf("%c",'{');
                        for (countersnode_t *node = counters->head; node != NULL; node = node->next) {
                                // print this node
                                if(node->next == NULL){
                                        printf("%i %i",node->key,*(node->item));
                                }else{
                                        printf("%i %i",node->key,*(node->item));
                                }
                        }
                        //printf("%c",'}');
                        //fputc('}', fp);
                }
                else {
                        //fputs("(null)", fp);
                        printf("%s","(null)");
                }
        }




