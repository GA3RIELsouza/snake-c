#ifndef COORDINATES_H
#define COORDINATES_H

#include <stdbool.h>

typedef struct {
    short int x;
    short int y;
} Coordinates;

void initCoordinates(Coordinates *coordinates, short int x, short int y);

bool compareCoordinates(Coordinates coordinate1, Coordinates coordinate2);

#endif
