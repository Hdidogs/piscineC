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

typedef struct {
    int grid_width;
    int grid_height;
    int ship_sizes[5];
} GameConfig;


int contain(char *chaine1, char *chaine2) {

    for(int i = 0; i < strlen(chaine2); i++) {
        if (chaine1[i]  != chaine2[i]) {
            return 0;

        }
    }
    return 1;
}

GameConfig *load_config(const char *filename, GameConfig *config) {
    // TODO: Ouvrir le fichier
    FILE *f = fopen(filename,"r");

    int gw = 0;
    int gh = 0;
    int index = 0;
    int *size = malloc(sizeof(int) * 5);

     if (f == NULL) {
        printf("File not found\n");
         FILE * f1 = fopen(filename,"w");
         fputs("# Configuration BattleChip\n",f);
         fputs("GRIDWIDTH = 10\n",f1);
         fputs("GRIDHEIGHT = 10\n",f1);
         fputs("SHIPCARRIER = 5\n",f1);
         fputs("SHIPBATTLESHIP = 4\n",f1);
         fputs("SHIPDESTROYER = 3\n",f1);
         fputs("SHIPDESTROYER = 3\n",f1);
         fputs("SHIPSUBMARINE = 2\n",f1);
         fclose(f1);
         load_config(f1,config);
    }else {

        char content[1000] = {0};
        int nb_lines = 0;
        char *commentaire ="#";
        char *gridWidth = "GRIDWIDTH";
        char *gridHeight = "GRIDHEIGHT";
        char *shipsizes = "SHIPBATTLESHIP";
        char *shipsizes1 = "SHIPDESTROYER";
        char *shipsizes2 = "SHIPSUBMARINE";
        char *shipsizes3 = "SHIPCARRIER";


        printf("File opened\n");
        //on parcour ligne par ligne le fichier
        // TODO: Parser ligne par ligne (ignorer # commentaires)
        // TODO: Extraire key=value
        while(fgets(content, sizeof(content), f)) {
            //si la ligne contien # on ne la lis pas
            if (contain(content, commentaire)==1) {
                continue;
            }//sinon on lis la ligne
            else {
                if (contain(content, gridWidth)) {
                    //printf("Grid width\n");
                    sscanf(content,"GRIDWIDTH = %d", &gw);
                    nb_lines++;
                }
                else if (contain(content, gridHeight)) {
                    //printf("grid height\n");
                    sscanf(content,"GRIDHEIGHT = %d", &gh);
                    nb_lines++;
                }
                else if (contain(content, shipsizes) ||
         contain(content, shipsizes1) ||
         contain(content, shipsizes2) ||
         contain(content, shipsizes3)) {

                    //printf("Ship sizes\n");

                    if (contain(content, shipsizes)) {
                        sscanf(content, "SHIPBATTLESHIP = %d", &size[index]);
                    }
                    else if (contain(content, shipsizes1)) {
                        sscanf(content, "SHIPDESTROYER = %d", &size[index]);
                    }
                    else if (contain(content, shipsizes2)) {
                        sscanf(content, "SHIPSUBMARINE = %d", &size[index]);
                    }
                    else if (contain(content, shipsizes3)) {
                        sscanf(content, "SHIPCARRIER = %d", &size[index]);
                    }

                    index++;
                    nb_lines++;
         }

                else {
                    //printf("DEBUG: Ligne %d: '%s'\n", nb_lines, content);
                    nb_lines++;
                }

            }


        }
        fclose(f);
        printf(" File closed\n");
    }

    // TODO: Valider les valeurs
    config->grid_width = gw;
    config->grid_height = gh;
    for(int i = 0; i < 5; i++) {
        config->ship_sizes[i] = size[i];
    }

    return config;

}

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
    int taille =ship->size;
    if (ship->orientation=='n') {

        for (int i=ship->x;taille!=0;i++) {

            if (map->map[i][ship->y] == 0) {
                map->map[i][ship->y] = 1;
                taille--;
            }
        }
    }else if (ship->orientation=='s') {
        for (int i=ship->x;taille!=0;i--) {
            if (map->map[i][ship->y] == 0) {
                map->map[i][ship->y] = 1;
                taille--;
            }
        }

    }else if (ship->orientation=='o') {
        for (int i=ship->y;taille!=0 ;i++) {
            if (map->map[ship->x][i] == 0) {
                map->map[ship->x][i] = 1;
                taille--;
            }
        }

    }else if (ship->orientation=='e') {
        for (int i=ship->y;taille!=0;i--) {
            if (map->map[ship->x][i] == 0) {
                map->map[ship->x][i] = 1;
                taille--;
            }
        }
    }else {
        return 0;
    }
}

int getMap2(unsigned int x, unsigned int y, Map *map) {
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

int canPlaceBoat(Map *map, Ship *ship, int shipSize) {
    int taille = 0;

    if (ship->orientation=='n') {
        for (int i=ship->x;i<map->size || shipSize>0;i++) {

            if (i<map->size && shipSize>0&& map->map[ship->x][i] == 0) {
                shipSize--;
                taille++;
            }else if (shipSize==0) {
                return 1;
            }else {
                return 0;
            }
        }
    }else if (ship->orientation=='s') {
        for (int i=ship->x;i>0 || shipSize>0;i--) {
            if (i>0&& shipSize>0&& map->map[ship->x][i] == 0) {
                shipSize--;
                taille++;

            }else if (shipSize==0) {
                return 1;
            }else {
                return 0;
            }
        }

    }else if (ship->orientation=='o') {
        for (int i=ship->y;i<map->size || shipSize>0;i++) {
            if (i<map->size&& shipSize>0 && map->map[ship->x][i] == 0) {
                shipSize--;
                taille++;
            }else if (shipSize==0) {
                return 1;
            }else {
                return 0;
            }
        }

    }else if (ship->orientation=='e') {
        for (int i=ship->y;i>0 || shipSize!=0;i--) {
            if (i>0 && shipSize!=0&& map->map[ship->x][i] == 0) {
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

    if (canPlaceBoat(map,ship,ship->size)) {

        ship->orientation = ship->orientation;
        ship->x = ship->x;
        ship->y = ship->y;
        addShip(map,ship);
        return 1;
    }
    return 0;
}

int canAttackRandom(Map *map, int x, int y) {
    int l;
    int c;

    if (map->map[x][y] == 0) {
        setMapValue(x,y,map,-1);
        for (int i = 0; i<4;i++) {
            c= rand()%map->size;
            l = rand()%map->size;
            canAttack(map,l,c);

        }

    }else if (map->map[x][y] == 1) {
        setMapValue(x,y,map,-2);
        for (int i = 0; i<4;i++) {
            c= rand()%map->size;

            l = rand()%map->size;
            canAttack(map,l,c);
        }
    }else if (map->map[x][y] == -2) {

        return 0;
    }else if (map->map[x][y] == -1) {

        return 0;
    }else {
        return 0;
    }

    return 1;
}

int canAttackNuke(Map *map, int x, int y) {

    if (map->map[x][y] == 0) {
        setMapValue(x,y,map,-1);
    }else if (map->map[x][y] == 1) {
        setMapValue(x,y,map,-2);
    }else if (map->map[x][y] == -2) {

        return 0;
    }else if (map->map[x][y] == -1) {

        return 0;
    }else {
        return 0;
    }
    int dx[] = { 1, -1,  1, -1,  0,  0,  1, -1 };
    int dy[] = {-1,  1,  1, -1, -1,  1,  0,  0 };

    for (int i = 0; i < 8; i++) {
        canAttack(map, x + dx[i], y + dy[i]);
    }
    return 1;
}


int canAttackCross(Map *map, int x, int y) {
    if (map->map[x][y] == 0) {
        setMapValue(x,y,map,-1);

    }else if (map->map[x][y] == 1) {
        setMapValue(x,y,map,-2);


    }else if (map->map[x][y] == -2) {

        return 0;
    }else if (map->map[x][y] == -1) {

        return 0;
    }else {
        return 0;
    }

    int dx[] = { 1, -1,  1, -1};
    int dy[] = {-1,  1,  1, -1};

    for (int i = 0; i < 8; i++) {
        canAttack(map, x + dx[i], y + dy[i]);
    }
    return 1;

}

int verifVictoire(Map *map) {
    for (int i = 0; i < map->size; i++) {
        for (int j = 0; j < map->size; j++) {
            if (map->map[i][j] == 1) {
                return 0;
            }
        }
    }
    return 1;
}

int main(void) {

    GameConfig *config = malloc(sizeof(GameConfig));
    char *filename= "config.txt";

    load_config(filename,config);


    printf("=== Bienvenue dans le jeu de la Bataille Navale ===\n");
    printf("1. Jouer en Solo\n");
    printf("2. Jouer a 2 Joueurs\n");
    printf("Votre choix : ");
    int choix;
    scanf("%d", &choix);

    if (choix == 1) {
        Map *map = createMap(10);
        Ship *ship= malloc(sizeof(Ship));

        for (int i = 0; i < 5; i++) {
            ship->size= config->ship_sizes[i];
            char *name;
            if (ship->size==5) {
                name="carrier";
            }else if (ship->size==4) {
                name="Battleship";
            }else if (ship->size==3) {
                name="destroyer";
            }else if (ship->size==2) {
                name="Submarine";
            }
            int l;
            printf("Entree les Coordonee du bateau %s de longueur %d\n",name,ship->size);
            printf("x :");
            scanf("%d",&l);
            char c;
            printf("y :");
            scanf(" %c",&c);
            char orientation;
            printf("Orientation :");
            scanf(" %c",&orientation);
            int *x=malloc(sizeof(int));
            int *y=malloc(sizeof(int));
            setCoord(l,c,x,y);
            ship->x=*x;
            ship->y=*y;
            ship->orientation = orientation;

            if (tryPlaceBoat(map,*x,*y,ship->orientation,ship)) {
               printMap(map);
            }else {
                printf("%d",tryPlaceBoat(map,*x,*y,orientation,ship));
                i--;
            }
        }



        printf("\nVos bateaux sont placés ! (le mode solo IA reste à coder)\n");

    } else if (choix == 2) {


        printf("\nLes deux joueurs ont placé leurs bateaux !\n");


    } else {
        printf("Choix invalide.\n");
    }


    return 0;

}