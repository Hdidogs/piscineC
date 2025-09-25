#include <stdio.h>
#include <string.h>

typedef struct {
    unsigned int x;
    unsigned int y;
    unsigned short live;
    unsigned short size;
} Ship;

int canPlaceBoat(char **map, int mapSize, int x, int y, char orientation, short shipSize) {
    int taille = 0;
    if (orientation=='n') {
        for (int i=x;i<mapSize || shipSize>0;i++) {

            if (i<mapSize ) {
                shipSize--;
                taille++;
            }else if (shipSize==0) {
                return 1;
            }else {
                return 0;
            }
        }
    }else if (orientation=='s') {
        for (int i=x;i>0 || shipSize>0;i--) {
            if (i>0&& shipSize>0) {
                shipSize--;
                taille++;

            }else if (shipSize==0) {
                return 1;
            }else {
                return 0;
            }
        }

    }else if (orientation=='o') {
        for (int i=y;i<mapSize || shipSize>0;i++) {
            if (i<mapSize&& shipSize>0) {
                shipSize--;
                taille++;
            }else if (shipSize==0) {
                return 1;
            }else {
                return 0;
            }
        }

    }else if (orientation=='e') {
        for (int i=y;i>0 || shipSize!=0;i--) {
            if (i>0 && shipSize!=0) {
                shipSize--;
                taille++;
            }else if (shipSize==0) {
                return 1;
            }else {
                return 0;
            }
        }
    }else {
        return 0;
    }
    return 1;
}

int main(void) {

    char mapeSize = 10;

    char map[10][10]={0};
    int b;
    b = canPlaceBoat(map, mapeSize, 2, 2, 'o', 2);
    printf("%d\n",b);
    return 0;
}