#include <stdio.h>
#include <stdlib.h>
#include "functions.h"
#include "mainmenu.c"
#include "competdium.c"

int main()
{
	bpet battlePets[20];
	
	loadBattlePets("competdium.txt", battlePets);
    startMenu(battlePets);

    return 0;

}