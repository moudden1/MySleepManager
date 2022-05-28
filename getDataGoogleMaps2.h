#include <json-c/json.h>
#include <stdio.h>
#include <curl/curl.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#define MAX 300

struct string {
    char *ptr;
    size_t len;
};

void init_string(struct string *s);
size_t writefunc(void *ptr, size_t size, size_t nmemb, struct string *s);
int getRoad(double doubleLatitude, double doubleLongitude,char villeDestination[MAX]);
