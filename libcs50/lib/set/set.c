//  set.c
//  lab3
//


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

/**************** local types ****************/
typedef struct set_node{
    char *key;
    void *data;
    struct set_node *next;
    
}setnode_t;

/**************** global types ****************/
typedef struct set{
    struct set_node *head;
	void(*itemprint)(FILE*fp, char *key, void *data);
    void(*itemdelete)(void*data);
}set_t;


/**************** global functions ****************/
/* that is, visible outside this file */
/*create a new empty set data structure*/
set_t *set_new(void(*itemdelete)(void *data),void(*itemprint)(FILE *fp, char *key, void *data)){
    
    set_t *set=malloc(sizeof(set_t));
    if(set==NULL){
        printf("error in allocating memory for a new set");
        return NULL;}
    else{ //initialize the set data structure to empty
        set->head=NULL;
        set->itemdelete=itemdelete;
        return set;
}
}

/**************** local functions ****************/
/* not visible outside this file */
setnode_t *setnode_new(char *key, void *data){
    setnode_t *new_set_node=malloc(sizeof(setnode_t));
    if(new_set_node==NULL){
        printf("error in allocating memory for a new set node");
        return NULL;
    }
    new_set_node->key=malloc(strlen(key)+1);
    if(new_set_node->key==NULL){
        free(new_set_node);
        return NULL;
    }
    strcpy(new_set_node->key,key);
    new_set_node->data=data;
    new_set_node->next=NULL;
    return new_set_node;
    
    }

/**************** global functions ****************/
/*return data for the given key, or NULL if key is not found.*/
void *set_find(set_t *set, char *key){
    if(set==NULL){
        printf("the given set is empty");
        return NULL;
    }
    //loop over the linked list
    setnode_t *set_node=set->head;
    while(set_node!=NULL){
        if(strcmp(set_node->key, key)==0){
            return set_node->data; //if find it, return data for the key
        }
        set_node=set_node->next;
    }
    
    return NULL; // if key is not found, return NULL
    
    }


/**************** global functions ****************/
/* return false if key already exists
return true if new item was inserted
return NULL if set is empty
return false if other errors incurred*/
bool set_insert(set_t *set, char *key, void *data){
    if(set==NULL){
        perror("error");
        return false;
    }
    /*search whether the key exist*/
    setnode_t *set_node=set->head;
    while(set_node!=NULL){
        if(strcmp(set_node->key, key)==0){ // if key already exists, return false
            return false;
        }
    set_node=set_node->next;
    }
    
    //insert key and return true
    setnode_t *new_set_node=setnode_new(key,data);
    new_set_node->next=set->head;
    set->head=new_set_node;
    return true;
    
}



void set_delete(set_t *set){
    if(set==NULL){
        return;
    }
    else{
        setnode_t *node=set->head;
        while(node!=NULL){
            if(set->itemdelete!=NULL){
                (*set->itemdelete)(node->data);//delete node's data
                setnode_t *next=node->next;
                free(node->key);
                free(node);
                node =next;
            }
			
        }
		
	free (set);
    }
	
}

/*adapted according to lab3 solution code*/
void set_print(FILE *fp, set_t *set){

	if(set==NULL){
		fputs("(null)",fp);
		return;
	} else{
		fputc('[',fp);
		for (setnode_t *node=set->head; node!=NULL; node=node->next){
			//print the current node
			if(set->itemprint !=NULL)
				(*set->itemprint)(fp,node->key,node->data);
			fputs(", ",fp);
		}
		
		fputc(']',fp);
	}
	
	return;
	}



/*set iterate*/
void set_iterate(set_t *set, void(*itemfunc)(void *arg, const char *key, void *data), void *arg){
	
	//node is a generic pointer
	//item function, need to add key
	if (set ==NULL || itemfunc == NULL)
		return;
	
	else{
		for (setnode_t *node=set->head; node!=NULL; node=node->next){
			(*itemfunc)(arg, node->key, node->data);}
		
		
		return;}
	
}



