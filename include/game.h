#ifndef GAME_H
#define GAME_H

#include <windows.h>

#include "food.h"
#include "snake.h"
#include "direction.h"

const int normal_movement_beep_frequency = 400;
const int eating_food_beep_frequency = 500;

Food food;
Snake snake;
Direction snake_direction;
Direction last_snake_direction;

int main(int argc, char **argv);

void game_loop(HANDLE *keys_thread);

DWORD WINAPI render_map(LPVOID lpParam);

DWORD WINAPI beep(LPVOID lpFrequency);

DWORD WINAPI check_keys_pressed(LPVOID lpParam);

void defeat(HANDLE *keys_thread);

void victory(HANDLE *keys_thread);

#endif
