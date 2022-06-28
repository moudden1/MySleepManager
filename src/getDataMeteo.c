#include "getDataMeteo.h"


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

void getMeteo(char * temp)
{
	CURL *hnd = curl_easy_init();
	
	if(hnd)
	{
		 struct string s;
       	 init_string(&s);
		curl_easy_setopt(hnd, CURLOPT_CUSTOMREQUEST, "GET");
		curl_easy_setopt(hnd, CURLOPT_URL, "https://community-open-weather-map.p.rapidapi.com/weather?q=Lens%2Cfr&units=metric&mode=json");


		struct curl_slist *headers = NULL;
		headers = curl_slist_append(headers, "X-RapidAPI-Key: 27de46402cmsh12fd7c7475b6225p18f68cjsn4358d13c3072");
		headers = curl_slist_append(headers, "X-RapidAPI-Host: community-open-weather-map.p.rapidapi.com");
		curl_easy_setopt(hnd, CURLOPT_HTTPHEADER, headers);
		curl_easy_setopt(hnd, CURLOPT_WRITEFUNCTION, writefunc);
        	curl_easy_setopt(hnd, CURLOPT_WRITEDATA, &s);
        	CURLcode ret = curl_easy_perform(hnd);
        	//printf("%s \n",s.ptr);
		struct json_object *obj = json_tokener_parse(s.ptr);
				//printf("%s \n",obj);
		if (!obj) { fputs("json_tokener_parse failed\n", stderr); return ; }

		struct json_object *routes = json_object_object_get(obj, "main");
		//printf("%s\n",json_object_get_string(json_object_object_get(routes, "temp")) );
		strcpy(temp,json_object_get_string(json_object_object_get(routes, "temp")));
		//return strcat(json_object_get_string(json_object_object_get(routes, "temp")),"°C");
	}
	sprintf(temp, "%s°C", temp);
	  
}

