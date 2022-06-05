#include <curl/curl.h>
#include <string.h>


int main(){

	CURL *curl = curl_easy_init();
	if(curl) {
	  char *URL_BASE = curl_easy_escape(curl, URL_BASE,strlen(URL_BASE));
	  if(output) {
	    printf("Encoded: %s\n", output);
	    curl_free(output);
	  }
	  curl_easy_cleanup(curl);
	}
  
  
}
