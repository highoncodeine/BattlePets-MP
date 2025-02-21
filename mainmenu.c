#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

#define START_MENU 23

void clrscr()
{
    system("@cls || clear");
}

void displayStartMenu()
{
    printf("\n=========================\n");
    printf("        MAIN MENU       \n");
    printf("=========================\n");
    printf("[1] Battle!\n");
    printf("[2] ComPetDium\n");
    printf("[3] View Statistics\n");
    printf("[0] Exit\n");
    printf("=========================\n");
    printf("Select your input: ");
}

void displayBattleMenu()
{
    printf("\n=========================\n");
    printf("        BATTLE MENU       \n");
    printf("=========================\n");
    printf("[1] Create New Player\n");
    printf("[2] Load Player\n");
    printf("[3] Go Back to Start Menu\n");
    printf("=========================\n");
    printf("Select your input: ");
}

void battleMenu(int *back)
{
    int nInput = 0;
    
        displayBattleMenu();
        scanf("%d", &nInput);

        switch(nInput) {
            case 1:
                clrscr();
                printf("Enter Username: ");
                char username[37];
                scanf("%s", username);
                printf("Welcome, %s!\n", username);
                break;
            case 2:
                clrscr();
                printf("To be continued");
                break;
            case 3:
                clrscr();
                *back = START_MENU;
        }
}
void displayCompetdium()
{
    printf("\n=========================\n");
    printf("        THE COMPETDIUM       \n");
    printf("=========================\n");
    printf("[1] View BattlePets!\n");
    printf("[2] Add Battlepet\n");
    printf("[3] Edit BattlePet\n");
    printf("[4] Delete Battlepet\n");
    printf("[5] Save a Roster\n");
    printf("[6] Go Back to Start Menu\n");
    printf("=========================\n");
    printf("Select your input: ");
}

void competdiumMenu(int *back)
{
    int nInput = 0;
    
        displayCompetdium();
        scanf("%d", &nInput);

        switch(nInput) {
            case 1:
                clrscr();
                printf("To be continued");
                break;
            case 2:
                clrscr();
                printf("To be continued");
                break;
            case 3:
                clrscr();
                printf("To be continued");
                break;
            case 4:
                clrscr();
                printf("To be continued");
                break;
            case 5:
                clrscr();
                printf("To be continued");
                break;
            case 6:
                clrscr();
                *back = START_MENU;
        }
}

void startMenu()
{   
    int exit = 0;
    int input = 0;

    do{
        displayStartMenu();
        scanf("%d", &input);
    
        switch (input) {
            case 1:
                clrscr();
                do
                {
                    battleMenu(&input);
                } while (input != START_MENU);
                
                
                break;
            case 2:
                clrscr();
                do{
                    competdiumMenu(&input);
                } while (input != START_MENU);
                break;
            case 3:
                clrscr();
                printf("\n>>> Displaying Statistics...\n");
                break;
            case 0:
                clrscr();
                printf("\n>>> Exiting program. Thanks for Playing!\n");
                exit = 1;
                break;
            default:
                printf("\nInvalid choice! Please select a valid option.\n");
        }
    } while(exit == 0);   
}
