#include <stdio.h>

#include "../include/coordinates.h"
#include "../include/game.h"
#include "../include/consts.h"
#include "../include/food.h"

int main(int argc, char **argv) {
	system("title Snake");
	system("color 0f");

	srand(time(NULL));

	snake_direction = RIGHT;
    last_snake_direction = RIGHT;

    Coordinates snake_starting_coordinates;
	init_coordinates(&snake_starting_coordinates, 1, 1);

    init_snake(&snake, snake_starting_coordinates);
	randomize_food_coordinates(&food);

	HANDLE keys_thread = CreateThread(NULL, 0, check_keys_pressed, (LPVOID)argv[0], 0, NULL);

    game_loop(keys_thread);
}

void game_loop(HANDLE *keys_thread) {
	while(true) {
		move_snake(&snake, snake_direction);

		bool snakeIsBitingItself = (snake.length >= 2)
			&& is_body_in_coordinates(snake.head.son, snake.head.coordinates);

		if (snakeIsBitingItself) {
			defeat(keys_thread);
			break;
		} else if (snake.length == map_length * map_length) {
			victory(keys_thread);
			break;
		}

		HANDLE map_thread = CreateThread(NULL, 0, render_map, NULL, 0, NULL);

		bool snake_is_eating_food = is_food_in_coordinates(&food, snake.head.coordinates);

		HANDLE beep_thread;

		if (snake_is_eating_food) {
			grow_snake(&snake);

			beep_thread = CreateThread(NULL, 0, beep, (LPVOID)&eating_food_beep_frequency, 0, NULL);

			for (int i = 0; is_body_in_coordinates(&(snake.head), food.coordinates); i++) {
				if (i % 5 == 0) {
					move_food(&food, get_tail(&(snake.head))->coordinates);
				} else {
					randomize_food_coordinates(&food);
				}
			}
		} else {
			beep_thread = CreateThread(NULL, 0, beep, (LPVOID)&normal_movement_beep_frequency, 0, NULL);
		}

		Sleep(millis_between_movements);

		WaitForSingleObject(map_thread, INFINITE);
		WaitForSingleObject(beep_thread, INFINITE);

		CloseHandle(map_thread);
		CloseHandle(beep_thread);

		last_snake_direction = snake_direction;
	}
}

DWORD WINAPI render_map(LPVOID lpParam) {
	char *map = (char *)malloc(((map_length * map_length) * 2) * sizeof(char));
	Coordinates current_coordinates;
	int map_index = 0;

	if (map == NULL) {
		exit(1);
	}

	system("cls");
    for (int x = 0; x < map_length; x++) {
        for (int y = 0; y < map_length; y++) {
			init_coordinates(&current_coordinates, x, y);

			if (compare_coordinates(snake.head.coordinates, current_coordinates)) {
				map[map_index++] = 'O';
			} else if (is_body_in_coordinates(&(snake.head), current_coordinates)) {
				map[map_index++] = 'o';
			} else if (is_food_in_coordinates(&food, current_coordinates)) {
				map[map_index++] = 'x';
			} else {
				map[map_index++] = '.';
			}
			if (y < (map_length - 1)) {
				map[map_index++] = ' ';
			}
        }
		if (x < (map_length - 1)) {
			map[map_index++] = '\n';
		}
    }

	map[map_index] = '\0';

	printf("%s\n\nLength: %d\n\nE = Exit\nR = Restart", map, snake.length);

	free(map);
}

DWORD WINAPI beep(LPVOID lpFrequency) {
	int *frequency = (int *)lpFrequency;

	Beep(*frequency, movement_beep_millis);
}

DWORD WINAPI check_keys_pressed(LPVOID lpParam) {
	while(true) {
		if (GetAsyncKeyState('E') & 0x8000) {
			exit(0);
		} else if (GetAsyncKeyState('R') & 0x8000) {
			char command[1024];

			snprintf(command, sizeof(command), "start %s", (char *)lpParam);

			system(command);

			exit(0);
		} else if ((GetAsyncKeyState(VK_UP) & 0x8000) && last_snake_direction != DOWN) {
			snake_direction = UP;
		} else if ((GetAsyncKeyState(VK_DOWN) & 0x8000) && last_snake_direction != UP) {
			snake_direction = DOWN;
		} else if ((GetAsyncKeyState(VK_LEFT) & 0x8000) && last_snake_direction != RIGHT) {
			snake_direction = LEFT;
		} else if ((GetAsyncKeyState(VK_RIGHT) & 0x8000) && last_snake_direction != LEFT) {
			snake_direction = RIGHT;
		}

		Sleep(10);
	}
}

void defeat(HANDLE *keys_thread) {
	system("cls");
	system("color 04");
    printf("You lose!\n\nYour length: %d\n\nE = Exit\nR = Restart", snake.length);

	Beep(250, 400);
	Beep(200, 500);
	Beep(150, 1000);

	WaitForSingleObject(keys_thread, INFINITE);
}

void victory(HANDLE *keys_thread) {
	system("cls");
	system("color 0a");
    printf("You win!\n\nYour length: %d (the whole map!)\n\nE = Exit\nR = Restart", snake.length);

	Beep(300, 300);
	Beep(400, 200);
	Beep(500, 1000);

	WaitForSingleObject(keys_thread, INFINITE);
}
