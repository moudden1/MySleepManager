#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <string.h>
#include <wiringPi.h>
#include "reveil.h"
void getTimeNow(int *h, int *min, int *s, int *day, int *mois, int *an);
void declencherBuzzer();

void *reveilThread(void *arg)
{
  int h, min, s, day, mois, an;
  int duree_trajet_thread;
  heureReveil_t *heureReveil =(heureReveil_t *)arg;
  getTimeNow(&h, &min, &s, &day, &mois, &an);
  printf("heure reveil %d %d %d %d %d\n",heureReveil->annee,heureReveil->mois, heureReveil->jour,heureReveil->heure,heureReveil->min);
	printf("titre de l'event %s \n",heureReveil->titre);

  while(an != heureReveil->annee || mois != heureReveil->mois || day != heureReveil->jour){
  	getTimeNow(&h, &min, &s, &day, &mois, &an);
  }
  while(h != heureReveil->heure || min != heureReveil->min)
  {
  	//if((heureReveil->heure * 60 + heureReveil->min ) > (h*60+min+120))
  	//{
  		//int duree_trajet_thread = getDuration(50.62925,3.057256,heureReveil->destination, heureReveil->mode);
  		/*if(duree_trajet_thread != )
  		{
  			
  		}*/
  		//printf("reste moins de 2 heures pour le reveil \n");
  		//de
  	//}
  	getTimeNow(&h, &min, &s, &day, &mois, &an);	
  }
  declencherBuzzer();
  printf("time here !!!! \n");
}

int main(void)
{
  FILE *f,*f2;
  char c,c2;
  int date[6]={0};

 
    pthread_t th;
  //  int heureReveil[5][5] = {0};
    heureReveil_t *heureReveil[5];
  char phraseReveil[100][300] = {""};
   char phraseReveilTemp[300] = {""};
  int firstTime=1;
    	int nblignes=0;
delay(30000);
system("python3 quickstart.py");
	printf("hre \n");
   while(1)
   {
printf("hre \n");
   	f=fopen("agenda.txt","r");
	f2=fopen("events.txt","w+");
printf("hre \n");
	int nblignes2=0;
    	while((c2=fgetc(f2))!=255){
    		if(c2=='\n')
    		{
    			nblignes2++;
    		}	
    	}
printf("hre \n");
    	rewind(f2);
printf("hre \n");
    	printf("nblignes22 %d \n",nblignes2);
printf("hre \n");
  	int nbligneslues=0;
  	int k=0;
printf("hre \n");
  	while((c=fgetc(f))!=255){
printf("hre \n");
  		if(firstTime==1)
  		{
printf("hre \n");
			if(c=='\n')
			{
				nblignes++;	
				k=0;
			}
			else
			{
				phraseReveil[nblignes][k]=c;
				k++;
			}
			fputc(c,f2);
        	}else
        	{
        		if(c=='\n')
			{
				printf("phraseReveilTemp %s \n",phraseReveilTemp);
				int m=0;
				int quitter=0;
				while(m<nblignes && quitter==0)
				{
					if(strcmp(phraseReveil[m],phraseReveilTemp)==0)
					{
						// an7al whd l fichier houwa fin andir ghir les events jdad, mais khass nstocki had jdad f phraseReveil normal bach l mara jaya nl9ahoum! 
						printf("existe \n");
						quitter=1;
						memset(phraseReveilTemp,'\0',300);
						
					}
					m++;
				}
				if(quitter==0)
				{
						printf("je vais l'ajouter %s \n",phraseReveilTemp);
						fputs(phraseReveilTemp, f2);
						fputc('\n',f2);
						strcpy(phraseReveil[nblignes],phraseReveilTemp);
						nblignes++;
						memset(phraseReveilTemp,'\0',300);
				}
				k=0;
			}
			else
			{
				phraseReveilTemp[k]=c;
				k++;
			}
        	}
    	}
    	k=0;
     	nblignes2=0;
    	rewind(f2);
    	while((c2=fgetc(f2))!=255){
    		if(c2=='\n')
    		{
    			nblignes2++;
    		}	
    	}
    	rewind(f2);
    	rewind(f); // renvoyer à la pos 0	
    	printf("nblignes %d \n",nblignes2);
    	char chaine[300] = ""; 
    	printf("f * ************** \n");
    	for(int l=0; l<nblignes; l++)
    	{
    		printf("%s \n",phraseReveil[l]);
    	}
    	printf("f * ************** \n");
    	printf("f2 * ************** \n");
    	int p=0;
    	while(f2 != NULL && nblignes2>p)
    	{
    		fgets(chaine, 300, f2);
    		printf("%s",chaine);
    		p++;
    	}
    	printf("f2 * ************** \n");
    	rewind(f2);
    	rewind(f); // renvoyer à la pos 0
    if(nblignes2 > 0){
  do
  {	
	heureReveil[nbligneslues] = (heureReveil_t *)malloc(sizeof(heureReveil_t));
  	fscanf(f2,"%d-%d-%dT%d:%d",&date[0],&date[1],&date[2],&date[3],&date[4]);

  	int cpt=0;

  	printf("heure initial %d %d %d %d %d\n",date[0],date[1],date[2],date[3],date[4]);

  	while(cpt<10)
  	{
  		c=fgetc(f2);
  		cpt++;
  	}
  	cpt=0;
  	while((c=fgetc(f2))!='!')
  	{
  		
  		heureReveil[nbligneslues]->titre[cpt]=c;
  		cpt++;
  	}
 	heureReveil[nbligneslues]->titre[cpt]='\0';
  	cpt=0;
  	while((c=fgetc(f2))!='!')
  	{
  		heureReveil[nbligneslues]->mode[cpt]=c;
  		cpt++;
  	}
  	heureReveil[nbligneslues]->mode[cpt]='\0';
  	cpt=0;
  	while((c=fgetc(f2))!='!')
  	{
  		heureReveil[nbligneslues]->destination[cpt]=c;
  		cpt++;
  	}
  	heureReveil[nbligneslues]->destination[cpt]='\0';
  	cpt=0;
  	char notifreveil[3]; 
  	while((c=fgetc(f2))!='!')
  	{
  		notifreveil[cpt]=c;
  		cpt++;
  	}
  	notifreveil[cpt]='\0';
	int notifreveilenint=atoi(notifreveil);

  	int duree_trajet = getDuration(50.62925,3.057256,heureReveil[nbligneslues]->destination, heureReveil[nbligneslues]->mode);



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
  	
  	while(notifreveilenint>0)
  	{
  		// a modifier pour prendre en compte heure <0 et jour mois année 
	  	while(date[4]>=0 && notifreveilenint>0)
	  	{
	  		date[4]-=1;
	  		notifreveilenint-=1;
	  	}
	  	if(notifreveilenint>0)
	  	{
	  		date[3]-=1;
	  		date[4]=59;
	  	}
  	}
  	
  	
  	
  

  	heureReveil[nbligneslues]->annee = date[0];
  	heureReveil[nbligneslues]->mois = date[1];
  	heureReveil[nbligneslues]->jour = date[2];
  	heureReveil[nbligneslues]->heure = date[3];
  	heureReveil[nbligneslues]->min = date[4];
  	
  	pthread_create(&th, NULL, reveilThread, (void *)heureReveil[nbligneslues]);
  	delay(2000);
  	while((c=fgetc(f2))!='\n');
  	nbligneslues++;
  
  }while(c!=255 && nbligneslues!=nblignes2);
  }
  	  	delay(30000);
	  	system("python3 quickstart.py");
	  	firstTime=0;

 }
  pthread_join(th, NULL);
  fclose(f);
  fclose(f2);
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

void declencherBuzzer()
{
	wiringPiSetup () ;
  pinMode (27, OUTPUT) ;
 int i=0;
  while (i<1000)
  {
    digitalWrite (27, HIGH) ; delay (1) ;
    digitalWrite (27, LOW) ; delay (2) ;
    i++;
  }
}
// crontab
