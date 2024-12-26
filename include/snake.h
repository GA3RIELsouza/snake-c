#ifndef SNAKE_H
#define SNAKE_H

#include <stdbool.h>

#include "body.h"
#include "direction.h"

typedef struct {
    Body head;
    short int length;
} Snake;

void initSnake(Snake *snake, Coordinates coordinates);

void moveSnake(Snake *snake, Direction direction);

void growSnake(Snake *snake);

#endif
