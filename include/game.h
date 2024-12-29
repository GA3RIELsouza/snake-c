#ifndef GAME_H
#define GAME_H

#include <windows.h>

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

DWORD WINAPI renderMap(LPVOID lpParam);

DWORD WINAPI beep(LPVOID lpFrequency);

void *logicRandomizeFood();

DWORD WINAPI checkKeysPressed(LPVOID lpParam);

void defeat();

void victory();

#endif
