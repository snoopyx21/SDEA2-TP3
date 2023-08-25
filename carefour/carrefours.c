#include "carrefours.h"

/******************************************/
/*
// tabcarrefours.c 
Table de carrefours
*/

unsigned int tabcarrefoursHacheNext(tabcarrefours t, unsigned int n, unsigned int prev)
{
	if (n>=5) return (prev+t.step)% t.taille_max;
	else return (prev * 69069 + 907633385) % t.taille_max;
}
unsigned int tabcarrefoursHache(tabcarrefours t, char str[CODE_LEN])
{
	unsigned int i = 26*(unsigned int)(str[0]-'A')+(unsigned int)(str[1]-'A')
		+100*(unsigned int)(str[2]-'0')+10*(unsigned int)(str[3]-'0')+(unsigned int)(str[4]-'0');
	return tabcarrefoursHacheNext(t, 0, i);
}

tabcarrefours tabcarrefoursNouv(unsigned int max)
{
	tabcarrefours t;
	t.codes = (char *)malloc(sizeof(char)*CODE_LEN*max);
	if (t.codes==NULL) { printf("memory allocation error.\n"); t.taille_max=0; return t; }
	t.taille_max=max;
	unsigned int i;
	for (i=0; i<max; i++) { t.codes[CODE_LEN*i]=VOID_CODE; }
	t.step = 19;
	while(max%t.step==0) t.step+=2; // step ne doit pas etre un diviseur de max
	return t;
}

void tabcarrefoursFree(tabcarrefours t)
{
	free(t.codes);
}

unsigned int tabcarrefoursCardinal(tabcarrefours t)
{
	unsigned int count=0, i;
	for (i=0; i<t.taille_max; i++)
		if (t.codes[CODE_LEN*i]!=VOID_CODE && t.codes[CODE_LEN*i]!=NULL_CODE) count++;
	return count;
}

unsigned int tabcarrefoursAdd(tabcarrefours t, char str[CODE_LEN])
{
	unsigned int i;
	unsigned int p = tabcarrefoursHache(t, str);
	for (i=0; i<t.taille_max; i++)
	{
		if (t.codes[p*CODE_LEN]==VOID_CODE || t.codes[p*CODE_LEN]==NULL_CODE)
		{
			if (i>0) printf("warning: collision niv. %d\n", i);
			strncpy(&t.codes[p*CODE_LEN],str, CODE_LEN);
			return p;
		}
		p= tabcarrefoursHacheNext(t,i+1,p);
	}
	printf("Table is full! Cannot add.\n");
	return 0;
}

unsigned int tabcarrefoursSup(tabcarrefours t, char str[CODE_LEN])
{
	unsigned int i;
	unsigned int p = tabcarrefoursHache(t, str);
	for (i=0; i<t.taille_max; i++)
	{
		if (t.codes[p*CODE_LEN]==VOID_CODE) return 0; // cannot delete
		if (t.codes[p*CODE_LEN]!=NULL_CODE)
		{
			if (strncmp(&t.codes[p*CODE_LEN],str, CODE_LEN)==0)
			{
				t.codes[p*CODE_LEN]=NULL_CODE;
				return p;
			}
		}
		p = tabcarrefoursHacheNext(t, i + 1, p);
	}
	return 0;
}

int tabcarrefoursRech(tabcarrefours t, char str[CODE_LEN])
{
	unsigned int i;
	unsigned int p = tabcarrefoursHache(t, str);
	for (i=0; i<t.taille_max; i++)
	{
		if (t.codes[p*CODE_LEN]==VOID_CODE) return -1; // not found
		if (t.codes[p*CODE_LEN]!=NULL_CODE)
		{
			if (strncmp(&t.codes[p*CODE_LEN],str, CODE_LEN)==0)
			{
				return (int)p;
			}
		}
		p = tabcarrefoursHacheNext(t, i + 1, p);
	}
	return -1;
}
