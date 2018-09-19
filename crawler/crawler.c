/* ========================================================================== */
/* File: crawler.c - Tiny Search Engine web crawler
 *
 * Author: Wesley Thompson
 * Date: May 1, 2017
 *
 * Input: [seedURL] [webPageDirectory] [maxwebpage_tDepth]
 *
 */

#include <stdio.h>                           // print 
#include <curl/curl.h>                       // curl functionality
#include <string.h>                                                      // string functions
#include <ctype.h>                                                       // for argument checking
#include <sys/stat.h>                                            // for argument checking
#include <unistd.h>                                                      // for sleep

// ---------------- Local includes  e.g., "file.h"
#include "../libcs50/webpage_fetch.h"
#include "../libcs50/webpage.h"                             // curl and html functionality
#include "../libcs50/set.h"                            // webpage list functionality
#include "../libcs50/hashtable.h"                       // hashtable functionality
#include "../libcs50/webpage_internal.h"                        // utility stuffs



int MAX_NUMBER_OF_PAGES;
int MAX_DEPTH = 3;
set_t *url_set;
hashtable_t *url_table;
typedef struct pgnode {
        webpage_t *page;

} pgnode_t;
/* ========================================================================== */

void getLinks(webpage_t *page) {

 // variables to use within the loop
        int pos = 0;
        char **current_url = malloc(sizeof(char**));

        printf("Crawling - %s\n", page->url);
        fflush(stdout);
        int numPages = 0;
        // loop through each URL using the parse
        while (((pos = webpage_getNextURL(page, pos,current_url)) > 0)) {
                if (NormalizeURL(*current_url) == 0) {
                        printf(" Invalid url: %s\n", *current_url);
                        continue;
                }

                // valid URL
                printf(" Current Link:  %s\n", *current_url);

                char *url_copy = calloc(strlen(*current_url), sizeof(char) + 1);
                strncpy(url_copy, *current_url, strlen(*current_url));
//                free(current_url);


                if (hashtable_insert(url_table,url_copy,url_copy)) { // if not already added    
                        webpage_t *list_page = malloc(sizeof(webpage_t));
                        list_page->url = url_copy;
                        list_page->depth = page->depth + 1;
                        pgnode_t *node = malloc(sizeof(pgnode_t));
                        node->page = list_page;
                        set_insert(url_set,list_page->url,node);
                }

        }
       free(page);
}

int main(int argc, char** argv)
{

// make sure command line arguments are correct}

        if (NormalizeURL(argv[1]) == 0) {
                printf("Invalid URL given.\n");
                return 1;
        }

        if (argc != 4) {
                printf("This program requires 3 arguments: a URL, a webPageDirectory, and a maxwebpage_tDepth\n");
                return 1;
        }



        struct stat s = {0};

        if (stat(argv[2], &s) == -1) {
                mkdir(argv[2], S_IRWXU);
        }

        for (int i = 0; i < strlen(argv[3]); i++) {
                if (!isdigit(argv[3][i])) {
                        printf("Depth must be entered as an integer.\n");
                        return 1;
                }
        }

        if (atoi(argv[3]) > MAX_DEPTH) {
                printf("The depth entered must be less than %i.\n", MAX_DEPTH);
                return 1;
        }


    curl_global_init(CURL_GLOBAL_ALL);

 // inititalizie seed page
        webpage_t *page = malloc(sizeof(webpage_t));
        page->url = argv[1];
        page->depth = 1;
        page->html = "";
        url_set = set_new();
        url_table = hashtable_new(MAX_DEPTH*10);



    // get seed webpage
    if (!webpage_fetch(page)) {
                printf("Invalid seed URL given.\n");
                return 1;
        }


      //write first file
        char *file_name = calloc(strlen(argv[2]) + sizeof(int) + 1, sizeof(char));
        int file_number = 1;


        // get desired file path based on current number
        sprintf(file_name, "%s%i", argv[2], file_number);

        // open file and write lines
        FILE *file = fopen(file_name, "w+");
        free(file_name);
        fprintf(file, "%s\n", page->url);
        fprintf(file, "%i\n", page->depth);
        fprintf(file, "%s\n", page->html);
        fclose(file);
        file_number++;

        hashtable_insert(url_table, page->url,page);

       //get urls from seed page
        getLinks(page);

        //page *current_node;   
  // while there are urls to crawl
        while (url_set->head != NULL) {
                // get next url from list
                webpage_t *current_page = malloc(sizeof(webpage_t));
                 current_page = ((pgnode_t *) set_getfirst(url_set)->item)->page;

                // get webpage for url
                if (webpage_fetch(current_page) == 0) {
                        printf("Invalid url: %s\n", current_page->url);
                        continue;
                }
                // check for empty URL
                if (strstr(current_page->html, "<TITLE>404 Invalid URL</TITLE>")) {
                        continue;
                }


                // write next file.... File Module Code
                char *file_path = malloc(strlen(argv[2]) + sizeof(int) + 1);
                sprintf(file_path, "%s%i", argv[2], file_number);
                FILE *page_file = fopen(file_path, "w");
                free(file_path);
                fprintf(page_file, "%s\n", current_page->url);
                fprintf(page_file, "%i\n", current_page->depth);
                fprintf(page_file, "%s\n", current_page->html);
                fclose(page_file);
                file_number++;

                // extract urls from webpage
                if (current_page->depth <= atoi(argv[3]) + 1) { // depth check
                        getLinks(current_page);
                }
                else {
                        break;
                }

                //sleep(INTERVAL_PER_FETCH);
        }

    // cleanup curl
    curl_global_cleanup();

    return 0;
}
                
