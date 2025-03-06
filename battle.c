#include <stdio.h>
#include <string.h>
#include "functions.h"

int getBattleResult(int element1, int element2){
	
	int affinity[8][8] = {
        //            Fire Water Grass Earth Air Electric Ice Metal
        /*Fire*/    {  0,   -1,    1,    1,    0,    0,    1,   -1 },
        /*Water*/   {  1,    0,   -1,    0,    0,    1,   -1,    1 },
        /*Grass*/   { -1,    1,    0,    1,   -1,    1,   -1,    0 },
        /*Earth*/   { -1,    0,   -1,    0,    1,   -1,    0,    1 },
        /*Air*/     {  0,    0,    1,   -1,    0,    1,   -1,   -1 },
        /*Electric*/{  0,   -1,   -1,    1,   -1,    0,   -1,    1 },
        /*Ice*/     { -1,    1,    1,    0,    1,    1,    0,   -1 },
        /*Metal*/   {  1,   -1,    0,   -1,    1,   -1,    1,    0 }
    };
    
    return affinity[element1][element2]; // return 1 if element 1 wins, -1 if element 2 wins, 0 if it is a draw.
}



/**
 * Checks if a username is valid according to the specifications
 * @param username The username to validate
 * @return 1 if the username is valid, 0 otherwise
 */
int username(char *username) 
{
    int length = strlen(username);
    
    // Check if username is within the allowed length
    if (length == 0 || length > MAX_USERNAME_LENGTH) {
        return 0;
    }
    
    // Check if username is valid
    for (int i = 0; i < length; i++) {
        char c = username[i];
        
        // Check if character is alphanumeric
        if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9')) {
            continue;
        }
        
        // Check if character is one of the allowed special characters
        if (c == '@' || c == '_' || c == '-' || c == '+' || c == '#' || c == '$' || c == '!' || c == '.') {
            continue;
        }
        
        // Character is not allowed
        return 0;
    }
    
    // Check if username contains spaces
    for (int i = 0; i < length; i++) {
        if (username[i] == ' ') {
            return 0;
        }
    }
    
    return 1;
}

/**
 * Creates and saves the new player to a file
 */
void createNewPlayer()
{
    Player player;
    printf("New Player Username: ");
    scanf("%s", player.username);
    
    if (username(player.username) == 1)
    {
        player.wins = 0;
        player.losses = 0;
        player.draws = 0;

        // Save player data to a text file
        FILE *file = fopen(PLAYER_FILE, "a");
        if (!file) {
            printf("Error opening file.\n");
            return;
        }
        fprintf(file, "%s\n%d Wins\n%d Losses\n%d Draws\n\n", player.username, player.wins, player.losses, player.draws);
        fclose(file);

        printf("Player saved successfully!\n");
    }
    else
    {
        printf("Invalid username. Player not saved.\n");
        return;
    }
}

void LoadPlayers(Player players[], int *playerCount) {
    FILE *file = fopen(PLAYER_FILE, "r");
    if (!file) {
        printf("Error opening file.\n");
        return;
    }

    *playerCount = 0;
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), file) && *playerCount < MAX_PLAYERS) {
        // username
        strcpy(players[*playerCount].username, strtok(buffer, "\n"));

        // wins
        fgets(buffer, sizeof(buffer), file);
        players[*playerCount].wins = atoi(buffer);

        // losses
        fgets(buffer, sizeof(buffer), file);
        players[*playerCount].losses = atoi(buffer);

        // draws
        fgets(buffer, sizeof(buffer), file);
        players[*playerCount].draws = atoi(buffer);

        
        fgets(buffer, sizeof(buffer), file);

        (*playerCount)++;
    }

    fclose(file);
}

void SelectPlayer(Player players[], int playerCount, Player *selectedPlayer, int playerNumber) {
    if (playerCount == 0) {
        printf("No players available.\n");
        return;
    }

    printf("Player %d, select a player:\n", playerNumber);
    for (int i = 0; i < playerCount; i++) {
        printf("%d. %s\n", i + 1, players[i].username);
    }

    int choice;
    printf(">> ");
    scanf("%d", &choice);

    if (choice < 1 || choice > playerCount) {
        printf("Invalid choice. Please try again.\n");
        SelectPlayer(players, playerCount, selectedPlayer, playerNumber);
        return;
    }

    *selectedPlayer = players[choice - 1];
    printf("Player %d has selected: %s\n", playerNumber, selectedPlayer->username);
    printf("Wins: %d\n", selectedPlayer->wins);
    printf("Losses: %d\n", selectedPlayer->losses);
    printf("Draws: %d\n", selectedPlayer->draws);
}

void selectPlayers(Player players[], int playerCount, Player *player1, Player *player2) {
    printf("====================================\n");
    printf("          PLAYER SELECTION          \n");
    printf("====================================\n");
    SelectPlayer(players, playerCount, player1, 1);
    printf("====================================\n");
    printf("          PLAYER SELECTION          \n");
    printf("====================================\n");
    SelectPlayer(players, playerCount, player2, 2);
    
}







