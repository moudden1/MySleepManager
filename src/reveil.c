#include "../include/reveil.h"
void *sub_mqtt(void *arg)
{
	int rc, id=1245;

	mosquitto_lib_init();

	struct mosquitto *mosq;

	mosq = mosquitto_new("subscribe-test", true, &id);
	mosquitto_connect_callback_set(mosq, on_connect);
	mosquitto_message_callback_set(mosq, on_message);
	
	rc = mosquitto_connect(mosq, "mqtt.fluux.io", 1883, 10);
	if(rc) {
		printf("Could not connect to Broker with return code %d\n", rc);
		return -1;
	}

	mosquitto_loop_start(mosq);
	printf("Press Enter to quit...\n");
	getchar();
	mosquitto_loop_stop(mosq, true);

	mosquitto_disconnect(mosq);
	mosquitto_destroy(mosq);
	mosquitto_lib_cleanup();

	return 0;
}

void *reveilThread(void *arg)
{
  int h, min, s, day, mois, an;
  int duree_trajet_thread;
  heureReveil_t *heureReveil =(heureReveil_t *)arg;
  getTimeNow(&h, &min, &s, &day, &mois, &an);
  int tempsrestant = 120;
  printf("heure reveil %d %d %d %d %d\n",heureReveil->annee,heureReveil->mois, heureReveil->jour,heureReveil->heure,heureReveil->min);
  printf("titre de l'event %s \n",heureReveil->titre);

  while(an != heureReveil->annee || mois != heureReveil->mois || day != heureReveil->jour){
  	getTimeNow(&h, &min, &s, &day, &mois, &an);
  }
  while(h != heureReveil->heure || min != heureReveil->min)
  {
	//printf("1 %d \n",heureReveil->heure * 60 + heureReveil->min);
	//printf("%d \n",h*60+min-tempsrestant);
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
						// a modifier pour prendre en compte heure <0 et jour mois annÃ©e 
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
						// a modifier pour prendre en compte heure <0 et jour mois annÃ©e 
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
  	//	printf("nouvelle duree %d, temps resrtant moins de %d \n",heureReveil->duree_trajet,tempsrestant);
		tempsrestant-=15;
//printf("heure reveil %d %d %d %d %d\n",heureReveil->annee,heureReveil->mois, heureReveil->jour,heureReveil->heure,heureReveil->min);
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

/*void *reveilThread(void *arg)
{
  int h, min, s, day, mois, an;
  int duree_trajet_thread;
  heureReveil_t *heureReveil =(heureReveil_t *)arg;
  getTimeNow(&h, &min, &s, &day, &mois, &an);
  int tempsrestant = 120;
  printf("heure reveil %d %d %d %d %d\n",heureReveil->annee,heureReveil->mois, heureReveil->jour,heureReveil->heure,heureReveil->min);
  printf("titre de l'event %s \n",heureReveil->titre);

  while(an != heureReveil->annee || mois != heureReveil->mois || day != heureReveil->jour){
  	getTimeNow(&h, &min, &s, &day, &mois, &an);
  }
  while(h != heureReveil->heure || min != heureReveil->min)
  {
	//printf("1 %d \n",heureReveil->heure * 60 + heureReveil->min);
	//printf("%d \n",h*60+min-tempsrestant);
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
						// a modifier pour prendre en compte heure <0 et jour mois année 
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
						// a modifier pour prendre en compte heure <0 et jour mois année 
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
  	//	printf("nouvelle duree %d, temps resrtant moins de %d \n",heureReveil->duree_trajet,tempsrestant);
		tempsrestant-=15;
//printf("heure reveil %d %d %d %d %d\n",heureReveil->annee,heureReveil->mois, heureReveil->jour,heureReveil->heure,heureReveil->min);
		delay(3000);
  	}
  	getTimeNow(&h, &min, &s, &day, &mois, &an);	
  }
  //declencherBuzzer();
  start_alarm_app(NULL, NULL);
  printf("time here !!!! \n");
}*/
// todo : ajouter dans le 2
/*void *reveilThread2(void *arg)
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
  	getTimeNow(&h, &min, &s, &day, &mois, &an);	
  }
  //declencherBuzzer();
  printf("time here 2!!!! \n");
}*/



int main(void)
{
  /*déclaration des vars*/
  FILE *f,*f2,*f3;
  char c,c2;
  int date[6]={0};
  pthread_t th,th2;
  heureReveil_t *heureReveil[5];
  char phraseReveil[100][300] = {""};
  char phraseReveilTemp[300] = {""};
  int firstTime=1;
  int nblignes=0,nblignes2=0,cpt=0;
  int nbligneslues=0,k=0,m=0,quitter=0;

  /*lancement du programme python pour récuperer les events*/
	/*faire qlq chose qui necessite connex et tant que ca marche pas reste bloqué*/
  system("python3 src/quickstart.py");
	pthread_create(&th2, NULL, sub_mqtt, NULL);
	f3=fopen("sensor.txt","w+");
printf("a \n");
   while(1)
   {
   	f=fopen("agenda.txt","r"); // fichier contenant les evenements
	f2=fopen("events.txt","w+"); // ce fichier contenant les nouveaux evenements qui seront planifiés
	
  	nbligneslues=0;
  	k=0;
  	while((c=fgetc(f))!=EOF){ // jusqu'à la fin du fichier

  		if(firstTime==1) // premiere fois où l'utilisateur exécute le programme
  		{
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
				m=0;
				quitter=0;
				while(m<nblignes && quitter==0)
				{
					if(strcmp(phraseReveil[m],phraseReveilTemp)==0) // verification si cette ligne execute deja dans le tableau qui contient les évenements passés
					{
						printf("existe \n");
						quitter=1;
						memset(phraseReveilTemp,'\0',300);
						
					}
					m++;
				}
				if(quitter==0)
				{
						printf("un nouveau event %s \n",phraseReveilTemp);
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
    	while((c2=fgetc(f2))!=EOF){
    		if(c2=='\n')
    		{
    			nblignes2++;
    		}	
    	}
    	rewind(f2);
    	rewind(f); // renvoyer à la pos 0	
    	/*printf("nblignes %d \n",nblignes2);
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
	*/
	// debug a enlever plus tard
   	if(nblignes2 > 0){
		  do
		  {	
			heureReveil[nbligneslues] = (heureReveil_t *)malloc(sizeof(heureReveil_t));

		  	fscanf(f2,"%d-%d-%dT%d:%d",&date[0],&date[1],&date[2],&date[3],&date[4]);

		  	cpt=0;

		  	printf("heure evenement %d %d %d %d %d\n",date[0],date[1],date[2],date[3],date[4]);

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
			if(strcmp(heureReveil[nbligneslues]->destination,"vide")==0)
			{
				heureReveil[nbligneslues]->duree_trajet=0;
			}
			else
			{
		  		heureReveil[nbligneslues]->duree_trajet = getDuration(50.62925,3.057256,heureReveil[nbligneslues]->destination, heureReveil[nbligneslues]->mode);
			}
			int temp = heureReveil[nbligneslues]->duree_trajet;

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
		  	
		  	
		  

		  	heureReveil[nbligneslues]->annee = date[0];
		  	heureReveil[nbligneslues]->mois = date[1];
		  	heureReveil[nbligneslues]->jour = date[2];
		  	heureReveil[nbligneslues]->heure = date[3];
		  	heureReveil[nbligneslues]->min = date[4];
		  	
		  	pthread_create(&th, NULL, reveilThread, (void *)heureReveil[nbligneslues]);
//pthread_create(&th, NULL, reveilThread2, (void *)heureReveil[nbligneslues]);
		  	delay(2000);
		  	while((c=fgetc(f2))!='\n');
		  	nbligneslues++;
		  
		  }while(c!=EOF && nbligneslues!=nblignes2);
  	}
  	  	delay(30000);// relancer le programme de recuperation des evenements chaque 30 secondes
	  	system("python3 src/quickstart.py");
	  	firstTime=0;

 }
  pthread_join(th, NULL);
  pthread_join(th2, NULL);
  fclose(f);
  fclose(f2);
  fclose(f3);
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




void on_connect(struct mosquitto *mosq, void *obj, int rc) {
	printf("ID: %d\n", * (int *) obj);
	if(rc) {
		printf("Error with result code: %d\n", rc);
		exit(-1);
	}
	if(mosquitto_subscribe(mosq, NULL, "sensors/pulse", 2)!=MOSQ_ERR_SUCCESS){
		printf("Error with subscription \n");
		exit(-1);
	}
	else printf(" subscription ok \n");
	
	
}

void on_message(struct mosquitto *mosq, void *obj, const struct mosquitto_message *msg) {
	FILE *f;
	f=fopen("sensor.txt","a");
	fputs((char *) msg->payload, f);
	fputc('\n',f);
	printf("New message with topic %s",(char *) msg->payload);
	fclose(f);
}
