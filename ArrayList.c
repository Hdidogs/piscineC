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
} Map;

typedef struct {
    Map *structs;
} ArrayList;

int main(void) {
}

