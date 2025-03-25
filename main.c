#include <stdio.h>
#include <stdlib.h>
#include "functions.h"
#include "mainmenu.c"
#include "competdium.c"
#include "statistics.c"

int main()
{	
	int maxPets = 0;
	int playerCount = 0;
	char fileName[50] = "competdium.txt";
	
	Player players[MAX_PLAYERS];
	bpet battlePets[20];

	countBattlePets(fileName, &maxPets);
	loadBattlePets(fileName, battlePets);
	
	loadPlayers(players, &playerCount);
	clrscr();

	displayLanding();
	
    startMenu(battlePets, players, maxPets, playerCount, fileName);
	
    return 0;

}