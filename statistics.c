#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "functions.h"

void printTopPlayers(Player players[], int playerCount){
	
	Player sortedPlayers[playerCount];
	
	for(int i = 0; i < playerCount; i++){
		
		sortedPlayers[i] = players[i];
		
	}
	
	 for (int j = 0; j < playerCount - 1; j++){
	 	
        int best = j;
        
        for (int k = j + 1; k < playerCount; k++) {
            
            if (sortedPlayers[k].wins > sortedPlayers[best].wins) {
                best = k;
            } 
            
            else if (sortedPlayers[k].wins == sortedPlayers[best].wins) {
                if (sortedPlayers[k].losses < sortedPlayers[best].losses) {
                    best = k;
                } 
                
                else if (sortedPlayers[k].losses == sortedPlayers[best].losses) {
                    if (sortedPlayers[k].draws < sortedPlayers[best].draws) {
                        best = k;
                    } 
                    
                    else if (sortedPlayers[k].draws == sortedPlayers[best].draws) {
                        if (sortedPlayers[k].username < sortedPlayers[best].username) {
                            best = k;
                        }
                    }
                }
            }
        }
        
        if (j != best) {
            Player temp = sortedPlayers[j];
            sortedPlayers[j] = sortedPlayers[best];
            sortedPlayers[best] = temp;
        }
    }

    displayTopPlayers(sortedPlayers);
}

void displayTopPlayers(Player sortedPlayers[]){
	
	int wins, losses, draws;
	
	printf("Top 5 Players\n");
	for(int i = 0; i < 5; i++){
		
		wins = sortedPlayers[i].wins;
		losses = sortedPlayers[i].losses;
		draws = sortedPlayers[i].draws;
		
		printf("[%d] %s (W: %d, L: %d, D: %d)\n", i + 1, sortedPlayers[i].username, wins, losses, draws);
	}
	
	printf("\nPress enter to continue...");
	getchar();
	getchar();
}

void printTopBattlePets(bpet battlePets[], int maxPets){
	
	bpet sortedPets[maxPets];
	
	for(int i = 0; i < maxPets; i++){
		
		sortedPets[i] = battlePets[i];
	}
	
	for(int j = 0; j < maxPets - 1; j++){
		
		int min = j;
		
		for(int k = j + 1; k < maxPets; k++){
			
			if(sortedPets[min].matches < sortedPets[k].matches){
				
				min = k;
			}
			
		}
		
		if(j != min){
			
			bpet temp = sortedPets[j];
			sortedPets[j] = sortedPets[min];
			sortedPets[min] = temp;
		}
	}
	
	displayTopPets(sortedPets);
}

void displayTopPets(bpet sortedPets[]){
	
	printf("Top 5 BattlePets:\n");
	
	for(int i = 0; i < 5; i++){
		
		printf("[%d] %s (%d matches)\n", i + 1, sortedPets[i].name, sortedPets[i].matches);
	}
	
	printf("\nPress enter to continue...");
	getchar();
	getchar();
}