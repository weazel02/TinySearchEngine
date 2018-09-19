//
//  settest.c
//  lab3
//
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "set.h"

void delete(void *data);

int main(){
    /*create a new set*/
    set_t *new_set=set_new(delete);
    int i=2;
    
    //int *p=malloc(sizeof(p));
    //int *p;
   
  
    /*insert "hello,2"node*/
    char *c="hello";
    if(set_insert(new_set,c,&i)){
        printf("insert 'hello key' was successful\n");
    }
       else{
           printf("insert 'hello key' was not successful\n");
           
       }
    
    /*insert "hello,2"node again*/
    //set_insert(new_set, "hello",&p);
     if(set_insert(new_set, c,&i)){
        printf("insert 'hello key' was successful\n");
    }
        else{
            printf("insert 'hello key' was not successful\n");
              
          }
       
    i=5;
    /*insert "okay,5"node*/;
    c="okey";
    set_insert(new_set, c,&i);
    
    
    /*find "hellogoodbye" key, which doesn't exist*/
    c="hellogoodbye";
    
    if(set_find(new_set,c)!=NULL){
        int *q=set_find(new_set,c);
        printf("the data of this key is %d\n",*q);
    }
    else {
        printf("the data of 'Hello Goodbye' is NULL\n");}
    
    /*find the data of "hello" key*/
    c="hello";
    if(set_find(new_set,c)!=NULL){
    int *q=set_find(new_set,"hello");
        printf("the data of 'hello' is %d\n",*q);
    }
    else {
        printf("the data of t'hello' is NULL\n");}
    
    
    set_delete(new_set);
    
    return 0;
   

}


void delete(void *data){
    if(data){
        //free(data);
    }
    
    
    
}
