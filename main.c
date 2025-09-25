#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

Map *createMap(unsigned int size) {
    Map *map = (Map *)malloc(sizeof(Map));
    map->size = size;
    map->shipAllocation = 0;

    map->map = (int **)malloc(size * sizeof(int*));

    for (int i = 0; i < size; i++) {
        map->map[i] = (int *)malloc(size * sizeof(int));
        for (int j = 0; j < size; j++) {
            map->map[i][j] = 0;
        }
    }

    return map;
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
}

int getMapValue(unsigned int x, unsigned int y, Map *map) {
    if (x >= map->size || y >= map->size) return -1;

    return map->map[y+1][x+1];
}

int setMapValue(unsigned int x, unsigned int y, Map *map, int val) {
    if (x >= map->size || y >= map->size) return 0;
    map->map[x][y] = val;

    return 1;
}

void freeMap(Map *map) {
    free(map);
}

void printMap(Map *map) {
    int n = 1;
    char c = 'A';
    for (int i = 0; i < map->size + 1; i++) {
        for (int j = 0; j < map->size + 1; j++) {
            if (i == 0 && j != 0) {
                printf("%c ", c);
                c++;
            } else if (i != 0 && j != 0) {
                printf("%d ", map->map[i - 1][j - 1]);
            } else if (i != 0 && j == 0) {
                printf("%d ", n);
                n++;
            } else {
                printf("  ");
            }
        }
        printf("\n");
    }
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

int canAttack(Map *map, int x, int y) {
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

void setCoord(int l, char c, int *x, int *y) {
    *x=l-1;
    *y=c-65;
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


int main(void) {


    return 0;
}