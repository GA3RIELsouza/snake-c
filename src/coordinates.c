#include "../include/coordinates.h"

void init_coordinates(Coordinates *coordinates, short int x, short int y) {
    coordinates->x = x;
    coordinates->y = y;
}

bool compare_coordinates(Coordinates coordinate1, Coordinates coordinate2) {
    return coordinate1.x == coordinate2.x && coordinate1.y == coordinate2.y;
}
