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

// Function prototypes
int checkElementIndex(char* element);
char* checkElement(int element);
int getBattleResult(int element1, int element2);
int username(char *username);
void createNewPlayer();

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

#endif