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

// main menu.c func prototypes
void clrscr();
void displayStartMenu();
void displayBattleMenu();
void battleMenu(int *back, int playerCount, int maxPets, Player players[]);
void displayCompetdium();
void displayBattlePets(bpet battlePets[], int maxPets);
void accessBattlePets(bpet battlePets[], int index);
void viewBattlePetsMenu(bpet battlePets[], int *nInput, int maxPets);
void competdiumMenu(int *back, bpet battlePets[], int maxPets);
void displayStatistics();
void statisticsMenu(int *back, Player players[], bpet battlePets[], int maxPets, int playerCount);
void startMenu(bpet battlePets[], Player players[], int maxPets, int playerCount);
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
void Fight(Player *player1, Player *player2, bpet roster1[], bpet roster2[], int results[3][3]);
void displayMatchResultsGrid(int results[3][3], int *player1Wins, int *player2Wins);
void showMatchResults(Player *player1, Player *player2, int results[3][3]);
void determineWinner(Player *player1, Player *player2, int results[3][3], int player1Wins, int player2Wins);
void updatePlayerStats(Player *player1, Player *player2, int results[3][3]);
// competdium.c func prototypes
char *checkElement(int element);
int checkElementIndex(char* element);
void countBattlePets(const char *filename, int* maxPets);
void loadBattlePets(const char *filename, bpet battlePets[]);
void editBattlePetName(const char *newName, const char *battlePetName);
void editBattlePetElement(int newElementCode, const char *battlePetName);
void editBattlePetDesc(const char *newDesc, const char *battlePetName);
void editBattlePets(bpet battlePets[], int maxPets);
void deleteBattlePet(char *battlePetName);
void addBattlePet(bpet battlePets[]);
void saveRoster (bpet battlePets[], int maxPets, bpet roster[]);

// statistics.c func prototypes
void printTopPlayers(Player players[], int playerCount);
void displayTopPlayers(Player sortedPlayers[]);
void printTopBattlePets(bpet battlePets[], int maxPets);
void displayTopPets(bpet sortedPets[]);

#endif