#include "getDataGoogleMaps2.h"

// Documentation : https://developers.google.com/maps/documentation/directions/get-directions?hl=fr

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

int getDuration(double doubleLatitude, double doubleLongitude,char destination[MAX], char mode[10]){

    char URL_BASE[MAX];

    char stringLatitude[50];
    char stringLongitude[50];


    snprintf(stringLatitude, 50, "%f",doubleLatitude);
    snprintf(stringLongitude, 50, "%f",doubleLongitude);
    
    strcpy (URL_BASE,"https://maps.googleapis.com/maps/api/directions/json?origin=");
    strcat(URL_BASE,stringLatitude);
    strcat(URL_BASE,",");
    strcat(URL_BASE,stringLongitude);
    strcat(URL_BASE,"&destination=");
   

    CURL *curl;
    CURLcode res;

    curl_global_init(CURL_GLOBAL_DEFAULT);

    curl = curl_easy_init();

    if(curl) {

        struct string s;
        init_string(&s);
	char *destinationEncoder = curl_easy_escape(curl, destination,strlen(destination));
	strcat(URL_BASE,destinationEncoder);
	 if (strcmp(mode,"driving") == 0)
	 {
	 strcat(URL_BASE,"&avoid=tolls");
	 }
    	strcat(URL_BASE,"&mode=");
    	strcat(URL_BASE,mode);
    	strcat(URL_BASE,"&key=AIzaSyD1zIilw3kPVirr6-Oh_ST05b2zMAcgfIM");

	//printf("url final : %s\n",URL_BASE);
        curl_easy_setopt(curl, CURLOPT_URL, URL_BASE);

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writefunc);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &s);
		
        res = curl_easy_perform(curl);
	
        struct json_object *obj = json_tokener_parse(s.ptr);
        if (!obj) { fputs("json_tokener_parse failed\n", stderr); return 0; }
        struct json_object *routes = json_object_object_get(obj, "routes");
        if (!routes) { fputs("no routes\n", stderr); return 0; }

        struct json_object *route = json_object_array_get_idx(routes, 0);
        struct json_object *legs = json_object_object_get(route, "legs");
        size_t legslen = json_object_array_length(legs);

        struct json_object *duration = json_object_array_get_idx(legs, 0);
         
	return json_object_get_int(json_object_object_get(json_object_object_get(duration, "duration"), "value"))/60;
        if(res != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n",curl_easy_strerror(res));
        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();
    return 0;
}





