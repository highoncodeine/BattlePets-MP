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
#define PLAYER_FILE "players.txt"

// Define the bpet structure
typedef struct bpet {
    char name[50];
    int element;
    char desc[300];
    int matches;
} bpet;

// Define the Player structure
typedef struct {
    char username[MAX_USERNAME_LENGTH + 1];
    int wins;
    int losses;
    int draws;
} Player;

// Function prototypes
void loadBattlePets(const char *filename, bpet battlePets[]);
int checkElementIndex(char* element);
char* checkElement(int element);
int getBattleResult(int element1, int element2);
int username(char *username);
void createNewPlayer();
void LoadPlayers(Player players[], int *playerCount);
void SelectPlayer(Player players[], int playerCount, Player *selectedPlayer, int playerNumber);
void selectPlayers(Player players[], int playerCount, Player *player1, Player *player2);


#endif