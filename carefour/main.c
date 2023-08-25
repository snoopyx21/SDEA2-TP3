#include "carrefours.h"


int main()
{
	tabcarrefours tc;
	unsigned int i;
	char *carf[7] = { "ZW221" ,"ZW231" ,"ZW232", "ZW233" ,"ZW234" ,"ZW241", "ZW251" };
	tc = tabcarrefoursNouv(50);
	
	for (i=0; i<7; i++) printf("added %s: %u\n", carf[i], tabcarrefoursAdd(tc, carf[i]));

	printf("rech ZW220: %d\n", tabcarrefoursRech(tc,"ZW220"));
	printf("rech ZW231: %d\n", tabcarrefoursRech(tc,"ZW231"));
	printf("rech ZW221: %d\n", tabcarrefoursRech(tc,"ZW221"));

	printf("sup:%s: %u\n", "ZW221",tabcarrefoursSup(tc,"ZW221"));
	printf("sup:%s: %u\n", "ZW251", tabcarrefoursSup(tc,"ZW251"));
	printf("rech ZW220: %d\n", tabcarrefoursRech(tc,"ZW220"));
	printf("rech ZW231: %d\n", tabcarrefoursRech(tc,"ZW231"));
	printf("rech ZW221: %d\n", tabcarrefoursRech(tc,"ZW221"));
	
	printf("cardinal: %d\n", tabcarrefoursCardinal(tc));
}
