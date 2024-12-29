#ifndef COORDINATES_H
#define COORDINATES_H

#include <stdbool.h>

typedef struct {
    short int x;
    short int y;
} Coordinates;

void init_coordinates(Coordinates *coordinates, short int x, short int y);

bool compare_coordinates(Coordinates coordinate1, Coordinates coordinate2);

#endif
