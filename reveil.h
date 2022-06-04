typedef struct heureReveil heureReveil_t;
struct heureReveil
{
	int annee;
	int mois;
	int jour;
	int heure;
	int min;
	char destination[300];
	char mode[10];
};
