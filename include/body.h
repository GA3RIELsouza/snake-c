#ifndef BODY_H
#define BODY_H

#include "coordinates.h"

typedef struct Body {
    Coordinates coordinates;
    Coordinates oldCoordinates;
    struct Body *son;
} Body;

void init_body(Body *body, Coordinates coordinates);

void move_body(Body *body, Coordinates coordinates);

bool is_body_in_coordinates(Body *body, Coordinates coordinates);

void grow_body(Body *body);

Body *get_tail(Body *body);

#endif
