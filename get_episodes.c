#include "imdb.h"
 
size_t write_data( void *ptr, size_t size, size_t nmeb, void *stream)
{
	 return fwrite(ptr,size,nmeb,(FILE*)stream);
}
 
int get_episodes(char* DESTINATION_FILE, char* WEBPAGE_URL)
{
	printf("Downloading - %s\n", DESTINATION_FILE);
	 FILE * file = fopen(DESTINATION_FILE,"w+");
	  if(!file){
		  printf("Error while open file %s\n", DESTINATION_FILE);
		   perror("");
		    exit(1);
		     }
    CURL *handle = curl_easy_init();
    curl_easy_setopt(handle,CURLOPT_URL,WEBPAGE_URL); /*Using the http protocol*/
    curl_easy_setopt(handle,CURLOPT_WRITEFUNCTION, write_data);
    curl_easy_setopt(handle,CURLOPT_WRITEDATA, file);
    curl_easy_perform(handle);
    curl_easy_cleanup(handle);
    printf("Info downloaded\n");
    return 0;
}
