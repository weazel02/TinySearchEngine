//
//  hashtable.c
//  lab3
//
//
//

#include <stdio.h>
#include <stdlib.h>
#include "../set/set.h"
#include "jhash.h"

/**************** global types ****************/
typedef struct hashtable{
    long slot_num;
    set_t* *table; // table of pointers, each pointer pointing to a set
    void(*itemdelete)(void *data);
    
}hashtable_t;


/**************** global function ****************/
/* create a new empty hash table data structure */
hashtable_t* hashtable_new(const int num_slots,
						   void(*itemdelete)(void*data),
						   void(*itemprint)(FILE *fp, char *key, void *data)){
    
    hashtable_t *ht;  //use malloc to store num_slots array;
    
    // init hashtable
    ht = malloc(sizeof(hashtable_t));
    if(ht==NULL){
        return NULL;
    }
    
    ht->slot_num=num_slots;//initializing slot_num to num_slots of hashtable
    ht->itemdelete=itemdelete;
    
    
    //init the table array
    ht->table=malloc(num_slots*sizeof(set_t*));
    if(ht->table==NULL){
        free(ht);
        return NULL;
    }
    
    //create set in evey table slot. call set new funtion, initialize set, assign pointer to array element
    for (int i=0; i<num_slots; i++){
        set_t* s=set_new(itemdelete);
        if(s==NULL) {
            for(int j=0;j<i;j++){
                /*if there's failure in allocating memory for this set, free the memory allocated for previous sets*/
                free(ht->table[j]);
            }
            free(ht);
            return NULL; }
        ht->table[i]=s;}
    
    
    return ht;
}

/**************** global function ****************/
/*seach given key in the hashtable, return data for the given key, or NULL if not found */
void *hashtable_find(hashtable_t *ht, char *key){
    if(ht==NULL){
        return NULL;}
    
    else{
        long i=JenkinsHash(key, ht->slot_num);//call hashfunction to get the index
        return set_find(ht->table[i],key);}//go to the according hashtable slot and seach through the set data structure
}

/**************** global function ****************/
/*insert given key and data in the hashtable, return true if sucessfully inserted, otherwise return false */

bool hashtable_insert(hashtable_t *ht, char *key, void *data){
    if(ht==NULL){
        return false;
    }
    
    else {
        long j=JenkinsHash(key, ht->slot_num);//call hashfunction to get the index
        return set_insert(ht->table[j], key, data); //go to the corresponding hashtable slot and insert in the set
    }
    
}

void hashtable_delete(hashtable_t *ht){
    if(ht==NULL){
        return ;
    }
    else{
        for (int slot=0;slot<ht->slot_num; slot++){
            set_delete(ht->table[slot]);
        }
        free(ht->table);
        free(ht);
    }
	
}

/*adapted according to solution code for lab3*/
void *hashtable_print(FILE *fp, hashtable_t *ht){
	if (ht==NULL){
		fputs("null",fp);
		return 0;
			}
	
	else{
		for (int slot=0; slot<ht->slot_num;slot++){
			printf("%4d: ", slot);
			set_print(fp,ht->table[slot]);
			printf("\n");
			}
		return 0;
		}
 }



void hashtable_iterate(hashtable_t *ht, void(*itemfunc)(void *arg, const char *key, void *data), void *arg){
	
	//checking set, itemfunc
	if(ht==NULL|| itemfunc==NULL){
		return;
	}
	
	//loop through the array
	
	for (int i=0; i<ht->slot_num; i++)
		set_iterate(ht->table[i],itemfunc,arg);
	
}

