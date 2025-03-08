#include <stdio.h>
#include <stdlib.h>
#include "functions.h"
#include "mainmenu.c"
#include "competdium.c"

int main()
{	
	int maxPets = 0;
	bpet battlePets[20];
	
	countBattlePets("competdium.txt", &maxPets);
	loadBattlePets("competdium.txt", battlePets);
	
    startMenu(battlePets, maxPets);
	
    return 0;

}