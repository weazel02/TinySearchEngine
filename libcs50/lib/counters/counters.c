//
//  counters.c
//  updated for lab6
//
// Wesley Thompson
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "counters.h"
#include "../../../common/file.h"
#define min(a,b) (((a) < (b)) ? (a) : (b))

/**************** local types ****************/
typedef struct counter_node{
    int key;
    int counter;
    struct counter_node *next;
    
}counter_node_t;

/**************** global types ****************/
typedef struct counters{
    struct counter_node *head;
    
}counters_t;
static void add_to_array(void *arg, const int key, int count);
static int cmpfunc(const void *a, const void *b);
/**************** global functions ****************/
/**************** counters_new() ****************/
/*create a new counters data structure, initialize it to empty*/
counters_t *counters_new(void){
    counters_t *counters=malloc(sizeof(counters_t));
    if(counters==NULL){
        return NULL;}
    else{
        counters->head=NULL;
        return counters;
    }
}

/**************** local functions ****************/
/**************** counternode_new() ****************/
/*create a new counternode and set its counter to 1*/
counter_node_t *
counternode_new(int key){
    counter_node_t *counter=malloc(sizeof(counter_node_t));
    if (counter==NULL)
        return NULL;
    else{
        counter->key= key;
        counter->counter=1;
		counter->next=NULL;
        return counter;
    }
    
}


/**************** global functions ****************/
/**************** counters_add() ****************/
/**************** modified according to lab3 solution code ****************/

void counters_add(counters_t *ctrs, int key){
	
	if(ctrs==NULL){
		printf("ctrs is NULL");
		return;
	}
	
	//if the head is NULL, add the new counters node to head
	if (ctrs->head ==NULL){
		ctrs->head =counternode_new(key);
		return;
	}
	
	
    //if the key exists, increment its counters
	counter_node_t *counter=ctrs->head;
	counter_node_t *tail=ctrs->head;
    while (counter!=NULL){
        if (counter->key==key){
            counter->counter=counter->counter+1;
            return;
        }
		tail=counter;
        counter = counter->next;
		
	}
	
	/*add the node to the end*/
	counter_node_t *new_counter=counternode_new(key);
	tail->next=new_counter;}
	
	/* previous solution add the node to head */
	/*
    //key doesn't exist; add key and set it counters to 1
    
    counter_node_t *new_counter=counternode_new(key);
    new_counter->next=ctrs->head;
    ctrs->head=new_counter;
	 }
	*/
	


/**************** global functions ****************/
/**************** counters_get() ****************/
int counters_get(counters_t *ctrs, int key){
    if(ctrs==NULL){
		return 0;
    }
	
	
    counter_node_t *counter=ctrs->head;
    while (counter!=NULL){
        if (counter->key==key){
            return counter->counter;}
        counter=counter->next;
    }
    
    return 0;
}

/**************** global functions ****************/
/**************** counters_delete() ****************/
void counters_delete(counters_t *ctrs){
    if(ctrs==NULL){
        return;}
    else if(ctrs->head==NULL){
        free(ctrs);//if ctrs is an empty data structure, free ctrs
        return;
    }
    
    else{
        //if counters is not empty,free every counternode and then free the whole data structure
        counter_node_t *counter = ctrs->head;
        while(counter!=NULL){
            counter_node_t *tmpt = counter;
            counter = counter->next;
            free(tmpt);
        }
        free(ctrs);
        return;
    }
    
}

/**************** global functions ****************/
/* counters_set*/
/* Set value of the counter indicated by key.
 * If the key does not yet exist, create a counter for it
 * and initialize its counter value to 'count'.
 * NULL counters is ignored.
 */

void counters_set(counters_t *ctrs, int key, int count){
	
	if(ctrs==NULL){
		return;
	}
	
	/*if the key existed, set the counter to count*/
	if(counters_get(ctrs,key)!=0){
		for(counter_node_t *node=ctrs->head; node!=NULL; node=node->next){
			if(node->key==key){
				node->counter=count;
				return;}
			}
		
	}
	
	/*if the key existed, set the counter to count*/
	if(counters_get(ctrs,key)==0){
		counters_add(ctrs,key);
		for(counter_node_t *node=ctrs->head; node!=NULL; node=node->next){
			if(node->key==key){
				node->counter=count;
				return;}
		}
		
		}
	
	
		//counter_node_t *counter_node=counternode_new(key);
		//counter_node->counter=count;
		
		//counter_node->next=ctrs->head;
		//ctrs->head=counter_node;
		
	
}

/**************** global functions ****************/
/* counters_iterate*/
/* Iterate over all counters in the set (in undefined order):
 * call itemfunc for each item, with (arg, key, count).
 */

int counters_iterate(counters_t *ctrs,
					  void (*itemfunc)(void *arg, const int key, int count),
					  void *arg){
	
	if (ctrs ==NULL || itemfunc == NULL)
		return 2;
	if(ctrs->head==NULL)
		return 1;
	
	else{
		for (counter_node_t *node=ctrs->head; node!=NULL; node=node->next){
			(*itemfunc)(arg, node->key, node->counter);}
		
		return 0;}
	
}




/*
void counters_add(counters_t *ctrs,int key)
{
	if (ctrs==NULL)
		return;
	if (ctrs->head ==NULL)
		ctrs->head =counternode_new(key);
	
	else{
		counter_node_t *prev=ctrs->head;
		for(counter_node_t *node = prev; node !=NULL; node=prev->next){
			if (key==node->key){
				node->counter++;
				goto done;
			}
			prev=node;
		}
 
		prev->next=counternode_new(key);
		
		
	}

done:;
	
	
}
*/
counters_t *counters_intersect(counters_t *countersA, counters_t *countersB){
	
	if(countersA ==NULL || countersB ==NULL){
		//result =NULL;
		return NULL;
	}
	
	//if key in B not in A, set the key to 0
	for(counter_node_t *node_in_B=countersB->head; node_in_B!=NULL;node_in_B=node_in_B->next){
		if(counters_get(countersA,node_in_B->key)==0)
		{
			counters_set(countersB,node_in_B->key,0);
		}
	}
	
	
	for (counter_node_t *node_in_A=countersA->head; node_in_A!=NULL;node_in_A=node_in_A->next)
	{
		
		if(counters_get(countersB,node_in_A->key)==0){
			continue;
		}
		
		
		counters_set(countersB,node_in_A->key,min(node_in_A->counter,counters_get(countersB,node_in_A->key)));
					 }
	
	
	return countersB;
					 
}

void counters_union(counters_t *countersA, counters_t *countersB){
	
	if (countersA==NULL)
		return;
	
	for (counter_node_t *node_in_A=countersA->head; node_in_A!=NULL;node_in_A=node_in_A->next)
	{
		
		counters_set(countersB,node_in_A->key,(node_in_A->counter+counters_get(countersB,node_in_A->key)));

		
	}
	
	
	
}
 

/*
void counters_union(counters_t *countersA, counters_t *countersB){
	
	if (countersA==NULL)
		return;
	
	int count=0;
	for (counter_node_t *node_in_A=countersA->head; node_in_A!=NULL;node_in_A=node_in_A->next){
		for(counter_node_t *node_in_B=countersB->head;node_in_B!=NULL;node_in_B=node_in_B->next)
		{
			if(node_in_A->key==node_in_B->key){
				count=node_in_A->counter+node_in_B->counter;
				counters_set(countersB,node_in_B->key,count);}
			
		}
		if(counters_get(countersB, node_in_A->key)==0){
			counters_set(countersB,node_in_A->key,node_in_A->counter);}
		
	}
}*/


/*************** local function ****************/
/*function to count how many nodes are in the counters*/
static void counters_count(void *arg, const int key, int count)
{
	
	int *nitems = arg;
	
	if (nitems != NULL)
		(*nitems)++;

	
}


/******* struct********/
struct element
{
	int docID;
	int score;
};

/********************** local function **********************/
/************* function sort the querier result *************/
void counters_sort(counters_t *ctrs, char*page_directory)
{
	//printf("sort\n");
	int num=0;
	
	
	/*get the number of node in the counters*/
	counters_iterate(ctrs,counters_count,&num);
	
	/*if no nodes in the counters, no results matched*/
	if(num==0)
	{
		printf("no result matched\n");
		return;
	}
	
	
	/*build an array of pointers of structs of (docID, score) pairs*/
	struct element **array_sort=malloc(sizeof(struct element)*(num));
	
	
	if(array_sort==NULL)
	{
		printf("array_sort malloc error.\n");
		return;
	}
	
	
	/*initlaize all the pointers in the structs to NULL*/
	for(int i=0;i<num;i++)
		{array_sort[i]=NULL;}
	
	/*iterate over the counters node and add the pointers of the struct pairs to the array */
	counters_iterate(ctrs,add_to_array,array_sort);

	
	/*get the mathching results*/
	int index=0;
	for(int i=0;i<num;i++)
	{
		if(array_sort[i]->score>0) //node with score greater than 0 is considered as a match
			index++;
	}
	
	
	if(index==0)
		printf("no result matched\n");
	
	else
	{
		printf("Matches %d documents (ranked):\n",index);
		
		/*sort the array according to score*/
		qsort(array_sort,num,sizeof(struct element *),cmpfunc);

	
		/*print out the score, docID and http information*/
		for(int i=0;i<num;i++)
		{
			char*filename=malloc(strlen(page_directory)+10);
			sprintf(filename,"%s/%d",page_directory,array_sort[i]->docID);
			FILE*fp=fopen(filename,"r");
		
			if(fp==NULL)
			{	free(filename);
				fclose(fp);
				continue ;
			}
			else{
				char *line=NULL;
				line=readline(fp);
				if(array_sort[i]->score>0)
					printf("score %3d docID %5d : %s\n",array_sort[i]->score,array_sort[i]->docID,line);
				fclose(fp);
				free(line);
				free(filename);
				continue;
			}
		}
		printf("-------------------------------------------------------------------------\n");
	
	}
	
	/*clean up the array*/
	for(int i=0;i<num;i++){
		if(array_sort[i])
		free(array_sort[i]);} //clean every pointer in the array
	if(array_sort)
	free(array_sort); //clean the whole array data structure
	
	
}

/*************** local function ****************/
/*function to add pointers of struct to array*/
static void add_to_array(void *arg, const int key, int count)
{
	
	struct element **as=arg;
	
	struct element *node=malloc(sizeof(struct element));
	
	/*loop over the array to get the right position to add pointer*/
	int i=0;
	while(as[i]!=NULL){
		i=i+1;
	}
	
	as[i]=node;
	node->docID=key;
	node->score=count;
	
}


/*************** local function ****************/
/*****compare function to pass into qsort*******/
static int cmpfunc(const void *a, const void *b)
{
	/*get pointers to the element in the array to compare*/
	struct element* *ea=(struct element**)a;
	struct element* *eb=(struct element**)b;
	
	/*since each element in the array is also a pointer, 
	 we need to dereference the pointer passed into the
	 function and then compare the score*/
	return ((*eb)->score - (*ea)->score);
}



