#ifndef GAME_H
#define GAME_H

#include "food.h"
#include "snake.h"
#include "direction.h"

Food food;
Snake snake;
Direction lastDirection;

int main();

int gameLoop();

void renderMap();

Direction checkKeyPressed();

int defeat();

int victory();

#endif
