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

// Function prototypes
void displayMenu();
int checkElementIndex(char* element);
char* checkElement(int element);

typedef struct bpet{
	char name[50];
	int element;
	char desc[300];
	int matches;
	
} bpet;

#endif