#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "functions.h"



/**
 * Checks if a username is valid according to the specifications
 * @param username The username to validate
 * @return 1 if the username is valid, 0 otherwise
 */
int validateUsername(char *username) {
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
            // Valid character
        } else if (c == '@' || c == '_' || c == '-' || c == '+' || c == '#' || c == '$' || c == '!' || c == '.') {
            // Valid special character
        } else {
            // Invalid character
            return 0;
        }
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
    
    if (validateUsername(player.username) == 1)
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
        fprintf(file, "%s\n%d\n%d\n%d\n\n", player.username, player.wins, player.losses, player.draws);
        fclose(file);

        clrscr();
        printf("Player saved successfully!\n");
    }
    else
    {
        clrscr();
        printf("Invalid username. Player not saved.\n");
        return;
    }
}

void loadPlayers(Player players[], int *playerCount) {
    clrscr();
    FILE *file = fopen(PLAYER_FILE, "r");
    if (!file) {
        printf("Error opening file.\n");
    } else {
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

            // Skip the empty line
            fgets(buffer, sizeof(buffer), file);

            (*playerCount)++;
        }

        fclose(file);
        printf("Players loaded successfully.\n");
    }
}

void selectPlayer(Player players[], int playerCount, Player *selectedPlayer, int playerNumber) {
    int valid = 0;

    while (!valid) {
        clrscr();
        if (playerCount == 0) {
            printf("No players available.\n");
            valid = 1; // Exit the loop
        } else {
            printf("Player %d, select a player:\n", playerNumber);
            for (int i = 0; i < playerCount; i++) {
                printf("%d. %s\n", i + 1, players[i].username);
            }

            int choice;
            printf(">> ");
            scanf("%d", &choice);

            if (choice < 1 || choice > playerCount) {
                clrscr();
                printf("Invalid choice. Please try again.\n");
            } else {
                *selectedPlayer = players[choice - 1];
                clrscr();
                printf("Player %d has selected: %s\n", playerNumber, selectedPlayer->username);
                printf("Wins: %d\n", selectedPlayer->wins);
                printf("Losses: %d\n", selectedPlayer->losses);
                printf("Draws: %d\n", selectedPlayer->draws);

                
                // Wait for user input before clearing the screen
                printf("Press Enter to continue...");
                getchar(); // Consume the newline character left by scanf
                getchar(); // Wait for the user to press Enter
                valid = 1;
                
            }
        }
    }
}

int loadSavedRoster(char *username, bpet roster[], bpet battlePets[], int maxPets) {
    char filename[100];
    snprintf(filename, sizeof(filename), "saved_roster/%s.txt", username);
    FILE *file = fopen(filename, "r");
    int error = 0; // Error flag to track issues
    int i = 0;     // Counter for roster entries

    if (file == NULL) {
        printf("Error: Could not load saved roster for %s.\n", username);
        error = 1; // Set error flag
    } else {
        char line[50]; // Assuming BattlePet names are at most 49 characters long
        while (i < 9 && error == 0) {
            if (fgets(line, sizeof(line), file) != NULL) {
                line[strcspn(line, "\n")] = 0; // Remove the newline character

                // Find the BattlePet in the battlePets array by name
                int found = 0;
                for (int j = 0; j < maxPets; j++) {
                    if (strcmp(line, battlePets[j].name) == 0) {
                        roster[i] = battlePets[j]; // Copy the full BattlePet details to the roster
                        found = 1;
                    }
                }

                if (found == 0) {
                    printf("Error: BattlePet '%s' not found in ComPetDium.\n", line);
                    error = 1; // Set error flag
                } else {
                    i++;
                }
            } else {
                error = 1; // Set error flag if fewer than 9 lines are read
            }
        }

        fclose(file);

        if (i < 9 && error == 0) {
            printf("Error: Saved roster for %s is incomplete or corrupted.\n", username);
            error = 1; // Set error flag
        }
    }

    if (error == 0) {
        printf("Loaded saved roster for %s successfully.\n", username);

        // Display the final match roster
        printf("\nFinal Match Roster:\n");
        for (int i = 0; i < 9; i++) {
            printf("<%s> ", roster[i].name);
            if ((i + 1) % 3 == 0) printf("\n");
        }
    }

    return error == 0; // Return 1 for success, 0 for failure
}

void createRoster(bpet battlePets[], int maxPets, bpet roster[]) {
    int count = 0;

    while (count < 9) {
        clrscr(); // Clear the screen at the start of the loop
        printf("Match Roster:\n");
        for (int i = 0; i < 9; i++) {
            printf("<%s> ", count > i ? roster[i].name : "?");
            if ((i + 1) % 3 == 0) printf("\n");
        }

        printf("\nComPetDium:\n");
        for (int i = 0; i < maxPets; i++) {
            int alreadySelected = 0;
            for (int j = 0; j < count; j++) {
                if (strcmp(battlePets[i].name, roster[j].name) == 0) {
                    alreadySelected = 1;
                }
            }
            if (!alreadySelected) {
                printf("[%d] %s\n", i + 1, battlePets[i].name);
            }
        }

        printf(">> ");
        int choice;
        scanf("%d", &choice);

        if (choice < 1 || choice > maxPets) {
            printf("Invalid choice. Try again.\n");
            printf("Press Enter to continue...");
            getchar(); // Consume the newline character left by scanf
            getchar(); // Wait for the user to press Enter
        } else {
            int alreadySelected = 0;
            for (int j = 0; j < count; j++) {
                if (strcmp(battlePets[choice - 1].name, roster[j].name) == 0) {
                    alreadySelected = 1;
                }
            }

            if (alreadySelected) {
                printf("BattlePet already selected. Choose another.\n");
                printf("Press Enter to continue...");
                getchar(); // Consume the newline character left by scanf
                getchar(); // Wait for the user to press Enter
            } else {
                roster[count] = battlePets[choice - 1];
                count++;
            }
        }
    }

    // Final display of the completed roster
    clrscr();
    printf("Final Match Roster:\n");
    for (int i = 0; i < 9; i++) {
        printf("<%s> ", roster[i].name);
        if ((i + 1) % 3 == 0) printf("\n");
    }

}

void selectRoster(Player *player, bpet battlePets[], int maxPets, bpet roster[]) {
    int valid = 0;
    while (!valid) {
        clrscr(); // Clear the screen at the start of the menu
        printf("Player %s Roster\n", player->username);
        printf("[1] Load saved roster\n");
        printf("[2] Create roster for this match\n");
        printf(">> ");
        int choice;
        scanf("%d", &choice);

        if (choice == 1) {
            if (loadSavedRoster(player->username, roster, battlePets, maxPets)) {
                printf("Press Enter to continue...");
                getchar(); // Consume the newline character left by scanf
                getchar(); // Wait for the user to press Enter
                clrscr(); // Clear the screen after the user presses Enter
                valid = 1; // Exit the loop if loading was successful
            } else {
                printf("Returning to roster selection...\n");
                printf("Press Enter to continue...");
                getchar(); // Consume the newline character left by scanf
                getchar(); // Wait for the user to press Enter
            }
        } else if (choice == 2) {
            createRoster(battlePets, maxPets, roster);
            printf("Press Enter to continue...");
            getchar();
            getchar(); 
            clrscr(); 
            valid = 1; // Exit the loop after creating the roster
        } else {
            printf("Invalid choice. Please try again.\n");
            printf("Press Enter to continue...");
            getchar(); 
            getchar(); 
        }
    } 
}

int getBattleResult(int element1, int element2) {
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

void Fight(Player *player1, Player *player2, bpet roster1[], bpet roster2[], int results[3][3]){
    clrscr();
    printf("%s (Player 1) vs %s (Player 2)\n\n", player1->username, player2->username);
    printf("BattlePets, Fight!\n");
    
    
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
         int index = i * 3 + j;
         int result = getBattleResult(roster1[index].element, roster2[index].element);
         //display grid index and battlePets
         printf("[%d][%d] %s vs. %s\n", i, j, roster1[index].name, roster2[index].name); 
        
        // store result sa 2d array na results
        if (result == 1)
        results[i][j] = 1; // player 1 wins
        else if (result == -1)
        results[i][j] = 2; // player 2 wins
        else
        results[i][j] = 0; // draw
        
    }
    
}
    printf("\nPress Enter to continue... ");
    getchar();
}

void showMatchResults(Player *player1, Player *player2, int results[3][3]) {
    clrscr();
    int player1Wins = 0, player2Wins = 0;

    printf("\nMatch Results\n");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (results[i][j] == 1) player1Wins++;
            if (results[i][j] == 2) player2Wins++;

            /* 1: Player 1 wins
               2: Player 2 wins
               D: Draw         */
            if (results[i][j] == 1) {
                printf("[1] ");
            } else if (results[i][j] == 2) {
                printf("[2] ");
            } else {
                printf("[D] ");
            }
        }
        printf("\n");
    }

    // Lucky Win
    int luckyWin = 0;
    for (int i = 0; i < 3; i++) {
        // rows and columns
        if ((results[i][0] == results[i][1] && results[i][1] == results[i][2] && results[i][0] != 0) ||
            (results[0][i] == results[1][i] && results[1][i] == results[2][i] && results[0][i] != 0)) {
            luckyWin = results[i][i];
        }
    }
    // diagonals
    if ((results[0][0] == results[1][1] && results[1][1] == results[2][2] && results[0][0] != 0) ||
        (results[0][2] == results[1][1] && results[1][1] == results[2][0] && results[0][2] != 0)) {
        luckyWin = results[1][1];
    }

    // winner
    if (luckyWin == 1) {
        printf("\nWinner: %s (Player 1) [Lucky Win]\n", player1->username);
    } else if (luckyWin == 2) {
        printf("\nWinner: %s (Player 2) [Lucky Win]\n", player2->username);
    } else if (player1Wins > player2Wins) {
        printf("\nWinner: %s (Player 1) [Majority Win]\n", player1->username);
    } else if (player2Wins > player1Wins) {
        printf("\nWinner: %s (Player 2) [Majority Win]\n", player2->username);
    } else {
        printf("\nThe match is a draw!\n");
    }
    printf("Press Enter to play again... ");
    getchar();
    clrscr();

}











