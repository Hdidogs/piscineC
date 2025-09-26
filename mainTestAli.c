#include <stdio.h>
#include <time.h>
#include <stdlib.h>


typedef struct {
    unsigned int x;
    unsigned int y;
    unsigned short live;
    unsigned short size;
    char orientation;
} Ship;

typedef struct {
    Ship *ship;
    int **map;
    unsigned int size;
    unsigned int shipAllocation;
} Map;

int setMapValue(unsigned int x, unsigned int y, Map *map, int val) {
    if (x >= map->size || y >= map->size) return 0;
    map->map[x][y] = val;

    return 1;
}
int canPlaceBoat(Map *map, int x, int y, char orientation, short shipSize) {
    int taille = 0;
    if (orientation=='n') {
        for (int i=x;i<map->size || shipSize>0;i++) {

            if (i<map->size && shipSize>0&& map->map[x][i] == 0) {
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
            if (i>0&& shipSize>0&& map->map[x][i] == 0) {
                shipSize--;
                taille++;

            }else if (shipSize==0) {
                return 1;
            }else {
                return 0;
            }
        }

    }else if (orientation=='o') {
        for (int i=y;i<map->size || shipSize>0;i++) {
            if (i<map->size&& shipSize>0 && map->map[x][i] == 0) {
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
            if (i>0 && shipSize!=0&& map->map[x][i] == 0) {
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


int addShip(Map *map, Ship *ship) {
    if (map->shipAllocation == 0) {
        Ship *newShip = (Ship *)malloc(sizeof(Ship));
        newShip->x = ship->x;
        newShip->y = ship->y;
        newShip->orientation = ship->orientation;
        newShip->size = ship->size;

        map->shipAllocation++;
        map->ship = newShip;
    } else {
        Ship *temp = malloc(sizeof(Ship) * (map->shipAllocation +1));
        for (int i = 0; i < map->shipAllocation; i++) {
            temp[i] = map->ship[i];
        }

        temp[map->shipAllocation].x = ship->x;
        temp[map->shipAllocation].y = ship->y;
        temp[map->shipAllocation].orientation = ship->orientation;
        temp[map->shipAllocation].size = ship->size;

        free(map->ship);
        map->ship = temp;
        map->shipAllocation++;
    }

    for (int k = 0; k < ship->size; k++) {
        int x = ship->x + ship->orientation == 'n' ? -k : ship->orientation == 's' ? k : 0;
        int y = ship->y + ship->orientation == 'e' ? -k : ship->orientation == 'o' ? k : 0;
        if (map->map[x][y] == 0) {
            map->map[x][y] = 1;
        }
    }
}int canAttack(Map *map, int x, int y) {
    if (map->map[x][y] == 0) {
        setMapValue(x,y,map,-1);
        return 1;
    }else if (map->map[x][y] == 1) {
        setMapValue(x,y,map,-2);
        return 1;
    }else if (map->map[x][y] == -2) {
        return 0;
    }else if (map->map[x][y] == -1) {
        return 0;
    }
}
int tryPlaceBoat(Map *map, int x, int y,char orientation, Ship *ship ) {

    if (canPlaceBoat(map,x,y,ship->orientation,ship->size)) {
        ship->orientation = orientation;
        ship->x = x;
        ship->y = y;
        addShip(map,ship);
        return 1;
    }
    return 0;
}
void generateRandomXY( int *x, int *y) {
    int xTemp = 10;
    int yTemp = 10;

     *x = rand() % xTemp;
     *y = rand() % yTemp;

}

    int placeRandomBoat(Map *maps) {
    int or = 4;
    char orientation;
    int randomOrientation = rand() % or;
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
        int *x = malloc(sizeof(int ));
    int *y = malloc(sizeof(int ));
    generateRandomXY(x,y);
    if ( tryPlaceBoat( maps,  *x,  *y, orientation,  *ship))
        return 1;

    }


    int main() {
        srand(time(NULL));
    }
