#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
void getTimeNow(int *h, int *min, int *s, int *day, int *mois, int *an);
typedef struct heureReveil heureReveil_t;
struct heureReveil
{
	int annee;
	int mois;
	int jour;
	int heure;
	int min;
};
void delay(int number_of_seconds)
{
    // Converting time into milli_seconds
    int milli_seconds = 1000 * number_of_seconds;
  
    // Storing start time
    clock_t start_time = clock();
  
    // looping till required time is not achieved
    while (clock() < start_time + milli_seconds)
        ;
}

void *reveilThread(void *arg)
{
  int h, min, s, day, mois, an;
  heureReveil_t *heureReveil =(heureReveil_t *)arg;
  getTimeNow(&h, &min, &s, &day, &mois, &an);
/*  while(an != heureReveil[0] || mois != heureReveil[1] || day != heureReveil[2]){
  	getTimeNow(&h, &min, &s, &day, &mois, &an);
  }
  while(h != heureReveil[3] || min != heureReveil[4])
  {
  	getTimeNow(&h, &min, &s, &day, &mois, &an);	
  }*/
  printf("time here !!!! \n");
}

int main(void)
{
  FILE *f;
  char c;
  heureReveil_t *heureReveil;
  heureReveil_t *heureReveil2;
  heureReveil = (heureReveil_t *)malloc(sizeof(heureReveil_t));
  heureReveil2 = (heureReveil_t *)malloc(sizeof(heureReveil_t));
  int date[3]={0};
  f=fopen("agenda.txt","r");
  do
  {	
  	printf("%c \n",c);
  	fscanf(f,"%d-%d-%dT%d:%d",&date[0],&date[1],&date[2],&date[3],&date[4]);
  	printf("%d %d %d %d %d\n",date[0],date[1],date[2],date[3],date[4]); 
  	delay(200);  	
  	while((c=fgetc(f))!='\n');
  }while((c=fgetc(f))!=EOF);
  printf("donZe\n");
  pthread_t th;
    printf("here\n");
  heureReveil->annee = 2022;
    printf("here\n");
  heureReveil->mois = 05;
  heureReveil->jour = 26;
  heureReveil->heure = 17;
  heureReveil->min = 00;
  heureReveil2->annee = 2022;
  heureReveil2->mois = 05;
  heureReveil2->jour = 26;
  heureReveil2->heure = 17;
  heureReveil2->min = 01;
  printf("here\n");
 // int heureReveil[5] = {2022, 05, 24, 15, 9};
 // int heureReveil2[5] = {2022, 05, 24, 15, 10};
  pthread_create(&th, NULL, reveilThread, (void *)heureReveil);
  pthread_create(&th, NULL, reveilThread, (void *)heureReveil2);
  pthread_join(th, NULL);
  return 0;
}

void getTimeNow(int *h, int *min, int *s, int *day, int *mois, int *an)
{
  time_t now;
  // Renvoie l'heure actuelle
  time(&now);
  // Convertir au format heure locale
  struct tm *local = localtime(&now);
  *h = local->tm_hour;        
  *min = local->tm_min;       
  *s = local->tm_sec;       
  *day = local->tm_mday;          
  *mois = local->tm_mon + 1;     
  *an = local->tm_year + 1900;  
}
// crontab
