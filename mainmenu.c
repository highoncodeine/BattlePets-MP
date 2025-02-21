#include <stdio.h>
#include "functions.h"

// Displays the Menu :)
void displayMenu()
{
    printf("\n=========================\n");
    printf("        MAIN MENU       \n");
    printf("=========================\n");
    printf("[1] Battle!\n");
    printf("[2] ComPetDium\n");
    printf("[3] View Statistics\n");
    printf("[0] Exit\n");
    printf("=========================\n");
    printf("Enter your choice: ");
}
/*scans user input for choice :)
 param*/
int getChoice()
{
    int choice;
    displayMenu(); 
    scanf("%d", &choice);
    return choice;

}

void inputChoice(int choice)
{
    choice = getChoice();
    switch (choice) {
        case 1:
            printf("\n>>> Starting Battle Mode...\n");
            break;
        case 2:
            printf("\n>>> Opening ComPetDium...\n");
            break;
        case 3:
            printf("\n>>> Displaying Statistics...\n");
            break;
        case 0:
            printf("\n>>> Exiting program. Goodbye!\n");
            break;
        default:
            printf("\nInvalid choice! Please select a valid option.\n");
    }
}
