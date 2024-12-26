#ifndef FOOD_H
#define FOOD_H

#include <stdlib.h>
#include <time.h>

#include "coordinates.h"
#include "snake.h"

typedef struct {
    Coordinates coordinates;
} Food;

void randomizeFood(Food* food);

bool isFoodInCoordinates(Food* food, Coordinates coordinates);

#endif
