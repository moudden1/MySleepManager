#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <string.h>
void getTimeNow(int *h, int *min, int *s, int *day, int *mois, int *an);
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
  int *heureReveil =(int *)arg;
  getTimeNow(&h, &min, &s, &day, &mois, &an);
  printf("heure reveil %d %d %d %d %d\n",heureReveil[0],heureReveil[1], heureReveil[2],heureReveil[3],heureReveil[4]);
  
  while(an != heureReveil[0] || mois != heureReveil[1] || day != heureReveil[2]){
  	//printf("heure reveil 1%d %d %d %d %d\n",heureReveil[0],heureReveil[1], heureReveil[2],heureReveil[3],heureReveil[4]);
  	getTimeNow(&h, &min, &s, &day, &mois, &an);
  	//printf("now %d %d %d %d %d\n",an, mois, day, h, min);
  }
  delay(4000);
  while(h != heureReveil[3] || min != heureReveil[4])
  {
  	//printf("heure reveil %d %d %d %d %d\n",heureReveil[0],heureReveil[1], heureReveil[2],heureReveil[3],heureReveil[4]);
  	getTimeNow(&h, &min, &s, &day, &mois, &an);	
  	//printf("now %d %d %d %d %d\n",an, mois, day, h, min);
  }
 
  printf("time here !!!! \n");
}

int main(void)
{
  FILE *f;
  char c;
  int date[5]={0};
  char titre[100];
  char destination[300];
  char mode[10];
    pthread_t th;
    int heureReveil[10][5] = {0};
  f=fopen("agenda.txt","r");
  	int nblignes=0;
  	int nbligneslues=0;
  	while((c=fgetc(f))!=EOF){
        	if(c=='\n')
        	{
        		nblignes++;	
        	}
    	}
    	rewind(f); // renvoyer à la pos 0	
    	
  do
  {	
  	fscanf(f,"%d-%d-%dT%d:%d ",&date[0],&date[1],&date[2],&date[3],&date[4]);
  	int cpt=0;
  	while(cpt<10)
  	{
  		c=fgetc(f);
  		cpt++;
  	}
  	cpt=0;

  	while((c=fgetc(f))!='!')
  	{
  		titre[cpt]=c;
  		cpt++;
  	}
 	titre[cpt]='\0';
  	cpt=0;
  	
  	while((c=fgetc(f))!='!')
  	{
  		mode[cpt]=c;
  		cpt++;
  	}
  	mode[cpt]='\0';
  	cpt=0;
  	
  	while((c=fgetc(f))!='!')
  	{
  		destination[cpt]=c;
  		cpt++;
  	}
  	destination[cpt]='\0';
  	



  	int duree_trajet = getRoad(50.62925,3.057256, destination, mode);

  	printf("hre2 \n");

  	while(duree_trajet>0)
  	{
  		// a modifier pour prendre en compte heure <0 et jour mois année 
	  	while(date[4]>=0 && duree_trajet>0)
	  	{
	  		date[4]-=1;
	  		duree_trajet-=1;
	  	}
	  	if(duree_trajet>0)
	  	{
	  		date[3]-=1;
	  		date[4]=59;
	  	}
  	}
  
  	heureReveil[nbligneslues][0]=date[0];
  	heureReveil[nbligneslues][1]=date[1];
  	heureReveil[nbligneslues][2]=date[2];
  	heureReveil[nbligneslues][3]=date[3];
  	heureReveil[nbligneslues][4]=date[4];
  	pthread_create(&th, NULL, reveilThread, (void *)heureReveil[nbligneslues]);
  	while((c=fgetc(f))!='\n');
  	nbligneslues++;
  	
  }while(c!=EOF && nbligneslues!=nblignes);

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
