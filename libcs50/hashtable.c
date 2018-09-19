/* hashtable.c - Unordered collection of key value pairse
 *
 * Created By: Wesley Thompson 
 * Date: 4/21/2017
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "memory.h"
#include "jhash.h"
/************ LOCAL TYPES *************/
typedef struct hashnode {
        char *key;
        void *item;
        struct hashnode *next;
} hashnode_t;
/************ GLOBAL TYPES ************/
typedef struct hashtable {
        hashnode_t **table;
	int numBuckets;
} hashtable_t;
static hashnode_t * hashnode_new(const char *key, void *item);

/* Create a new (empty) hashtable; return NULL if error. */
hashtable_t *hashtable_new(const int num_slots){
	if(num_slots <= 0){
		return NULL;

	}else {
		hashtable_t *ht = malloc(sizeof(hashtable_t));
		hashnode_t **table = calloc(num_slots, sizeof(hashnode_t *));
		if(ht != NULL){
			ht->numBuckets = num_slots;
			ht->table = table;
			return ht;
		}
		return NULL;
	}
}

/* Insert item, identified by key (string), into the given hashtable.
 * The key string is copied for use by the hashtable.
 * Return false if key exists in ht, any parameter is NULL, or error;
 * return true iff new item was inserted.
 */
bool hashtable_insert(hashtable_t *ht, const char *key, void *item){
	if(ht != NULL && key != NULL && item != NULL){
		long hash_key = JenkinsHash(key,ht->numBuckets);
		if(ht->table[hash_key] == NULL){

			hashnode_t *newNode = hashnode_new(key, item);
			if(newNode != NULL){
				ht->table[hash_key] = newNode;
				return true;
			}
		}else{
			hashnode_t *node = ht->table[hash_key];
			for (; node->next != NULL; node = node->next) {
				if(strcmp(key, node->key) == 0){
					return false;
				}
			}
			 hashnode_t *newNode = hashnode_new(key, item);
			 if(newNode != NULL){
                                node->next = newNode;
                                return true;
                        }
		}
	}
	return false;
}
/********* setnode_new() ***************/

static hashnode_t * hashnode_new(const char *key, void *item){
        hashnode_t *node = count_malloc(sizeof(hashnode_t));

        if(node == NULL) {
                return NULL;
        }else {
                node->item = item;
                node->key = key;
                node->next = NULL;
                return node;
        }
}

void hashtable_print(hashtable_t *ht, FILE *fp, void (*itemprint)(FILE *fp, const char *key, void *item)){
	if(fp != NULL && ht != NULL){
		fputc('{', fp);
		for( int i = 0; i < ht->numBuckets; i++){
			if (itemprint != NULL) {
				hashnode_t *node = ht->table[i];
				for (; node != NULL; node = node->next){	
					(*itemprint)(fp, node->key, node->item);
					fputc(',', fp);
				}
				fputc('\n',fp);
			}
		}
		fputc('}', fp);
	}		
	else{
		fputs("(null)", fp);
	}
}

/* Return the item associated with the given key;
 * return NULL if hashtable is NULL, key is NULL, key is not found.
 */
void *hashtable_find(hashtable_t *ht, const char *key){
	if(ht != NULL && key != NULL){
		long hash_key = JenkinsHash(key,ht->numBuckets);
		if(ht->table[hash_key] == NULL){
			return false;
		}else{
			hashnode_t *node = ht->table[hash_key];
			for (; node!= NULL; node = node->next) {
				if(strcmp(key, node->key) == 0){
					return node->item;
				}
			}

		}
	}
	return false;
	
}
/* Iterate over all items in the table; in undefined order.
 * Call the given function on each item, with (arg, key, item).
 * If ht==NULL or itemfunc==NULL, do nothing.
 */
void hashtable_iterate(hashtable_t *ht, void *arg,
		void (*itemfunc)(void *arg, const char *key, void *item) ){
	for( int i = 0; i < ht->numBuckets; i++){
		if (itemfunc != NULL) {
			hashnode_t *node = ht->table[i];
			for (; node != NULL; node = node->next){
				(*itemfunc)(arg, node->key, node->item);
			}
		}
	}
}
/* Delete the whole hashtable; ignore NULL ht.
 * Provide a function that will delete each item (may be NULL).
 */
void hashtable_delete(hashtable_t *ht, void (*itemdelete)(void *item)){
	if(ht != NULL){
		for( int i = 0; i < ht->numBuckets; i++){
			if (itemdelete != NULL) {
				hashnode_t *node = ht->table[i];
				while (node != NULL){
					hashnode_t *next = node->next;
					(*itemdelete)(node->item);
					count_free(node);
					node = next;
				}
			}
		}
	count_free(ht);
	}
	memset((void *)ht, 0, sizeof(hashtable_t));
}
