#include <stdio.h>
#include <curl/curl.h>
#include <string.h>
#include <stdlib.h>
#include <json-c/json.h>

#define MAX_METEO 50


 struct string {
    char *ptr;
    size_t len;
};

 void init_string(struct string *s);
 size_t writefunc(void *ptr, size_t size, size_t nmemb, struct string *s);
 void getMeteo(char * temp);