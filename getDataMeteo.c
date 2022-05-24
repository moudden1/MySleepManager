#include <stdio.h>
#include <curl/curl.h>
 
int main(void)
{
	struct curl_slist *headers = NULL;
	CURL *hnd = curl_easy_init();
	if(hnd)
	{
		curl_easy_setopt(hnd, CURLOPT_CUSTOMREQUEST, "GET");
		curl_easy_setopt(hnd, CURLOPT_URL, "https://community-open-weather-map.p.rapidapi.com/weather?q=Lens%2Cfr&units=metric&mode=json");


		headers = curl_slist_append(headers, "X-RapidAPI-Host: community-open-weather-map.p.rapidapi.com");
		headers = curl_slist_append(headers, "X-RapidAPI-Key: 279894ab9amsh4e06b1d95d7eccfp1d1d69jsn5e40552cda66");
		curl_easy_setopt(hnd, CURLOPT_HTTPHEADER, headers);
	}
	CURLcode ret = curl_easy_perform(hnd);
	  return 0;
}
