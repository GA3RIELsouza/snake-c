#ifndef GAME_H
#define GAME_H

#include "food.h"
#include "snake.h"
#include "direction.h"

const int normalMovementFrequency = 400;
const int eatingFoodFrequency = 500;

Food food;
Snake snake;
Direction lastDirection;

int main();

void gameLoop();

void *renderMap();

void *beep(void *frequencyPointer);

void *logicRandomizeFood();

void *checkKeysPressed();

void defeat();

void victory();

#endif
