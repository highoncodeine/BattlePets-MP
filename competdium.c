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

void loadBattlePets(const char *filename, bpet battlePets[]){
	 
	char temp[50];
	
	FILE *file = fopen(filename, "r");
	
    if (!file){
    	
        printf("Error: Could not open file.\n");
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

}

void addBattlePet(){
	
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
		
		clrscr();
		printf("Name: %s\n", name);
		printf("Element: %s\n\n", checkElement(element));
		printf("%s\n\n", desc);
		
		printf("Is the battlepets info correct?\n[1] Yes\n[0] No\n>> ");
		scanf("%d", &confirm);
	
	} while(confirm == 0);
	
	fprintf(file, "%s\n", name);
	fprintf(file, "%s\n", checkElement(element));
	fputs("0\n\n", file);
	
	clrscr();
	printf("Name: %s\n", name);
	printf("Element: %s\n\n", checkElement(element));
	printf("%s\n", desc);
	
	printf("Battlepet saved succesfully.\n");
	printf("Press Enter to continue...");
    getchar(); 
	getchar(); 
	
	clrscr();
	
	fclose(file);
}