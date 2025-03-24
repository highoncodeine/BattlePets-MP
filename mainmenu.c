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
    printf("       BATTLE MENU       \n");
    printf("=========================\n");
    printf("[1] Create New Player\n");
    printf("[2] Select Player\n");
    printf("[3] Go Back to Start Menu\n");
    printf("=========================\n");
    printf("Select your input: ");
}

void displaySelect(){
	printf("=========================\n");
    printf("     PLAYER SELECTION       \n");
    printf("=========================\n");
    
}


void battleMenu(int *back, int playerCount, int maxPets, Player players[])
{
    int nInput;
    Player player1, player2;
    bpet battlePets[MAX_PETS];
    bpet roster1[9], roster2[9];
    int results[3][3];

    loadBattlePets("competdium.txt", battlePets); // Load BattlePets from competdium.txt
    countBattlePets("competdium.txt", &maxPets); // Count the number of BattlePets

    displayBattleMenu();
    scanf("%d", &nInput);

    switch (nInput)
    {
    case 1:
        clrscr();
        createNewPlayer();
        break;
    case 2:
        clrscr();
        loadPlayers(players, &playerCount);

        // Player 1 selects their player and roster
        displaySelect();
        selectPlayer(players, playerCount, &player1, 1, NULL);
        clrscr();
        printf("Player 1: %s, select your roster.\n", player1.username);
        selectRoster(&player1, battlePets, maxPets, roster1);

        // Player 2 selects their player and roster
        displaySelect();
        selectPlayer(players, playerCount, &player2, 2, &player1);
        clrscr();
        printf("Player 2: %s, select your roster.\n", player2.username);
        selectRoster(&player2, battlePets, maxPets, roster2);

        clrscr();
        printf("Both players have selected their players and rosters. Ready to battle!\n");
        Fight(&player1, &player2, roster1, roster2, results);
        showMatchResults(&player1, &player2, results);
        break;
    case 3:
        clrscr();
        *back = START_MENU;
        break;
    default:
        clrscr();
        printf("Invalid Input.\n\n");
        break;
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

void displayBattlePets(bpet battlePets[], int maxPets)
{
	loadBattlePets("competdium.txt", battlePets);
	countBattlePets("competdium.txt", &maxPets);
	
	printf("BATTLEPET LIST: \n\n");
    for (int i = 0; i < maxPets; i++) {
    	if(i < 10){
    		
        	printf(" [%d]  Name: %s\n", i, battlePets[i].name);
        } else {
        	 
        	printf("[%d]  Name: %s\n", i, battlePets[i].name);
		}
    }
}

void accessBattlePets(bpet battlePets[], int index){
	
	char* elementalType = checkElement(battlePets[index].element);
	
	printf("BattlePet Name: %s\n", battlePets[index].name);
	printf("Elemental Type: %s\n", elementalType);
	printf("Description: %s\n", battlePets[index].desc);
	printf("Matches: %d\n\n\n", battlePets[index].matches);
}

void viewBattlePetsMenu(bpet battlePets[], int *nInput, int maxPets)
{
    clrscr();
    
    loadBattlePets("competdium.txt", battlePets);
    countBattlePets("competdium.txt", &maxPets);
    
    displayBattlePets(battlePets, maxPets);
    printf("\nTo view the details of a Battlepet, enter its index, Otherwise ");
	printf("Press 0 to go Back: \n\n");
    scanf("%d", nInput);

	if(*nInput > 0 && *nInput < maxPets){
		
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

void displayDeleteMenu(bpet battlePets[], int maxPets){
	
	int bpetIndex;
	loadBattlePets("competdium.txt", battlePets);
    displayBattlePets(battlePets, maxPets);
    printf("\n Which BattlePet should be deleted: ");
    scanf("%d", &bpetIndex);
    deleteBattlePet(battlePets[bpetIndex].name);
}

void competdiumMenu(int *back, bpet battlePets[], int maxPets)
{
    int nInput = 0;

    clrscr();
    displayCompetdium();
    scanf("%d", &nInput);

    switch (nInput) {
        case 1:
            clrscr();
            do {
                viewBattlePetsMenu(battlePets, &nInput, maxPets);
            } while (nInput != 0);
            break;
        case 2:
            clrscr();
            addBattlePet(battlePets);
            break;
        case 3:
            clrscr();
			editBattlePets(battlePets, maxPets);
            break;
        case 4:
            clrscr();
            displayDeleteMenu(battlePets, maxPets);
            break;
        case 5:
            clrscr();
            bpet roster[9];
            saveRoster(battlePets, maxPets, roster);
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

void statisticsMenu(int *back, Player players[], bpet battlePets[], int maxPets, int playerCount)
{
    int nInput = 0;

    displayStatistics();
    scanf("%d", &nInput);

    switch (nInput) {
        case 1:
            clrscr();
            loadPlayers(players, &playerCount);
            printTopPlayers(players, playerCount);
            clrscr();
            break;
        case 2:
            clrscr();
            countBattlePets("competdium.txt", &maxPets);
            loadBattlePets("competdium.txt", battlePets);
            printTopBattlePets(battlePets, maxPets);
            clrscr();
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

void startMenu(bpet battlePets[], Player players[], int maxPets, int playerCount)
{
    int exit = 0;
    int input = 0;

    do {
        displayStartMenu();
        scanf("%d", &input);

        switch (input) {
            case 1:
                clrscr();
                do {
                    battleMenu(&input, playerCount, maxPets, players);
                } while (input != START_MENU);
                break;
            case 2:
                clrscr();
                do {
                    competdiumMenu(&input, battlePets, maxPets);
                } while (input != START_MENU);
                break;
            case 3:
                clrscr();
                do {
                    statisticsMenu(&input, players, battlePets, maxPets, playerCount);
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
