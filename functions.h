#ifndef FUNCTIONS_H
#define FUNCTIONS_H

// Define Constants
#define FIRE 0
#define WATER 1
#define GRASS 2
#define EARTH 4
#define AIR 5
#define ELECTRIC 6
#define ICE 7
#define METAL 8
#define START_MENU 23
#define MAX_PETS 16
#define MAX_PLAYERS 50
#define MAX_USERNAME_LENGTH 37
#define MAX_LINE 100
#define PLAYER_FILE "players.txt"

// struct typedefs
typedef struct bpet{
	char name[50];
	int element;
	char desc[300];
	int matches;
	
} bpet;

typedef struct {
    char username[MAX_USERNAME_LENGTH +1];
    int wins;
    int losses;
    int draws;
} Player;

// mainmenu.c func prototypes
void clrscr();
void displayStartMenu();
void displayBattleMenu();
void battleMenu(int *back);
void displayCompetdium();
void displayBattlePets(bpet battlePets[]);
void accessBattlePets(bpet battlePets[], int index);
void viewBattlePetsMenu(bpet battlePets[], int *nInput);
void competdiumMenu(int *back, bpet battlePets[]);
void displayStatistics();
void statisticsMenu(int *back);
void startMenu(bpet battlePets[]);

// battle.c func prototypes
int getBattleResult(int element1, int element2);
int validateUsername(char *username);
void createNewPlayer();

// competdium.c func prototypes
char *checkElement(int element);
int checkElementIndex(char* element);
void loadBattlePets(const char *filename, bpet battlePets[]);


#endif