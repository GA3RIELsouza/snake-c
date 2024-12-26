#ifndef BODY_H
#define BODY_H

#include <stdbool.h>

#include "coordinates.h"

typedef struct Body {
    Coordinates coordinates;
    Coordinates oldCoordinates;
    struct Body *son;
} Body;

void initBody(Body *body, Coordinates coordinates);

void moveBody(Body *body, Coordinates coordinates);

bool isBodyInCoordinates(Body *body, Coordinates coordinates);

void growBody(Body *body);

Body *getTail(Body *body);

#endif
