
#include "tabchainetri.h"

/*
// tabchaine.c 
*/
tabchaine tabchaineNouv()
{
	tabchaine t = (tabchaine)malloc(sizeof(struct s_tabchaine));
	if (t==NULL) { printf("memory allocation error.\n"); return NULL; }
	t->n_chaines=0;
	t->n_car=0;
	t->id_count=0;
	t->max_car = MAX_CAR;
	t->max_chaines=MAX_CHAINES;
	t->chaines = (char *)malloc(sizeof(char)*t->max_car);
	if (t->chaines==NULL) { printf("memory allocation error.\n"); free(t); return NULL; }
	unsigned int i;
	for (i=0; i<MAX_CAR; i++) t->chaines[i]=0;
	t->indices = (int *)malloc(sizeof(int)*t->max_chaines);
	if (t->indices==NULL) { printf("memory allocation error.\n"); free(t->chaines); free(t); return NULL; }
	t->adresse = (unsigned int *)malloc(sizeof(unsigned int)*t->max_chaines);
	if (t->adresse==NULL) { printf("memory allocation error.\n"); free(t->indices); free(t->chaines); free(t); return NULL; }
	t->indicestrie = (int *)malloc(sizeof(int)*t->max_chaines);
	if (t->indicestrie==NULL) { printf("memory allocation error.\n"); free(t->adresse); free(t->indices); free(t->chaines); free(t); return NULL; }
	return t;
}

void tabchaineFree(tabchaine t) 
{
	free(t->chaines);
	free(t->indices);
	free(t->indicestrie);
	free(t->adresse);
	free(t);
}

unsigned int tabchaineCardinal(tabchaine t) { return (unsigned int)t->n_chaines; }

// usage interne
int tabchaineRechPosInd(tabchaine t, char *str)
{
	int a = 0, b = t->n_chaines-1;
	while (a<b)
	{
		int m = (a+b)/2;
		int lg = strlen(str) < tabchaineLength(t, t->indicestrie[m]) ? strlen(str) : tabchaineLength(t, t->indicestrie[m]);
		int cmp = strncmp(t->chaines+t->adresse[t->indicestrie[m]],str,lg);
		if (cmp<0 || (cmp == 0 && strlen(str) > tabchaineLength(t, t->indicestrie[m]))) a = m + 1; else b = m;
	}
	return a;
}

// usage interne
int tabchaineRechPos(tabchaine t, char *str)
{
	int a = tabchaineRechPosInd(t,str);
	if (strlen(str) == tabchaineLength(t, t->indicestrie[a])) { if (strncmp(t->chaines + t->adresse[t->indicestrie[a]], str, strlen(str)) == 0) return a; }
	return -1; // not found, return value out of range
}
// usage interne
int tabchainePos(tabchaine t, int index)
{
	int a = 0, b = t->n_chaines-1;
	while (a<b)
	{
		int m = (a+b)/2;
		if (t->indices[m]==index) return m;
		if (t->indices[m]<index) a=m+1; else b=m-1;
	}
	if (t->indices[a]==index) return a;
	else return -1; // not found, return value out of range	
}
// usage interne
unsigned short tabchaineLength(tabchaine t, int pos)
{
	return strlen(t->chaines + t->adresse[pos]);
}

// adjonction
int tabchaineAdd(tabchaine t, char *str)
{
	unsigned int ll = strlen(str);
	if (ll+t->n_car>=t->max_car) // debordement memoire
	{
		t->chaines=(char *)realloc(t->chaines, sizeof(char)*(t->max_car+MAX_CAR));
		if (t->chaines==NULL) { printf("memory allocation error.\n"); exit(1); }
		t->max_car+=MAX_CAR;
	}
	if (t->n_chaines>=t->max_chaines) // debordement memoire
	{
		t->indices=(int *)realloc(t->indices, sizeof(int)*(t->max_chaines+MAX_CHAINES));
		if (t->indices==NULL) { printf("memory allocation error.\n"); exit(1); }
		t->indicestrie=(int *)realloc(t->indicestrie, sizeof(int)*(t->max_chaines+MAX_CHAINES));
		if (t->indicestrie==NULL) { printf("memory allocation error.\n"); exit(1); }
		t->adresse=(unsigned int *)realloc(t->adresse, sizeof(unsigned int)*(t->max_chaines+MAX_CHAINES));
		if (t->adresse==NULL) { printf("memory allocation error.\n"); exit(1); }
		t->max_chaines+=MAX_CHAINES;
	}
	// adjonction en queue de liste pour les indices et adresses
	t->adresse[t->n_chaines]=t->n_car;
	t->indices[t->n_chaines]=t->id_count;
	// adjonction en position pour indicetrie
	int pos = tabchaineRechPosInd(t,str);
	if (strncmp(t->chaines+t->adresse[t->indicestrie[pos]],str,strlen(str))<0) pos++;
	int i;
	for (i=t->n_chaines; i>pos; i--) t->indicestrie[i]=t->indicestrie[i-1];
	t->indicestrie[pos]=t->n_chaines;
	t->n_chaines++;
	// adjonction en queue pour les caracteres
	strcpy(t->chaines+t->n_car, str);
	t->n_car += ll+1;
	
	t->id_count++;
	return t->id_count-1;
}

// acces a la valeur, le resultat est dans str
void tabchaineGetChaine(tabchaine t, int index, char *str)
{
	unsigned int pos = tabchainePos(t, index);
	unsigned short ll = tabchaineLength(t,pos);
	unsigned int i;
	for (i=0; i<=(unsigned int)ll; i++) str[i]=t->chaines[t->adresse[pos]+i];
}
// recherche par clef
int tabchaineRech(tabchaine t, char *str)
{
	
	int i=tabchaineRechPos(t,str);
	if (i==-1) return -1; // not found, return value out of range
	else return t->indices[t->indicestrie[i]];
}

// supression
int tabchaineSup(tabchaine t, char *str)
{
	int i = tabchaineRechPos(t,str);
	if (i==-1) return -1;
	unsigned int a = i;
	unsigned int tindex=t->indicestrie[a];
	int index = t->indices[tindex];
	unsigned int car_pos = t->adresse[i];
	unsigned int length = tabchaineLength(t,tindex)+1;
	// supression dans un tableau->décaler les cases du tableau
	for (i=tindex; i<t->n_chaines-1; i++) t->indices[i]=t->indices[i+1];
	for (i=tindex; i<t->n_chaines-1; i++) t->adresse[i]=t->adresse[i+1]-length; // reajuster les adresses a cause du decalage
	t->n_chaines--;
	// idem pour le tableau contenant les caractères
	unsigned int j;
	for (j=car_pos; j<t->n_car-length; j++) t->chaines[j]=t->chaines[j+length];
	t->n_car-=length; 
	t->chaines[t->n_car]=0;
	// idem pour le tableau trie en decalant, en plus, les indices
	for (i=a; i<t->n_chaines; i++) t->indicestrie[i]=t->indicestrie[i+1];
	for (i=0; i<t->n_chaines; i++) if (t->indicestrie[i]>tindex) t->indicestrie[i]--;
	return index;
}


