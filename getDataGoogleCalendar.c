#include <stdio.h>
#include <curl/curl.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#define MAX 300

// How to compile : gcc get.c -lcurl -ljson-c

// Lien du github utilisé 
// https://github.com/DaveGamble/cJSON#including-cjson 

#include <json-c/json.h>


struct string {
    char *ptr;
    size_t len;
};


void init_string(struct string *s) {
    s->len = 0;
    s->ptr = malloc(s->len+1);
    if (s->ptr == NULL) {
        fprintf(stderr, "malloc() failed\n");

    }
    s->ptr[0] = '\0';
}


size_t writefunc(void *ptr, size_t size, size_t nmemb, struct string *s)
{
    size_t new_len = s->len + size*nmemb;
    s->ptr = realloc(s->ptr, new_len+1);
    if (s->ptr == NULL) {
        fprintf(stderr, "realloc() failed\n");
    }
    memcpy(s->ptr+s->len, ptr, size*nmemb);
    s->ptr[new_len] = '\0';
    s->len = new_len;

    return size*nmemb;
}

void getRoad(double doubleLatitude, double doubleLongitude,char villeDestination[MAX]){

    char URL_BASE[MAX];

    char stringLatitude[50];
    char stringLongitude[50];

    snprintf(stringLatitude, 50, "%f",doubleLatitude);
    snprintf(stringLongitude, 50, "%f",doubleLongitude);

    strcpy (URL_BASE,"https://www.googleapis.com/calendar/v3/calendars/primary&key=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");
 /*
    strcat(URL_BASE,stringLatitude);
    strcat(URL_BASE,",");
    strcat(URL_BASE,stringLongitude);
    strcat(URL_BASE,"&destination=");
    strcat(URL_BASE,villeDestination);
    strcat(URL_BASE,"&avoid=tolls&mode=driving&key=AIzaSyD1zIilw3kPVirr6-Oh_ST05b2zMAcgfIM");
*/
    printf("url final : %s\n",URL_BASE);

    CURL *curl;
    CURLcode res;

    curl_global_init(CURL_GLOBAL_DEFAULT);

    curl = curl_easy_init();

    if(curl) {
	printf("in3al mok \n");
        struct string s;
        init_string(&s);

        curl_easy_setopt(curl, CURLOPT_URL, URL_BASE);

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writefunc);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &s);
	
        res = curl_easy_perform(curl);
	printf("s %s \n",s);
        struct json_object *obj = json_tokener_parse(s.ptr);
        if (!obj) { fputs("json_tokener_parse failed\n", stderr); return; }
	printf("obj %s \n",obj);
     /*   struct json_object *routes = json_object_object_get(obj, "routes");
        if (!routes) { fputs("no routes\n", stderr); return; }

        struct json_object *distance ;
        struct json_object *steps;

        size_t routeslen = json_object_array_length(routes);
        printf("There are %zd routes.\n", routeslen);
        for (size_t idx = 0; idx < routeslen; ++idx){
            printf("route %zd:\n", idx);
            struct json_object *route = json_object_array_get_idx(routes, idx);

            struct json_object *legs = json_object_object_get(route, "legs");
            size_t legslen = json_object_array_length(legs);

            for (size_t idy = 0; idy < legslen; ++idy){
                struct json_object *distance = json_object_array_get_idx(legs, idx);
                printf("Object Distance is %s\n", json_object_get_string(json_object_object_get(distance, "distance")));

                struct json_object *duration = json_object_array_get_idx(legs, idx);
                printf("Object duration is %s\n", json_object_get_string(json_object_object_get(duration, "duration")));

                struct json_object *end_location = json_object_array_get_idx(legs, idx);
                printf("Object end_location is %s\n", json_object_get_string(json_object_object_get(end_location, "end_location")));
            }

        }
        */

        if(res != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n",curl_easy_strerror(res));
        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();
}


int main(){

    getRoad(50.6265,3.0528,"Arras");
    return 0;

}

// Documentation : https://developers.google.com/maps/documentation/directions/get-directions?hl=fr
