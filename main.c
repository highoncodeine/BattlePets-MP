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
	Player players[MAX_PLAYERS];
	bpet battlePets[20];
	
	countBattlePets("competdium.txt", &maxPets);
	loadBattlePets("competdium.txt", battlePets);
	
	loadPlayers(players, &playerCount);
	clrscr();
	
    startMenu(battlePets, players, maxPets, playerCount);
	
    return 0;

}