//
//  hashtabletest.c
//  lab3
//
//

#include <stdio.h>
#include <stdlib.h>
#include "../set/set.h"
#include "jhash.h"
#include "hashtable.h"

void delete(void *data);


int main(){
    
    /*create a new hashtable with 5 slots*/
    hashtable_t *hashtable=hashtable_new(5,delete);
    
    int p=5;
    /*insert "hello, 5" to the hashtable*/
    if(hashtable_insert(hashtable,"hello",&p)){
        printf("'hello 5'insert was sucessful.\n");
    }
    else{
        printf("'hello 5'insert was not sucessful.\n");

    }
    
    /*insert "hello, 5" to the hashtable again*/
    if(hashtable_insert(hashtable,"hello",&p)){
        printf("'hello 5'insert was sucessful.\n");
    }
    else{
        printf("'hello 5'insert was not sucessful.\n");
        
    }
    
    p=3;
    /*insert "world, 3" to the hashtable*/
    if(hashtable_insert(hashtable,"world",&p)){
        printf("'world 3'insert was sucessful.\n");
    }
    else{
        printf("'world 3'insert was not sucessful.\n");
        
    }
    
    /*find the data of "hello" key in the hashtable*/
    if(hashtable_find(hashtable,"hello")!=NULL){
        int *i=hashtable_find(hashtable,"hello");
        printf("the data of Hello in hashtable is %d.\n",*i);
    }
    
    else{
        printf("'hello'key was not found in the hashtable.");
    }
    
     /*find the data of "goodbye" key in the hashtable*/
    if(hashtable_find(hashtable,"goodbye")!=NULL){
        int *i=hashtable_find(hashtable,"goodbye");
        printf("the data of goodbye in hashtable is %d.\n",*i);
    }
    
    else{
        printf("'goodbye'key was not found in the hashtable.\n");
    }
    
    hashtable_delete(hashtable);
    
    return 0;
    
    
    
}

void delete(void *data){
    if(data){
        free (data);
    }
}
