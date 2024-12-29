#ifndef FOOD_H
#define FOOD_H

#include <stdlib.h>
#include <time.h>

#include "coordinates.h"
#include "snake.h"

typedef struct {
    Coordinates coordinates;
} Food;

void randomize_food_coordinates(Food *food);

bool is_food_in_coordinates(Food *food, Coordinates coordinates);

void move_food(Food *food, Coordinates coordinates);

#endif
