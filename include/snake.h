#ifndef SNAKE_H
#define SNAKE_H

#include "body.h"
#include "direction.h"

typedef struct {
    Body head;
    short int length;
} Snake;

void init_snake(Snake *snake, Coordinates coordinates);

void move_snake(Snake *snake, Direction direction);

void grow_snake(Snake *snake);

#endif
