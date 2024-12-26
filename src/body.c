#include <stdio.h>
#include <stdlib.h>

#include "../include/body.h"

void initBody(Body* body, Coordinates coordinates) {
    body->coordinates = coordinates;
    body->son = NULL;
}

void moveBody(Body* body, Coordinates coordinates) {
    body->oldCoordinates = body->coordinates;
    body->coordinates = coordinates;

    if (body->son != NULL) {
        moveBody(body->son, body->oldCoordinates);
    }
}

bool isBodyInCoordinates(Body* body, Coordinates coordinates) {
    if (compareCoordinates(body->coordinates, coordinates)) {
        return true;
    }

    if (body->son != NULL) {
        return isBodyInCoordinates(body->son, coordinates);
    }

    return false;
}

void growBody(Body* body) {
    if (body->son == NULL) {
        body->son = (Body*)malloc(sizeof(Body));
        initBody(body->son, body->coordinates);
    } else {
        growBody(body->son);
    }
}
