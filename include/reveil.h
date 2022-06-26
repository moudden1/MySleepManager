#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <string.h>
#include <wiringPi.h>
#include <mosquitto.h>
#include <signal.h>

void getTimeNow(int *h, int *min, int *s, int *day, int *mois, int *an);
void declencherBuzzer();
void on_connect(struct mosquitto *mosq, void *obj, int rc) ;
void on_message(struct mosquitto *mosq, void *obj, const struct mosquitto_message *msg);

typedef struct heureReveil heureReveil_t;
struct heureReveil
{
	int annee;
	int mois;
	int jour;
	int heure;
	int min;
	int notif;
	char destination[300];
	char mode[10];
	char titre[100];
	int duree_trajet;
};
