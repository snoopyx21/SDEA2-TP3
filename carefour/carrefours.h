#include "stdlib.h"
#include "string.h"
#include "memory.h"
#include "stdio.h"

/******************************************/
/*
// tabcarrefours.h 
Table de carrefours
*/

#define CODE_LEN 5
#define VOID_CODE '?'
#define NULL_CODE '+'


typedef struct s_tabcarrefours {
	char				*codes;
	unsigned int		taille_max;
	unsigned int		step;
} tabcarrefours;

tabcarrefours tabcarrefoursNouv(unsigned int max);
void tabcarrefoursFree(tabcarrefours t);
unsigned int tabcarrefoursCardinal(tabcarrefours t);
unsigned int tabcarrefoursAdd(tabcarrefours t, char str[CODE_LEN]);
unsigned int tabcarrefoursSup(tabcarrefours t, char str[CODE_LEN]);
int tabcarrefoursRech(tabcarrefours t, char str[CODE_LEN]);

// usage interne uniquement
unsigned int tabcarrefoursHache(tabcarrefours t, char str[CODE_LEN]);
unsigned int tabcarrefoursHacheNext(tabcarrefours t, unsigned int n, unsigned int prev);

