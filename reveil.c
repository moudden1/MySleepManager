#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
void getTimeNow(int *h, int *min, int *s, int *day, int *mois, int *an);

void *reveilThread(void *arg)
{
  int h, min, s, day, mois, an;
  int *heureReveil =(int *)arg;
  getTimeNow(&h, &min, &s, &day, &mois, &an);
  while(an != heureReveil[0] || mois != heureReveil[1] || day != heureReveil[2]){

  	getTimeNow(&h, &min, &s, &day, &mois, &an);
  }
  while(h != heureReveil[3] || min != heureReveil[4])
  {
  	getTimeNow(&h, &min, &s, &day, &mois, &an);	
  }
  printf("time here !!!! \n");
}

int main(void)
{
  pthread_t th;
  int heureReveil[5] = {2022, 05, 24, 15, 9};
int heureReveil2[5] = {2022, 05, 24, 15, 10};
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
