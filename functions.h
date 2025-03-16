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
#define MAX_PETS 50
#define MAX_PLAYERS 50
#define MAX_USERNAME_LENGTH 37
#define PLAYER_FILE "players.txt"
#define MAX_LINE 100
#define TEMP_FILE "temp.txt"

// struct typedefs
typedef struct bpet {
    char name[50];
    int element;
    char desc[300];
    int matches;
} bpet;


typedef struct {
    char username[MAX_USERNAME_LENGTH + 1];
    int wins;
    int losses;
    int draws;
} Player;

// Function prototypes
void clrscr();
void displayStartMenu();
void displayBattleMenu();
void battleMenu(int *back);
void displayCompetdium();
void displayBattlePets(bpet battlePets[], int maxPets);
void accessBattlePets(bpet battlePets[], int index);
void viewBattlePetsMenu(bpet battlePets[], int *nInput, int maxPets);
void competdiumMenu(int *back, bpet battlePets[], int maxPets);
void displayStatistics();
void statisticsMenu(int *back);
void startMenu(bpet battlePets[], int maxPets);
void displaySelect();

// battle.c func prototypes
int getBattleResult(int element1, int element2);
int validateUsername(char *username);
void createNewPlayer();
void loadPlayers(Player players[], int *playerCount);
void selectPlayer(Player players[], int playerCount, Player *selectedPlayer, int playerNumber);
int loadSavedRoster(char *username, bpet roster[], bpet battlePets[], int maxPets);
void createRoster(bpet battlePets[], int maxPets, bpet roster[]);
void selectRoster(Player *player, bpet battlePets[], int maxPets, bpet roster[]);

// competdium.c func prototypes
char *checkElement(int element);
int checkElementIndex(char* element);
void countBattlePets(const char *filename, int* maxPets);
void loadBattlePets(const char *filename, bpet battlePets[]);
void addBattlePet(bpet battlePets[]);
void saveRoster (bpet battlePets[], int maxPets, bpet roster[]);


#endif