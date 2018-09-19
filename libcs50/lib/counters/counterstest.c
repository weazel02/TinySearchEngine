//
//  counterstest.c
//  lab3
//
//  

#include <stdio.h>
#include <stdlib.h>
#include "counters.h"



int main(){
    
    /*create a new counter data structure*/
    counters_t *countersA=counters_new();
	counters_t *countersB=counters_new();
	
	counters_add(countersA,1);
	counters_add(countersA,1);
	counters_add(countersA,2);
	counters_add(countersA,2);
	
	counters_add(countersB,2);
	counters_add(countersB,2);
	counters_add(countersB,3);
	
	//counters_t *result=counters_new();
	
	
	counters_t *c=counters_intersect(countersA,countersB);
	
	int i=0;
	i=counters_get(c,1);
	
	printf("i=counters_get(countersB,1) is %d ;\n",i);
	i=counters_get(c,2);
	printf("i=counters_get(countersB,2) is %d ;\n",i);
	i=counters_get(c,3);
	printf("i=counters_get(countersB,3) is %d ;\n",i);
	
	counters_delete(c);
	
	/*
	
	//add to countersB, counters won't change
	
	counters_union(countersA,countersB);
	printf("after union\n");
	
	i=counters_get(countersB,1);
	printf("i=counters_get(countersB,1) is %d ;\n",i);
	i=counters_get(countersB,2);
	printf("i=counters_get(countersB,2) is %d ;\n",i);
	i=counters_get(countersB,3);
	printf("i=counters_get(countersB,3) is %d ;\n",i);
	*/
	counters_delete(countersA);
	//counters_delete(countersB);
	
	
	//counters_t *new_counter;
	//printf("hello\n");
    /*add key 1 to new counter*/
    //counters_add(new_counter,1);
	//printf("add another key")
    /*add key 2 to new counter*/
    //counters_add(new_counter,2);
    /*add key 1 to new counter again*/
    //counters_add(new_counter,1);
    /*add key 1 to new counter again*/
    //counters_add(new_counter,1);
	
	
    //int i=0;
    /*return the current value of the counter for key 1*/
    
    //i=counters_get(new_counter,1);
    //printf("the counter of key 1 is %d\n", i);
    
    /*return the current value of the counter for key 5*/
    //i=counters_get(new_counter,5);
    //printf("the counter of key 5 is %d\n", i);
    
    /*return the current value of the counter for key 2*/
    //i=counters_get(new_counter,2);
    //printf("the counter of key 2 is %d\n", i);
    
    //counters_delete(new_counter);
	
    
}



/*
void counters_iterate(counters_t *ctrs,
					  void (*itemfunc)(void *arg, const int key, int count),
					  void *arg)



static void
counters_intersect(counters_t *countersA, counters_t *countersB){
	
	counters_iterate(countersB,counters_intersect_helper,countersB_arg);

}

countersB_arg{
	
}



void counters_intersect_helper(void *arg, const int key, int count){
	//counters_intersect_helper(countersB_arg, const int Bkey, int Bcount)
	counters_t *countersA=arg;
	counters_iterate(countersA,key_count,)
	
	if(counters_get(two_counters->countersA,key)!=0 && counters_get(two_counters->countersB,key)!=0){
		int new_count;
		
		if(two_counters->countersA->counter < two_counters->countersB->counter){
			new_count=countersA->counter;
		}
		else{
			new_count=countersB->count;
		}
		return counters_set(two_counters->result,key,new_count);
	}
}



static void
counters_intersect(counters_t *countersA, counters_t *countersB,counters_t *result){
	int count=0;
	for (counter_node_t *node_in_A=countersA->head; node_in_A!=NULL;node_in_A=node_in_A->next){
		for(counters_node_t *node_in_B=countersB->head);node_in_B!=NUL;node_in_B=node_in_B->next){
			if(node_in_A->key==node_in_B->key){
				if(node_in_A->counter > node_in_B ->counter){
					count=node_in_B->counter;
					counters_set(result,node_in_A->key,count)
				}
				else{
					count=node_in_A->counter;
					counters_set(result,node_in_A->key,count);
				}
			}
		}
	}
	
}

 */


