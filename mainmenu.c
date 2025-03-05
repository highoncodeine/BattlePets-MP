#include <stdio.h>
#include <stdlib.h>
#include "functions.h"
#include "battle.c"



void clrscr()
{
    system("@cls || clear");
}

void displayStartMenu()
{
    printf("=========================\n");
    printf("        MAIN MENU       \n");
    printf("=========================\n");
    printf("[1] Battle!\n");
    printf("[2] ComPetDium\n");
    printf("[3] View Statistics\n");
    printf("[4] Exit\n");
    printf("=========================\n");
    printf("Select your input: ");
}

void displayBattleMenu()
{
    printf("=========================\n");
    printf("    SELECT PLAYER ONE       \n");
    printf("=========================\n");
    printf("[1] Create New Player\n");
    printf("[2] Load Player\n");
    printf("[3] Go Back to Start Menu\n");
    printf("=========================\n");
    printf("Select your input: ");
}

void displayPlayers(){
	printf("=========================\n");
    printf("    SELECT PLAYER ONE       \n");
    printf("=========================\n");
    
}

void battleMenu(int *back)
{
    int nInput = 0;
    
        displayBattleMenu();
        scanf("%d", &nInput);

        switch(nInput) {
            case 1:
                clrscr();
                createNewPlayer();
                break;
            case 2:
                clrscr();
                printf("To be continued");
                break;
            case 3:
                clrscr();
                *back = START_MENU;
        }
}
void displayCompetdium()
{
    printf("=========================\n");
    printf("     THE COMPETDIUM       \n");
    printf("=========================\n");
    printf("[1] View BattlePets!\n");
    printf("[2] Add Battlepet\n");
    printf("[3] Edit BattlePet\n");
    printf("[4] Delete Battlepet\n");
    printf("[5] Save a Roster\n");
    printf("[6] Go Back to Start Menu\n");
    printf("=========================\n");
    printf("Select your input: ");
}

void displayBattlePets(bpet battlePets[]){
	
	for(int i = 0; i < MAX_PETS; i++){
		
		printf("[%d]  Name: %s\n", i, battlePets[i].name);
	}
}

void accessBattlePets(bpet battlePets[], int index){
	
	char* elementalType = checkElement(battlePets[index].element);
	
	printf("%s\n\n", battlePets[index].name);
	printf("Elemental Type: %s\n", elementalType);
	printf("Description: %s\n", battlePets[index].desc);
	printf("Matches: %d\n\n\n", battlePets[index].matches);
}

void viewBattlePetsMenu(bpet battlePets[], int *nInput){
	
	clrscr();
	displayBattlePets(battlePets);
	printf("\nTo view the details of a Battlepet, enter its index, Otherwise ");
	printf("Press 0 to go Back: \n\n");
	scanf("%d", nInput);
	
	if(*nInput > 0 && *nInput < MAX_PETS){
		
		clrscr();
		accessBattlePets(battlePets, *nInput);
		
		printf("Press 0 to go Back: ");
		scanf("%d", nInput);
		if(*nInput != 0){
		}
		
	} else {
		
		printf("Invalid Input\n");
	}
}

void competdiumMenu(int *back, bpet battlePets[])
{
    int nInput = 0;
    	
    	clrscr();
        displayCompetdium();
        scanf("%d", &nInput);

        switch(nInput) {
            case 1:
                clrscr();
                do{
                viewBattlePetsMenu(battlePets, &nInput);	
				} while (nInput != 0);
				
                break;
            case 2:
                clrscr();
                printf("To be continued");
                break;
            case 3:
                clrscr();
                printf("To be continued");
                break;
            case 4:
                clrscr();
                printf("To be continued");
                break;
            case 5:
                clrscr();
                printf("To be continued");
                break;
            case 6:
                clrscr();
                *back = START_MENU;
                break;
            default:
                clrscr();
                printf("Invalid Input.\n\n");
        }
}

void displayStatistics()
{
    printf("=========================\n");
    printf("        STATISTICS       \n");
    printf("=========================\n");
    printf("[1] View Top Players\n");
    printf("[2] View Top Battlepets\n");
    printf("[3] Go Back to Start Menu\n");
    printf("=========================\n");
    printf("Select your input: ");
}

void statisticsMenu(int *back)
{
    int nInput = 0;

        displayStatistics();
        scanf("%d", &nInput);

        switch(nInput){
            case 1:
                clrscr();
                printf("To be continued");
                break;
            case 2:
                clrscr();
                printf("Top 5 Battlepets:\n 1.\n 2.");
                break;
            case 3:
                clrscr();
                *back = START_MENU;
                break;
            default:
                clrscr();
                printf("Invalid Input. \n\n");
                break;
        }
}


void startMenu(bpet battlePets[])
{   
    int exit = 0;
    int input = 0;

    do{
        displayStartMenu();
        scanf("%d", &input);
    
        switch (input) {
            case 1:
                clrscr();
                do{
                    battleMenu(&input);
                } while (input != START_MENU);
                break;
            case 2:
                clrscr();
                do{
                    competdiumMenu(&input, battlePets);
                } while (input != START_MENU);
                break;
            case 3:
                clrscr();
                do{
                    statisticsMenu(&input);
                } while (input != START_MENU);
                break;
            case 4:
                clrscr();
                printf("Thanks for playing. Closing Game.\n");
                exit = 1;
                break;
            default:
                clrscr();
                printf("Invalid Input.\n\n");
        }
    } while (exit == 0);   
}
