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
void displayLanding();
void displayStartMenu();
void displayBattleMenu();
void battleMenu(int *back, int playerCount, int maxPets, Player players[], const char *fileName);
void displayCompetdium();
void displayBattlePets(bpet battlePets[], int maxPets, const char *fileName);
void accessBattlePets(bpet battlePets[], int index);
void viewBattlePetsMenu(bpet battlePets[], int *nInput, int maxPets, const char *fileName);
void competdiumMenu(int *back, bpet battlePets[], int maxPets, char *fileName, Player players[], int playerCount);
void displayStatistics();
void statisticsMenu(int *back, Player players[], bpet battlePets[], int maxPets, int playerCount, const char *fileName);
void startMenu(bpet battlePets[], Player players[], int maxPets, int playerCount, char *filename);
void displaySelect();

// battle.c func prototypes
int getBattleResult(int element1, int element2);
int validateUsername(char *username);
void createNewPlayer();
void loadPlayers(Player players[], int *playerCount);
void selectPlayer(Player players[], int playerCount, Player *selectedPlayer, int playerNumber, Player *alreadySelectedPlayer);
int loadSavedRoster(char *username, bpet roster[], bpet battlePets[], int maxPets);
void createRoster(bpet battlePets[], int maxPets, bpet roster[]);
void selectRoster(Player *player, bpet battlePets[], int maxPets, bpet roster[]);
void simulateFight(Player *player1, Player *player2, bpet roster1[], bpet roster2[], int results[3][3]);
void displayMatchResultsGrid(Player *player1, Player *player2, int results[3][3], int *player1Wins, int *player2Wins);
void showMatchResults(Player *player1, Player *player2, bpet roster1[], bpet roster2[], int results[3][3], const char *fileName);
void determineWinner(Player *player1, Player *player2, int results[3][3], int player1Wins, int player2Wins, char *winType, char *winner);
void updatePlayerStats(Player *player1, Player *player2, int results[3][3]);
void updateBattlePetStats(bpet roster1[], bpet roster2[], const char *fileName);
void saveMatchResults(Player *player1, Player *player2, bpet roster1[], bpet roster2[], int results[3][3], const char *winType, const char *winner);

// competdium.c func prototypes
char *checkElement(int element);
int checkElementIndex(char* element);
void countBattlePets(const char *filename, int* maxPets);
void loadBattlePets(const char *filename, bpet battlePets[]);
void editBattlePetName(const char *newName, const char *battlePetName, const char *fileName);
void editBattlePetElement(int newElementCode, const char *battlePetName, const char *fileName);
void editBattlePetDesc(const char *newDesc, const char *battlePetName, const char *fileName);
void incrementBattlePetMatches(char *battlePetName, const char *fileName);
void editBattlePets(bpet battlePets[], int maxPets, const char *fileName);
void deleteBattlePet(char *battlePetName, const char *fileName);
void addBattlePet(bpet battlePets[], const char *fileName);
char *getPassword(const char* playerName);
void addNewPassword(const char *playerName, const char *newPassword);
void inputPassword(const char* playerName, int *playerAccess);
void saveRoster(Player players[], int playerCount, bpet battlePets[], int maxPets, bpet roster[]);
void importBattlePets(bpet battlePets[], int maxPets, char *fileName);

// statistics.c func prototypes
void printTopPlayers(Player players[], int playerCount);
void displayTopPlayers(Player sortedPlayers[]);
void printTopBattlePets(bpet battlePets[], int maxPets);
void displayTopPets(bpet sortedPets[]);

#endif