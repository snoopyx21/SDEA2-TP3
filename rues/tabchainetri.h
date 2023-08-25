
#include "stdlib.h"
#include "string.h"
#include "memory.h"
#include "stdio.h"

/******************************************/
/*
// tabchainetri.h 
Table de chaines de caracteres, avec double indexation (double tri)
*/

#define MAX_CAR 50
#define MAX_CHAINES 5

typedef struct s_tabchaine {
	char				*chaines;
	int					*indices; // rangement par ordre alphabetique
	unsigned int		*adresse;
	int					*indicestrie; // rangement par indice
	int					id_count;

	unsigned short		n_chaines; 
	unsigned int		n_car;
	unsigned int		max_car;
	unsigned short		max_chaines;  
} *tabchaine;

tabchaine tabchaineNouv();
void tabchaineFree(tabchaine t);
unsigned int tabchaineCardinal(tabchaine t);
int tabchaineAdd(tabchaine t, char *str);
int tabchaineSup(tabchaine t, char *str);
// recherche de l'indice d'une chaine
int tabchaineRech(tabchaine t, char *str);
// recuperation de la chaine a partir de l'indice
void tabchaineGetChaine(tabchaine t, int index, char *str);

// usage interne uniquement
unsigned short tabchaineLength(tabchaine t, int pos);
int tabchaineRechPosInd(tabchaine t, char *str);
int tabchaineRechPos(tabchaine t, char *str);
int tabchainePos(tabchaine t, int index);

