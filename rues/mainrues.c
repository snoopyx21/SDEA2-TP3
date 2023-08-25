
#include "tabchainetri.h"


/******************************************/
/******************************************/
int main(int argc, char* argv[])
{
	unsigned short i,j;

	printf("Tester tabchaine avec des noms de rue\n");
	tabchaine tt = tabchaineNouv();
	tabchaineAdd(tt,"Zellenberg");
	tabchaineAdd(tt,"Chapelle");
	tabchaineAdd(tt,"Altkirch");
	tabchaineAdd(tt,"Haute");
	tabchaineAdd(tt,"Ancienne ecole");
	tabchaineAdd(tt,"Saint Hippolyte");
	tabchaineAdd(tt,"Ziegelfeld");
	printf("Les indices:\n");
	for (i=0; i<tt->n_chaines; i++) printf("%d ",tt->indices[i]);
	printf(" (%u caracteres)\n", tt->n_car);
	for (i=0; i<tt->n_chaines; i++) printf("%d ",tt->indices[tt->indicestrie[i]]);
	printf("\n");

	printf("Cardinal = %u\n", tabchaineCardinal(tt));
	printf("recherche rue %s => ident= %d\n", "Haute",tabchaineRech(tt,"Haute"));
	printf("recherche rue %s => ident= %d\n", "Ancienne ecole",tabchaineRech(tt,"Ancienne ecole"));
	printf("recherche rue %s => ident= %d\n", "Langstross",tabchaineRech(tt,"Langstross"));
	char nrue[256]; 
	tabchaineGetChaine(tt, 0, nrue); printf("recherche ident %d => nom rue = %s\n", 0, nrue);
	tabchaineGetChaine(tt, 1, nrue); printf("recherche ident %d => nom rue = %s\n", 1, nrue);
	tabchaineGetChaine(tt, 6, nrue); printf("recherche ident %d => nom rue = %s\n", 6, nrue);
	printf("sup de Haute\n");
	tabchaineSup(tt,"Haute");
	printf("adj de Langstross\n");
	tabchaineAdd(tt,"Langstross");

	printf("Les indices:\n");
	for (i=0; i<tt->n_chaines; i++) printf("%d ",tt->indices[i]);
	printf(" (%u caracteres)\n", tt->n_car);
	for (i=0; i<tt->n_chaines; i++) printf("%d ",tt->indices[tt->indicestrie[i]]);
	printf("\n");
	printf("Cardinal = %u\n", tabchaineCardinal(tt));
	printf("recherche rue %s => ident= %d\n", "Haute",tabchaineRech(tt,"Haute"));
	printf("recherche rue %s => ident= %d\n", "Ancienne ecole",tabchaineRech(tt,"Ancienne ecole"));
	printf("recherche rue %s => ident= %d\n", "Langstross",tabchaineRech(tt,"Langstross"));
	tabchaineGetChaine(tt, 0, nrue); printf("recherche ident %d => nom rue = %s\n", 0, nrue);
	tabchaineGetChaine(tt, 1, nrue); printf("recherche ident %d => nom rue = %s\n", 1, nrue);
	tabchaineGetChaine(tt, 6, nrue); printf("recherche ident %d => nom rue = %s\n", 6, nrue);

	tabchaineFree(tt);
	return 0;
}

