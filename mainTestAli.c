#include <stdio.h>
#include <time.h>
#include <stdlib.h>



typedef struct {
    unsigned int x;
    unsigned int y;
    unsigned short live;
    unsigned short size;
} Ship;


int generateRandomXY(){
    int x = 10;
    int y = 10;
    int or = 4;
    char orientation;


    int randomX = rand() % x;
    int randomY = rand() % y;
    int randomOrientation = rand() % or;
    printf("Random X = %d\nRandom Y = %d\nRandomOrientation=%d\n", randomX, randomY, randomOrientation);

    switch (randomOrientation) {
     case 0:
             orientation='n';
            break;

     case 1:
             orientation='s';
            break;

     case 2:
             orientation='e';
            break;

     case 3:
             orientation='o';
            break;
 }
    printf("Random orientation =%c\n", orientation);
return 0;
    }

int placeRandomBoat(char **maps,int mapsize) {

}

int main() {
    srand(time(NULL));
    generateRandomXY();

}

