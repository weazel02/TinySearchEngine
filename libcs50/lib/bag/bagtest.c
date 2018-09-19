//
//  bagtest.c
//  lab3
//
//

#include <stdio.h>
#include <stdlib.h>
#include "bag.h"
#include <string.h>


void delete(void* data);

int main()
{
    bag_t *newbag;
    
    
    //call bag_new() to create a new bag
    newbag=bag_new(delete);
    if (newbag == NULL){
        printf("bag_new failed\n");
        return 0;
    }
    
    char *a="first";
    
    //char *a=malloc(strlen(d + 1));
    //char *b = a;
    
    //strcpy(a,d);
    //a="first";
    /*add 'first' item in the bag*/
    bag_insert(newbag,a);
    
    a="second";
    //strcpy(a,d);
    /*add 'second' item in the bag*/
    bag_insert(newbag,a);
    
    a="third";
    //strcpy(a,d);
    /*add 'third' item in the bag*/
    bag_insert(newbag,a);
    
    printf("we add three itmes: 'first', 'second' and 'third'.\n");
    
    /*extract a item in the bag
     print the content of the item
     or print the bag is empty
     */
    
    char *extract=bag_extract(newbag);
    if(extract!=NULL){
        
        printf("the removed item is %s.\n",extract);}
    else{
        printf("the bag is empty.\n");
    }
    
    extract=bag_extract(newbag);
    if(extract!=NULL){
        
        printf("the removed item is %s.\n",extract);}
    else{
        printf("the bag is empty.\n");
    }
    
    extract=bag_extract(newbag);
    if(extract!=NULL){
        
        printf("the removed item is %s.\n",extract);}
    else{
        printf("the bag is empty.\n");
    }
    
    extract=bag_extract(newbag);
    if(extract!=NULL){
        
        printf("the removed item is %s.\n",extract);}
    else{
        printf("the bag is empty.\n");
    }
    
    bag_delete(newbag);
    
    //free(b);
    
    return 0;
}

void delete(void *data){
    if(data){
        free(data);
    }
}

