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

void addBattlePet(bpet battlePets[]){
	
	FILE *file = fopen("competdium.txt", "a");
	
	char name[50], desc[300];
	int element;
	int confirm = 0;
	
	do{
		clrscr();
		
		printf("Input the name of your Battlepet: ");
		scanf("%49s", name);
		getchar();
		
		clrscr();
		printf("Name: %s\n\n", name);
		
		printf("Input the element of your Battlepet:\n[0]Fire\n[1]Water\n[2]Grass\n[3]Earth\n[4]Air\n[5]Electric\n[6]Ice\n[7]Metal\n\n");
		scanf("%d", &element);
		getchar();
		
		clrscr();
		printf("Name: %s\n", name);
		printf("Element: %s\n\n", checkElement(element));
		
		printf("Write a short description for your Battlepet: ");
		fgets(desc, sizeof(desc), stdin);
		desc[strcspn(desc, "\n")] = 0;
		
		clrscr();
		printf("Name: %s\n", name);
		printf("Element: %s\n\n", checkElement(element));
		printf("%s\n\n", desc);
		
		printf("Is the battlepets info correct?\n[1] Yes\n[0] No\n>> ");
		scanf("%d", &confirm);
	
	} while(confirm == 0);
	
	fprintf(file, "%s\n", name);
	fprintf(file, "%s\n", checkElement(element));
	fprintf(file, "%s\n", desc);
	fputs("0\n", file);
	fputs("\n", file);
	
	clrscr();
	printf("Name: %s\n", name);
	printf("Element: %s\n\n", checkElement(element));
	printf("%s\n", desc);
	
    loadBattlePets("competdium.txt", battlePets);
    
	printf("Battlepet saved succesfully.\n");
	printf("Press Enter to continue...");
    getchar(); 
	getchar(); 
	
	clrscr();
	
	fclose(file);
	
}

void editBattlePets(bpet battlePets[], int maxPets){
	
	int nInput;
	int modifyInput;
	
	char newName[50];
	char newDesc[300];
	int newElement;
	int mainLoop = 1;
	
	do{
		displayBattlePets(battlePets, maxPets);
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
						loop = 0;
						break;
					case 2:
						
						do{
							printf("[0] Fire  [1] Water  [2] Grass  [3] Earth  [4] Air  [5] Electric  [6] Ice  [7] Metal\n");
							printf("Input New Element: ");
							scanf("%d", &newElement);
							getchar();
							
							if(newElement >= 0 && newElement <= 7){
								nInvalid = 0;
							} else {
								clrscr();
								printf("Invalid Input.\n\n");
							}
							loop = 0;
						} while (nInvalid);
						break;
					case 3:
						printf("Input New Description (MAX OF 300 CHARACTERS): ");
						getchar();
						fgets(newDesc, sizeof(newDesc), stdin);
						loop = 0;
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

void deleteBattlePet(bpet battlePets[]){
	
}
void saveRoster(bpet battlePets[], int maxPets, bpet roster[]) {
    char playerName[50];
    char filePath[100];
    FILE *file;

    clrscr();
    printf("Enter your player name: ");
    scanf("%49s", playerName);
    getchar();

    snprintf(filePath, sizeof(filePath), "saved_roster/%s.txt", playerName);

	createRoster(battlePets, maxPets, roster);

    file = fopen(filePath, "w");
    for (int i = 0; i < 9; i++) {
        fprintf(file, "%s\n", roster[i].name);
    }
    fclose(file);

    // Display the success message and wait for user acknowledgment
    printf("Roster saved successfully to %s.\n", filePath);
    printf("Press Enter to continue...");
    getchar(); // Consume the newline character left by scanf
    getchar(); // Wait for the user to press Enter

    clrscr(); // Clear the screen after the user presses Enter
}


