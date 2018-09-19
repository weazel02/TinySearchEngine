/* querier.c
 *
 *
 * Created by: Wesley Thompson
 * Date: May 13th, 2017
 *
 *
 *
 *
 *
 */
/*system include*/
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

/*local include*/
#include "../common/file.h"
#include "../common/webpage.h"
#include "../common/web.h"
#include "../common/index.h"
#include "../common/word.h"
#include "../libcs50/lib/hashtable/hashtable.h"
#include "../libcs50/lib/counters/counters.h"
#define min(a,b) (((a) < (b)) ? (a) : (b))

/*prototypes*/
static void conditionalFree(void *item);
static bool isValidQuery(char **words, int num);
static int checkArguments(int argc, char *argv[]);
static void queryStart(index_t*index, char *page_directory);
static void deleteElement(void*element);
static void printElement(FILE *fp, char *key, void *element);
static int getWords(char *line, char **words);
static void queryRun(index_t *index, char *page_directory, char **words);

/******************* main function **********************/
int main(int argc, char *argv[])
{	
	 //Check input parameters, load parameters
		
	if(checkArguments(argc,argv)!=0)
	{
		return(-1);
	}
	
	char *page_directory=argv[1];
	char *index_filename=argv[2];
	
	//Load the index
	index_t *index=index_new(800,deleteElement,printElement);
	if(index==NULL)
	{
		printf("Creation of index data structure failed.\n");
		return -1;
	}
	
	index_load(index,index_filename);
	

	//Call query to begin querying for entered words 	
	queryStart(index,page_directory);
	
	//Clean up
	index_delete(index);


	return 0;
}
/*************** local function ****************/
//Free the item in memory is it exists 
static void conditionalFree(void *item){
	if(item){
		free(item);
	}
}

/*************** local function ****************/
//Check whether to make sure arguments are valid

static int checkArguments(int argc, char *argv[]){
	
	if(argc!=3)
	{
		printf("Please enter the correct number of arguments (2).\n");
		return(-1);
	}
	
	
	/*
	 check whether page_directory is readable and produced by crawler
	 */
	char *page_directory=NULL;
	page_directory=argv[1];
	const char crawler[]=".crawler";
	char *is_crawler_directory=malloc(strlen(page_directory)+strlen(crawler)+2);
	sprintf(is_crawler_directory,"%s/%s",page_directory,crawler);
	
	
	if(access(is_crawler_directory,R_OK))
	{
		printf("The entered directory needs to be one produced by the crawler. \n");
		conditionalFree(is_crawler_directory);
		return (-1);
	}
	
	conditionalFree(is_crawler_directory);
	
	/*check whether indexFilename is writable*/
	if(access(argv[2],W_OK))
	{
		printf("The entered index directory cannot be written to.\n");
		return (-1);
	}
	
	
	
	return 0;
}

/*************** local function ****************/
//Funcation which starts the query process.
static void queryStart(index_t *index, char *page_directory)
{
	char *line=NULL;
	
	
	printf("Enter words to query on:\n");
	while((line=readline(stdin))!=NULL)
	{
		int len=0;
		len=strlen(line);
		char **words=calloc((len/2+1),sizeof(char*));
		//Check for empty query
		if(len==0)
		{
			printf("Empty query. Must enter valid query input.\n");
			free(line);
			line=NULL;
			continue;
		}else{
			if(words == NULL){
				printf("Error allocating for query words.\n");
				free(line);
				line=NULL;
				return;
			}
		}


		//Check for spaces only entry
		static int num=0;
		if((num=getWords(line,words))==0)
		{
			printf("Querier is empty. Please enter words separated by spaces.You can make use of the and/or operators between words for more specific searches.\n");
			conditionalFree(line);
			for(int i=0; i<num; i++)
				conditionalFree(words[i]);
			conditionalFree(words);
			line=NULL;


			continue;
		}

		//If the query text is valid, run the query
		if(isValidQuery(words,num))
			queryRun(index,page_directory,words);


		//Free everything we used
		conditionalFree(line);
		for(int i=0; i<num; i++)
			conditionalFree(words[i]);
		conditionalFree(words);

		line=NULL;

		printf("Enter words to query on:\n");

	}
	
}


	
/*************** local function ****************/
//Function that gets the words of the query
static int getWords(char *data, char **words)
{
	int i=0;
	char *token=NULL;
	char space[2]= " "; //using white space (space or tab) as the delimiter
	
	for(token=strtok(data,space);token!=NULL;token=strtok(NULL,space))
	{
		char *new_word = strdup(token);
		words[i]=new_word;
		i++; //use i to count the number of words fetched
	}

	
	return i;
	
}

/*************** local function ****************/
//Function that makes sure query input is valid. Check to make sure and/or appear at the correct times
static bool isValidQuery(char **words,int num)
{
	
	char *andValue="and";
	char *orValue="or";


	
	//Check to make sure the operators are not the first word entered	
	if(strcmp(words[0],orValue)==0)
	{
		printf("'or'cannot be the first entered word.\n");
		return false;
	}
	if(strcmp(words[0],andValue)==0)
	{
		printf("'and' cannot be the first entered word.\n");
		return false;
	}
	int length = 0;
	for(int i=0; i < num; i++)
	{
		
	
		for(int j=0;j<strlen(words[i]);j++){
			//Make sure all characters are letter
			if(isalpha(words[i][j])==0){
				printf("The character '%c'is not allowed in the query.\n",words[i][j]);
				return false;}
			
			if(isupper(words[i][j]))
				//Convert to lower case	
				words[i][j] = tolower(words[i][j]);
			
			}
		
		//Check to make sure the and/or operators are not next to each other
		if(i>0)
		{
			if(strcmp(words[i-1],andValue)==0 || strcmp(words[i-1],orValue)==0 )
			{
				if(strcmp(words[i],andValue)==0 || strcmp(words[i],orValue)==0 )
				{
					printf("'and' and 'or' cannot be next to one another.\n");
					return false;
				}
			}
		}
		
	length = length + 1;
	}
	

	/* 'and' 'or' operator cannot be last*/
	if(strcmp(words[length-1],andValue)==0)
	{
		printf("'and' cannot be the last word entered.\n");
		return false;
	}
	
	if(strcmp(words[length-1],orValue)==0)
	{
		printf("'or'cannot be last word entered.\n");
		return false;
	}
	
	
	return true;
	
}
/*************** local function ****************/
//Function that runs the query on the given index/pagedirectory 

static void queryRun(index_t *index, char *page_directory, char **words)
{
	
	//Print the resultant query	
	printf("Result Query:\n");
	for(int i=0; words[i]!=NULL; i++)
	{
		printf("%s ",words[i]);
	}
	printf("\n");
	
	//Process the query data
	counters_t *andMatch=NULL; //tmpMatch to keep track of and operation
	counters_t *orMatch=NULL; //finalMatch to keep track of or operation
	
	//Loop over all the words	
	for(int i=0; words[i]!='\0'; i++)
	{
		
		char *andValue="and";
		char *orValue="or";
		
		//hit"and", then skip
		if(strcmp(andValue,words[i])==0)
			continue;
		
		//Set andMatch after hitting or/first word
		if(i==0 || (i>1 && strcmp(orValue,words[i-1])==0))
		{
			if(index_find(index,words[i])!=NULL)
			{	andMatch=counters_new();
				counters_union(index_find(index,words[i]),andMatch);
			}
		}
		
		
		// If hit "or", then update orMatch and set andMatch to NULL
		if(strcmp(orValue,words[i])==0)
		{
			//If or has been hit before we must do union and update or orMatch
			if(orMatch!=NULL)
			{
				//if andMatch is empty, union result would still be orMatch,therefore there is nothing to do
				//if andMatch is not empty, do union with orMatch
				if(andMatch!=NULL)
					counters_union(andMatch,orMatch);
			}
			
			//If its the first time we have seen or, update orMatch
			else{
				//If andMatch is not empty then we need make a new set and copy it over
				if(andMatch!=NULL){
					orMatch=counters_new();
				   counters_union(andMatch,orMatch);}
				}
			//After our orMatch is updated we need to clean up andMatch	
			if(andMatch){
				counters_delete(andMatch);
				andMatch=NULL;}
			continue;
		}
		
		//Intersection
		//If index_find returns null the intersection must also be null	
		if(index_find(index,words[i])==NULL)
		{
			//If andMatch is not Null, delete it 
			if(andMatch!=NULL){
				counters_delete(andMatch);
				andMatch=NULL;}
		}
		
		else{
			//If andMatch is not null we can do the intersection
			if(andMatch!=NULL)
				counters_intersect(index_find(index,words[i]),andMatch);
			}
		}
	
		//if orMatch is not empty, combine with andMatch
		if(orMatch!=NULL)
		{
			//If andMatch is Null we need to make a new set
			if(andMatch==NULL)
				andMatch=counters_new();
			counters_union(orMatch,andMatch);
		}
	//The final query result is stored in andMatch. Sort it.
	counters_sort(andMatch,page_directory);
	//Cleanup	
	if(andMatch){
		counters_delete(andMatch);
	}
	
	if(orMatch){
		counters_delete(orMatch);
	}
	
	return;
	}
	



/*************** local function ****************/
static void deleteElement(void*element){
	if(element)
		counters_delete(element);
}

static void printElement(FILE *fp, char *key, void *element){
	
	if(element)
		printf("print\n");
}





