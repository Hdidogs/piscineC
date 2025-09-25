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
    map->map[y-1][x-1] = val;

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

int main(void) {
    const short AIRCRAFTCARRIERSIZE = 5;
    const short CRUISERSIZE = 4;
    const short DESTROYERSIZE = 3;
    const short TORPEDOSIZE = 2;

    return 0;
}