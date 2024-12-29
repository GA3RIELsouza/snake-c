#include <stdio.h>
#include <stdlib.h>

#include "../include/body.h"

void init_body(Body *body, Coordinates coordinates) {
    body->coordinates = coordinates;
    body->son = NULL;
}

void move_body(Body *body, Coordinates coordinates) {
    body->oldCoordinates = body->coordinates;
    body->coordinates = coordinates;

    if (body->son != NULL) {
        move_body(body->son, body->oldCoordinates);
    }
}

bool is_body_in_coordinates(Body *body, Coordinates coordinates) {
    if (compare_coordinates(body->coordinates, coordinates)) {
        return true;
    }

    if (body->son != NULL) {
        return is_body_in_coordinates(body->son, coordinates);
    }

    return false;
}

void grow_body(Body *body) {
    if (body->son == NULL) {
        body->son = (Body*)malloc(sizeof(Body));
        init_body(body->son, body->coordinates);
    } else {
        grow_body(body->son);
    }
}

Body *get_tail(Body *body) {
    if (body->son != NULL) {
        get_tail(body->son);
    }

    return body;
}
