#include <stdio.h>
#include <stdlib.h>
#include "functions.h"
#include "battle.c"


void clrscr()
{
    system("@cls || clear");
}

void displayLanding(){
	
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf(" __________     _____    ___________ ___________ .____      ___________ __________  ___________ ___________   _________ \n");
    printf(" \\______   \\   /  _  \\   \\__    ___/ \\__    ___/ |    |     \\_   _____/ \\______   \\ \\_   _____/ \\__    ___/  /   _____/ \n");
    printf("  |    |  _/  /  /_\\  \\    |    |      |    |    |    |      |    __)_   |     ___/  |    __)_    |    |     \\_____  \\  \n");
    printf("  |    |   \\ /    |    \\   |    |      |    |    |    |___   |        \\  |    |      |        \\   |    |     /        \\ \n");
    printf("  |______  / \\____|__  /   |____|      |____|    |_______ \\ /_______  /  |____|     /_______  /   |____|    /_______  / \n");
    printf("         \\/          \\/                                  \\/         \\/                      \\/                      \\/ \n");
    printf("\n");
    printf("                                                   BY HADJJ AND JUSTIN                                                                            \n");
    printf("                                                 Press Enter to Continue");
	getchar();
	clrscr();
	
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
	clrscr();
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


void battleMenu(int *back, int playerCount, int maxPets, Player players[], const char *fileName) {
    int nInput;
    Player player1, player2;
    bpet battlePets[MAX_PETS];
    bpet roster1[9], roster2[9];
    int results[3][3];

    loadBattlePets(fileName, battlePets); // Load BattlePets from competdium.txt
    countBattlePets(fileName, &maxPets); // Count the number of BattlePets

    displayBattleMenu();
    scanf("%d", &nInput);

    switch (nInput) {
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

        // Simulate the battle
        simulateFight(&player1, &player2, roster1, roster2, results);

        // Show match results and save them
        showMatchResults(&player1, &player2, roster1, roster2, results, fileName);
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
    printf("[6] Import BattlePets\n");
    printf("[7] Go Back to Start Menu\n");
    printf("=========================\n");
    printf("Select your input: ");
}

void displayBattlePets(bpet battlePets[], int maxPets, const char *fileName)
{
	loadBattlePets(fileName, battlePets);
	countBattlePets(fileName, &maxPets);
	
	printf("=========================\n");
    printf("     BATTLEPET LIST     \n");
    printf("=========================\n\n");
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

void viewBattlePetsMenu(bpet battlePets[], int *nInput, int maxPets, const char *fileName)
{
    clrscr();
    
    loadBattlePets(fileName, battlePets);
    countBattlePets(fileName, &maxPets);
    
    displayBattlePets(battlePets, maxPets, fileName);
    printf("\nTo view the details of a Battlepet, enter its index, Otherwise ");
	printf("Input 0 to go Back: \n\n");
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

void displayDeleteMenu(bpet battlePets[], int maxPets, const char *fileName){
	
	int bpetIndex;
	loadBattlePets(fileName, battlePets);
    displayBattlePets(battlePets, maxPets, fileName);
    printf("\n Which BattlePet should be deleted: ");
    scanf("%d", &bpetIndex);
    deleteBattlePet(battlePets[bpetIndex].name, fileName);
}

void competdiumMenu(int *back, bpet battlePets[], int maxPets, char *fileName, Player players[], int playerCount) {
    int nInput = 0;

    clrscr();
    displayCompetdium();
    scanf("%d", &nInput);

    switch (nInput) {
        case 1:
            clrscr();
            do {
                viewBattlePetsMenu(battlePets, &nInput, maxPets, fileName);
            } while (nInput != 0);
            break;
        case 2:
            clrscr();
            addBattlePet(battlePets, fileName);
            break;
        case 3:
            clrscr();
            editBattlePets(battlePets, maxPets, fileName);
            break;
        case 4:
            clrscr();
            displayDeleteMenu(battlePets, maxPets, fileName);
            break;
        case 5:
            clrscr();
            bpet roster[9];
            saveRoster(players, playerCount, battlePets, maxPets, roster); 
            break;
        case 6:
            clrscr();
            importBattlePets(battlePets, maxPets, fileName);
            break;
        case 7:
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

void statisticsMenu(int *back, Player players[], bpet battlePets[], int maxPets, int playerCount, const char *fileName)
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
            countBattlePets(fileName, &maxPets);
            loadBattlePets(fileName, battlePets);
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

void startMenu(bpet battlePets[], Player players[], int maxPets, int playerCount, char *fileName)
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
                    battleMenu(&input, playerCount, maxPets, players, fileName);
                } while (input != START_MENU);
                break;
            case 2:
                clrscr();
                do {
                    competdiumMenu(&input, battlePets, maxPets, fileName, players, playerCount);
                } while (input != START_MENU);
                break;
            case 3:
                clrscr();
                do {
                    statisticsMenu(&input, players, battlePets, maxPets, playerCount, fileName);
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
