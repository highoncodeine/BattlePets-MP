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

void editBattlePet(bpet battlePets[]){
	
}

void deleteBattlePet(bpet battlePets[]){
	
}