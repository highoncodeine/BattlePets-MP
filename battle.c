#include <stdio.h>

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

char *checkElement(int element){
	
	char *elements[] = { "Fire", "Water", "Grass", "Earth", "Air", "Electric", "Ice", "Metal"};
	
	return elements[element];
}

