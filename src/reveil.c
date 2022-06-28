#include "../include/reveil.h"


void *reveilThread(void *arg)
{
  int h, min, s, day, mois, an;
  int duree_trajet_thread;
  heureReveil_t *heureReveil =(heureReveil_t *)arg;
  getTimeNow(&h, &min, &s, &day, &mois, &an);
  int tempsrestant = 120;
  printf("titre de l'event %s \n",heureReveil->titre);
  printf("heure reveil %d %d %d %d %d\n",heureReveil->annee,heureReveil->mois, heureReveil->jour,heureReveil->heure,heureReveil->min);

  while(an != heureReveil->annee || mois != heureReveil->mois || day != heureReveil->jour){
  	getTimeNow(&h, &min, &s, &day, &mois, &an);
  }
  while(h != heureReveil->heure || min != heureReveil->min)
  {
  	if((heureReveil->heure * 60 + heureReveil->min ) > (h*60+min-tempsrestant))
  	{
		if(heureReveil->duree_trajet!=0)
		{
			int duree_trajet_thread = getDuration(50.62925,3.057256,heureReveil->destination, heureReveil->mode);
			if(duree_trajet_thread != heureReveil->duree_trajet)
			{
				int diff = duree_trajet_thread - heureReveil->duree_trajet;
				heureReveil->duree_trajet = duree_trajet_thread;
				printf("difference entre les deux %d avant moins de %d min  \n",diff,tempsrestant);
				delay(3000);
				if(diff > 0)
				{
					while(diff>0)
					{
						while(heureReveil->min>=0 && diff>0)
						{
							heureReveil->min-=1;
							diff-=1;
						}
						if(diff>0)
						{
							heureReveil->heure-=1;
							heureReveil->min=59;
						}
					}
				}
				else
				{
					while(diff<0)
					{
						while(heureReveil->min>=0 && diff<0)
						{
							heureReveil->min+=1;
							diff+=1;
						}
						if(diff<0)
						{
							heureReveil->heure+=1;
							heureReveil->min=59;
						}
					}
				}
			}
		}
		tempsrestant-=15;
		delay(3000);
  	}
  	getTimeNow(&h, &min, &s, &day, &mois, &an);	
  }
  
  int pid_fils; pid_fils = fork(); 
  switch(pid_fils) { 
  	case -1: 
  		printf("Ne peut pas crÃ©er un processus fils"); 
  		break; 

  	case 0: 
  		//declencherBuzzer();
  		break;
  	default: 
  		start_alarm_app(0, "");
  		kill(pid_fils, SIGKILL); 
		break;
	}
}

int main(void)
{
  /*déclaration des vars*/
  FILE *f;
  char c;
  int date[6]={0},nbligneslues=0,cpt=0;
  pthread_t th;
  heureReveil_t *heureReveil;


  /*lancement du programme python pour récuperer les events*/
	/*faire qlq chose qui necessite connex et tant que ca marche pas reste bloqué*/
  system("python3 src/quickstart.py");
	
   while(1)
   {
   	f=fopen("agenda.txt","r"); // fichier contenant les evenements
	if( c=fgetc(f) != EOF) // verifier qu'il contient une ligne
	{
	  	nbligneslues=1;
	}
	rewind(f);
  	if(nbligneslues>0) /// jusqu'à la fin du fichier
	{ 
			heureReveil= (heureReveil_t *)malloc(sizeof(heureReveil_t));

		  	fscanf(f,"%d-%d-%dT%d:%d",&date[0],&date[1],&date[2],&date[3],&date[4]);

		  	cpt=0;

		  	printf("heure evenement %d %d %d %d %d\n",date[0],date[1],date[2],date[3],date[4]);
		  	while(cpt<10)
		  	{
		  		c=fgetc(f);
		  		cpt++;
		  	}
		  	cpt=0;

		  	while((c=fgetc(f))!='!')
		  	{
		  		
		  		heureReveil->titre[cpt]=c;
		  		cpt++;
		  	}
		 	heureReveil->titre[cpt]='\0';
		  	cpt=0;

		  	while((c=fgetc(f))!='!')
		  	{
		  		heureReveil->mode[cpt]=c;
		  		cpt++;
		  	}
		  	heureReveil->mode[cpt]='\0';
		  	cpt=0;

		  	while((c=fgetc(f))!='!')
		  	{
		  		heureReveil->destination[cpt]=c;
		  		cpt++;
		  	}
		  	heureReveil->destination[cpt]='\0';
		  	cpt=0;

		  	char notifreveil[3]; 
		  	while((c=fgetc(f))!='!')
		  	{
		  		notifreveil[cpt]=c;
		  		cpt++;
		  	}
		  	notifreveil[cpt]='\0';
			int notifreveilenint=atoi(notifreveil);
			if(strcmp(heureReveil->destination,"vide")==0)
			{
				heureReveil->duree_trajet=0;
			}
			else
			{
		  		heureReveil->duree_trajet = getDuration(50.62925,3.057256,heureReveil->destination, heureReveil->mode);
			}
			int temp = heureReveil->duree_trajet;

		  	while(temp>0)
		  	{
		  		// a modifier pour prendre en compte heure <0 et jour mois année 
			  	while(date[4]>0 && temp>0)
			  	{
			  		date[4]-=1;
			  		temp-=1;
			  	}
			  	if(temp>0)
			  	{
			  		date[3]-=1;
			  		date[4]=59;
					temp--;
			  	}
		  	}
		  	while(notifreveilenint>0)
		  	{
		  		// a modifier pour prendre en compte heure <0 et jour mois année 
			  	while(date[4]>0 && notifreveilenint>0)
			  	{
			  		date[4]-=1;
			  		notifreveilenint-=1;
			  	}
			  	if(notifreveilenint>0)
			  	{
			  		date[3]-=1;
			  		date[4]=59;
					notifreveilenint--;
			  	}
				
		  	}
		  	
		  	heureReveil->annee = date[0];
		  	heureReveil->mois = date[1];
		  	heureReveil->jour = date[2];
		  	heureReveil->heure = date[3];
		  	heureReveil->min = date[4];
		  	
		  	pthread_create(&th, NULL, reveilThread, (void *)heureReveil);
//pthread_create(&th, NULL, reveilThread2, (void *)heureReveil[nbligneslues]);
		  	delay(2000);		  
		  }
  	while(1);
	
  //	  	delay(70000);// relancer le programme de recuperation des evenements chaque 30 secondes
	//  	system("python3 src/quickstart.py");
 }
  pthread_join(th, NULL);
  fclose(f);
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
  while (1)
  {
    digitalWrite (27, HIGH) ; delay (1) ;
    digitalWrite (27, LOW) ; delay (2) ;
    i++;
  }
}
// crontab

