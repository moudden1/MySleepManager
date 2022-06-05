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
};
