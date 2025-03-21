#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "functions.h"

void printTopFive(Player players[], int playerCount){
	
	Player sortedPlayers[playerCount];
	
	for(int i = 0; i < playerCount; i++){
		
		sortedPlayers[i] = players[i];
		
	}
	
	for(int j = 0; j < playerCount - 1; j++){
		
		int min = j;
		
		for(int k = 0; k < playerCount; k++){
			
			if(sortedPlayers[min].wins > sortedPlayers[k].wins){
				
				min = k;
			}
			
		}
		
		if(j != min){
			
			Player temp = sortedPlayers[j];
			sortedPlayers[j] = sortedPlayers[min];
			sortedPlayers[min] = temp;
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
		
		printf("[%d] %s (W: %d, L: %d, D: %d)\n", i, sortedPlayers[i].username, wins, losses, draws);
	}
	
	printf("\nPress enter to continue...");
	getchar();
	getchar();
}