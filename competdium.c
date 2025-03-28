#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "functions.h"

char *checkElement(int element){
	
	char *elements[] = {"Fire", "Water", "Grass", "Earth", "Air", "Electric", "Ice", "Metal"};
	
	return elements[element];
}

int checkElementIndex(char* element){
	
	int index = 0;
	
	char *elements[] = {"Fire", "Water", "Grass", "Earth", "Air", "Electric", "Ice", "Metal"};
	
	for(int i = 0; i < 8; i++){
		
		if(strcmp(element, elements[i]) == 0){
			
			index = i;
		}
	}
	
	return index;
}

void countBattlePets(const char *filename, int* maxPets){
	
	char line[500];
	int lineCount = 0;
	int battlePetCount = 0;
	
	FILE *file = fopen(filename, "r");
	
	if (!file) {
        perror("Error opening file");
        return;
    }
	
	while(fgets(line, sizeof(line), file)){
		
		lineCount++;
		if(lineCount % 5 == 0){
			
			battlePetCount++;
		}
	}
	
	fclose(file);
	
	*maxPets = battlePetCount;
}

void loadBattlePets(const char *filename, bpet battlePets[]){
	 
	char temp[50];
	
	FILE *file = fopen(filename, "r");
	
	if (!file) {
        perror("Error opening file");
        return;
    }

    char line[400];
    int index = 0;

    while (fgets(line, sizeof(line), file)){
        
        if (strlen(line) <= 1) continue;  
        strcpy(battlePets[index].name, strtok(line, "\n"));

        
        fgets(line, sizeof(line), file);
        strcpy(temp, strtok(line, "\n"));
        battlePets[index].element = checkElementIndex(temp);

        
        fgets(line, sizeof(line), file);
        strcpy(battlePets[index].desc, strtok(line, "\n"));

        
        fgets(line, sizeof(line), file);
        battlePets[index].matches = atoi(line);

        index++;
    }
    
    fclose(file);

}

void displayCreateBattlePetHeader(){
	
	printf("=========================\n");
    printf("  CREATE YOUR BATTLEPET\n");
    printf("=========================\n");
    printf("\n");
}

void addBattlePet(bpet battlePets[], const char *fileName){
	
	FILE *file = fopen(fileName, "a");
	
	char name[50], desc[300];
	int element;
	int confirm = 0;
	
	do{
		clrscr();
    	displayCreateBattlePetHeader();
    	
		printf("Input the name of your Battlepet: ");
		scanf("%49s", name);
		getchar();
		
		clrscr();
		
		displayCreateBattlePetHeader();
		printf("Name: %s\n\n", name);
		
		printf("Input the element of your Battlepet:\n[0]Fire\n[1]Water\n[2]Grass\n[3]Earth\n[4]Air\n[5]Electric\n[6]Ice\n[7]Metal\n\n");
		scanf("Select your Input: %d", &element);
		getchar();
		getchar();
		
		clrscr();
		displayCreateBattlePetHeader();
		printf("Name: %s\n", name);
		printf("Element: %s\n\n", checkElement(element));
		
		printf("Write a short description for your Battlepet: ");
		fgets(desc, sizeof(desc), stdin);
		desc[strcspn(desc, "\n")] = 0;
		
		clrscr();
		displayCreateBattlePetHeader();
		printf("Name: %s\n", name);
		printf("Element: %s\n", checkElement(element));
		printf("Description: %s\n\n", desc);
		
		printf("Is the battlepets info correct?\n[1] Yes\n[0] No\n>> ");
		scanf("%d", &confirm);
	
	} while(confirm == 0);
	
	
	fprintf(file, "%s\n%s\n%s\n0\n\n", name, checkElement(element), desc);
	
	clrscr();
	displayCreateBattlePetHeader();
	printf("Name: %s\n", name);
	printf("Element: %s\n", checkElement(element));
	printf("Description: %s\n", desc);
	
    loadBattlePets(fileName, battlePets);
    
	printf("\n[Battlepet saved succesfully]\n\n");
	printf("Press Enter to continue...");
    getchar(); 
	getchar(); 
	
	clrscr();
	
	fclose(file);
	
}

void editBattlePetName(const char *newName, const char *battlePetName, const char *fileName){
	
	FILE *file = fopen(fileName, "r");
	FILE *tempFile = fopen(TEMP_FILE, "w");
	char line[256];
	int foundName = 0;
	int nameUpdated = 0;
	
	while(fgets(line, sizeof(line), file)){
		
	    if (strncmp(line, battlePetName, strlen(battlePetName)) == 0 && line[strlen(battlePetName)] == '\n'){
	    	
	        fprintf(tempFile, "%s", newName); 
	        nameUpdated = 1;
	        
	    } else {
	        fprintf(tempFile, "%s", line);
	    }
	}
	
	fclose(file);
	fclose(tempFile);
	
	if (nameUpdated){
        if (remove(fileName) != 0 || rename(TEMP_FILE, fileName) != 0) {
            perror("Error updating file");
            exit(EXIT_FAILURE);
        }
        printf("\n\n[Name updated successfully]\n\n");
        
    } else {
        printf("Name '%s' not found in the file.\n", battlePetName);
        remove(TEMP_FILE); // Cleanup temporary file
    }
}

void editBattlePetElement(int newElementCode, const char *battlePetName, const char *fileName){
	
	FILE *file = fopen(fileName, "r");
	FILE *tempFile = fopen(TEMP_FILE, "w");
	char line[256];
	int foundElement = 0;
	int elementUpdated = 0;
	char newElement[30];
	
	strcpy(newElement, checkElement(newElementCode));
	
	while (fgets(line, sizeof(line), file)) {
        size_t len = strlen(line);
        if (len > 0 && line[len - 1] == '\n') {
            line[len - 1] = '\0'; 
        }

        if (foundElement) {
            fprintf(tempFile, "%s\n", newElement);
            elementUpdated = 1;
            foundElement = 0;
            
        } else if (strcmp(line, battlePetName) == 0) {
            fprintf(tempFile, "%s\n", line); 
            foundElement = 1;
            
        } else {
            
            fprintf(tempFile, "%s\n", line);
        }
    }
	
	fclose(file);
	fclose(tempFile);
	
	if(elementUpdated){
        if (remove(fileName) != 0 || rename(TEMP_FILE, fileName) != 0) {
            perror("Error updating file");
            exit(EXIT_FAILURE);
        }
        printf("\n\n[Element updated successfully]\n\n");
        
    } else {
        printf("Name '%s' not found in the file.\n", battlePetName);
        remove(TEMP_FILE); // Cleanup temporary file
    }
}

void editBattlePetDesc(const char *newDesc, const char *battlePetName, const char *fileName){
	
	FILE *file = fopen(fileName, "r");
    FILE *tempFile = fopen(TEMP_FILE, "w");
    char line[256];
    int foundName = 0;
    int lineCounter = 0;
    int descUpdated = 0;

    while (fgets(line, sizeof(line), file)){
    	
        size_t len = strlen(line);
        if (len > 0 && line[len - 1] == '\n') {
            line[len - 1] = '\0';
        }

        if(foundName && lineCounter == 1){
        	
            fprintf(tempFile, "%s", newDesc);
            descUpdated = 1;
            foundName = 0;
            lineCounter = 0;
            
        } else if (foundName){
        	
            fprintf(tempFile, "%s\n", line);
            lineCounter++;
            
        } else if (strcmp(line, battlePetName) == 0){
        	
            fprintf(tempFile, "%s\n", line);
            foundName = 1;
            lineCounter = 0;
            
        } else {
        	
            fprintf(tempFile, "%s\n", line);
        }
    }

    fclose(file);
    fclose(tempFile);

    if (descUpdated) {
    	
        if (remove(fileName) != 0 || rename(TEMP_FILE, fileName) != 0) {
        	
            perror("Error updating file");
            exit(EXIT_FAILURE);
        }
        
        printf("\n[Description updated successfully]\n\n");
        
    } else {
    	
        printf("Battle pet name '%s' not found in the file.\n", battlePetName);
        remove(TEMP_FILE);
    }
}

void incrementBattlePetMatches(char *battlePetName, const char *fileName){
	
	FILE *file = fopen(fileName, "r");
	FILE *tempFile = fopen(TEMP_FILE, "w");
	
	char line[256];
    int foundBattlePet = 0;
    int lineCounter = 0; // To track the line offset for matches

    while (fgets(line, sizeof(line), file)) {
        if (foundBattlePet) {
            lineCounter++;
            if (lineCounter == 3) {
                // This is the matches line we need to update
                int matches = atoi(line);  // Convert the line to an integer
                matches++;                 // Increment the matches
                fprintf(tempFile, "%d\n", matches);  // Write the updated matches to the temp file
                foundBattlePet = 0;        // Reset the flag
                lineCounter = 0;
            } else {
                fprintf(tempFile, "%s", line); // Write the current line to the temp file
            }
        } else {
            char *lineWithoutNewline = strtok(line, "\n"); // Remove newline from the read line
            fprintf(tempFile, "%s\n", lineWithoutNewline ? lineWithoutNewline : "");
            
            // Check if this line matches the battle pet name
            if (strcmp(line, battlePetName) == 0) {
                foundBattlePet = 1;   // Set the flag to track the next 4 lines
            }
        }
    }

    fclose(file);
    fclose(tempFile);

    // Replace the original file with the updated file
    if (remove(fileName) != 0) {
        perror("Error removing original file");
        return;
    }

    if (rename(TEMP_FILE, fileName) != 0) {
        perror("Error renaming temporary file");
        return;
    }
}


void deleteBattlePet(char *battlePetName, const char *fileName){
	
	FILE *file = fopen(fileName, "r");
	FILE *tempFile = fopen(TEMP_FILE, "w");
	char line[256];
	int foundName = 0;
	
	while (fgets(line, sizeof(line), file)){
		
        if (foundName > 0 && foundName < 5) {
            
            foundName++;
        } else if (strncmp(line, battlePetName, strlen(battlePetName)) == 0 && line[strlen(battlePetName)] == '\n') {
            
            foundName = 1;
        } else {
            
            fputs(line, tempFile);
        }
    }
	
	fclose(file);
	fclose(tempFile);
	
	if (foundName > 0){
        if (remove(fileName) != 0 || rename(TEMP_FILE, fileName) != 0) {
            perror("Error updating file");
            exit(EXIT_FAILURE);
        }
        printf("\nDeleted BattlePet Successfully.\n");
        printf("Press Enter to Continue");
        getchar();
        getchar();
        
    } else {
        printf("Name '%s' not found in the file.\n", battlePetName);
        remove(TEMP_FILE); // Cleanup temporary file
    }
}

void editBattlePets(bpet battlePets[], int maxPets, const char *fileName){
	
	int nInput;
	int modifyInput;
	
	char newName[50];
	char newDesc[300];
	int newElement;
	int mainLoop = 1;
	
	do{
		clrscr();
		loadBattlePets(fileName, battlePets);
		displayBattlePets(battlePets, maxPets, fileName);
		printf("\nWhich Battlepet would you like to edit?\n>> ");
		scanf("%d", &nInput);
		getchar();
		
		if(nInput >= 0 && nInput < maxPets){
			
			int loop = 1;
			int nInvalid = 1;
			
			do{
				clrscr();
				accessBattlePets(battlePets, nInput);
				printf("What would you like to modify?\n[1] Name\n[2] Element\n[3] Description\n>> ");
				scanf("%d", &modifyInput);
				
				clrscr();
				accessBattlePets(battlePets, nInput);
			
				switch(modifyInput) {
					case 1:
						printf("Input New Name (MAX OF 50 CHARACTERS): ");
						getchar();
						fgets(newName, sizeof(newName), stdin);
						
						editBattlePetName(newName, battlePets[nInput].name, fileName);
						printf("Press Enter to continue...");
   						getchar(); 
						
						loop = 0;
						mainLoop = 0;
						break;
						
					case 2:
						
						do{
							printf("[0] Fire  [1] Water  [2] Grass  [3] Earth  [4] Air  [5] Electric  [6] Ice  [7] Metal\n\n");
							printf("Input New Element: ");
							scanf("%d", &newElement);
							getchar();
							
							if(newElement >= 0 && newElement <= 7){
								
								nInvalid = 0;
								editBattlePetElement(newElement, battlePets[nInput].name, fileName);
								printf("Press Enter to continue...");
   								getchar(); 
   								
							} else {
								clrscr();
								printf("Invalid Input.\n\n");
							}
							
							loop = 0;
							mainLoop = 0;
							
						} while(nInvalid);
						break;
						
					case 3:
						printf("Input New Description (MAX OF 300 CHARACTERS): ");
						getchar();
						fgets(newDesc, sizeof(newDesc), stdin);
						
						editBattlePetDesc(newDesc, battlePets[nInput].name, fileName);
						printf("Press Enter to continue...");
   						getchar(); 
						
						loop = 0;
						mainLoop = 0;
						break;
						
					default:
						printf("Invalid Input.\n");
						break;
				}
				
			} while (loop);
			
		} else {
			clrscr();
			printf("[WARNING: INVALID INPUT]\n\n");
			mainLoop = 1;
		}
	} while(mainLoop);
}

char* getPassword(const char* playerName){
	
    static char password[256]; // Static to ensure memory stays valid after return
    char line[256];
    
    FILE* file = fopen("passwords.txt", "r");
    int foundPlayer = 0;

    if (file == NULL) {
        strcpy(password, "Error: Unable to open file.");
    } else {
        while (fgets(line, sizeof(line), file) != NULL) {
            // Remove newline character from the line
            line[strcspn(line, "\n")] = '\0';

            if (foundPlayer) {
                strcpy(password, line);
                foundPlayer = 0;
            } else if (strcmp(line, playerName) == 0) {
                foundPlayer = 1;
            }
        }

        if (!foundPlayer && password[0] == '\0') {
            strcpy(password, "none");
        }

        fclose(file);
    }

    return password;
}

void addNewPassword(const char *playerName, const char *newPassword){
	
	FILE* file = fopen("passwords.txt", "a"); // Open the file in append mode

    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    fprintf(file, "\n%s\n%s\n", playerName, newPassword); // Append player name and password
    fclose(file);
    
    printf("[Password has been added successfully]");
}


void inputPassword(const char* playerName, int *playerAccess){
	
	char* password = getPassword(playerName);
	char inputPass[50];
	
	if(strcmp("none", password) == 0){
		
		char newPassword[50];
		clrscr();
		
		printf("=========================\n");
	    printf("      SAVE A ROSTER       \n");
	    printf("=========================\n\n");
		
		printf("[Player %s has not set their password]\n\n", playerName);
		printf("Input New Password (Must be alphanumeric characters only): ");
		scanf("%30s", newPassword);
		addNewPassword(playerName, newPassword);
		*playerAccess = 1;
		
	} else {
		
		int count = 0;
		
		do{
			clrscr();
			printf("=========================\n");
		    printf("      SAVE A ROSTER       \n");
		    printf("=========================\n\n");
			
			printf("Player: %s\n\n", playerName);
			printf("Input Password: ");
			scanf("%s", &inputPass);
			
			if(strcmp(inputPass, password) == 0){
				
				*playerAccess = 1;
			} else {
				
				count++;
				printf("\n\nIncorrect Password %d tries remaining\n", 4 - count);
				printf("Press Enter to Continue...");
				getchar();
				getchar();
			}
			
		} while(count < 4 && *playerAccess != 1);
		
	}
}

void saveRoster(Player players[], int playerCount, bpet battlePets[], int maxPets, bpet roster[]) {
    int selectedPlayerIndex = -1;
    char filePath[100];
    FILE *file;

    clrscr();
    
    printf("=========================\n");
    printf("      SAVE A ROSTER       \n");
    printf("=========================\n\n");
    printf("Select a player to save a roster for:\n");

    
    for (int i = 0; i < playerCount; i++) {
        printf("[%d] %s\n", i + 1, players[i].username);
    }

    printf("\n>> ");
    scanf("%d", &selectedPlayerIndex);
    getchar(); 

    
    if (selectedPlayerIndex < 1 || selectedPlayerIndex > playerCount) {
        printf("Invalid selection. Press Enter to continue...");
        getchar();
    } else {
    	
    	clrscr();
    	int playerAccess = 0;

        selectedPlayerIndex--;
        
		inputPassword(players[selectedPlayerIndex].username, &playerAccess);
		
		if(playerAccess == 1){
       
	        snprintf(filePath, sizeof(filePath), "saved_roster/%s.txt", players[selectedPlayerIndex].username);
	
	        
	        createRoster(battlePets, maxPets, roster);
	
	        
	        file = fopen(filePath, "w");
	        if (!file) {
	            printf("Error: Could not save roster.\n");
	        } else {
	            for (int i = 0; i < 9; i++) {
	                fprintf(file, "%s\n", roster[i].name);
	            }
	            fclose(file);
	
	            
	            printf("\n\n[Roster saved successfully for %s to %s]\n\n", players[selectedPlayerIndex].username, filePath);
	            printf("Press Enter to continue...");
	            getchar(); 
	            getchar(); 
	        }
	    }
    
	}

    clrscr(); 
}

void importBattlePets(bpet battlePets[], int maxPets, char *fileName){
	
	char tempFileName[50];
	
    FILE *file;
    int fileExists = 0;
    
    printf("=========================\n");
    printf("    IMPORT BATTLEPETS       \n");
    printf("=========================\n\n");
    
    printf("Input the name of the txt file you want to import\n");
    printf("[WARNING] You must include the .txt extension\n\n");
    printf(">> ");
    scanf("%49s", tempFileName);

        
    file = fopen(tempFileName, "r");
    
    	if (file) {
            fclose(file);  // File exists, close it
            fileExists = 1; // Set flag to true
        } else {
            printf("Error: File '%s' does not exist\n\n", tempFileName);
        }
    
	if(fileExists == 1){
	    strcpy(fileName, tempFileName);
	
	    loadBattlePets(fileName, battlePets);
	    countBattlePets(fileName, &maxPets);
	    
	    printf("'%s' has been loaded.\n\n", fileName);
	}
	
    printf("\nPress Enter to Continue");
    getchar();
    getchar();
}


