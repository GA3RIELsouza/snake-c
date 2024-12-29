#include <stdio.h>

#include "../include/coordinates.h"
#include "../include/game.h"
#include "../include/consts.h"
#include "../include/food.h"

int main() {
	system("title Snake");
	system("color 0f");

	srand(time(NULL));

    lastDirection = RIGHT;

    Coordinates startingCoordinates;
	initCoordinates(&startingCoordinates, 0, 0);

    initSnake(&snake, startingCoordinates);
	randomizeFood(&food);

	HANDLE keysThread = CreateThread(NULL, 0, checkKeysPressed, NULL, 0, NULL);

    gameLoop();
}

void gameLoop() {
	moveSnake(&snake, lastDirection);

	bool snakeIsBitingItself = (snake.length >= 5)
		&& isBodyInCoordinates(snake.head.son, snake.head.coordinates);

	if (snakeIsBitingItself) {
		defeat();
	} else if (snake.length == mapLength * mapLength) {
		victory();
	}

	HANDLE mapThread = CreateThread(NULL, 0, renderMap, NULL, 0, NULL);

	bool snakeIsEatingFood = isFoodInCoordinates(&food, snake.head.coordinates);

	HANDLE beepThread;

	if (snakeIsEatingFood) {
		growSnake(&snake);

		beepThread = CreateThread(NULL, 0, beep, (LPVOID)&eatingFoodFrequency, 0, NULL);

		for (int i = 0; isBodyInCoordinates(&(snake.head), food.coordinates); i++) {
			if (i % 5 == 0) {
				moveFood(&food, getTail(&(snake.head))->coordinates);
			} else {
				randomizeFood(&food);
			}
		}
	} else {
		beepThread = CreateThread(NULL, 0, beep, (LPVOID)&normalMovementFrequency, 0, NULL);
	}

	Sleep(millisBetweenMovements);

	WaitForSingleObject(mapThread, INFINITE);
    WaitForSingleObject(beepThread, INFINITE);

    CloseHandle(mapThread);
    CloseHandle(beepThread);

	gameLoop();
}

DWORD WINAPI renderMap(LPVOID lpParam) {
	Coordinates currentCoordinates;

	system("cls");
    for (int x = 0; x < mapLength; x++) {
        for (int y = 0; y < mapLength; y++) {
			initCoordinates(&currentCoordinates, x, y);

			if (compareCoordinates(snake.head.coordinates, currentCoordinates)) {
				printf("O ");
			} else if (isBodyInCoordinates(&(snake.head), currentCoordinates)) {
				printf("o ");
			} else if (isFoodInCoordinates(&food, currentCoordinates)) {
				printf("x ");
			} else {
				printf(". ");
			}
        }
		printf("\n");
    }

	printf("\nLength: %d", snake.length);
}

DWORD WINAPI beep(LPVOID lpFrequency) {
	int *frequency = (int *)lpFrequency;

	Beep(*frequency, movementSoundMillis);
}

DWORD WINAPI checkKeysPressed(LPVOID lpParam) {
	if ((GetAsyncKeyState(VK_UP) & 0x8000) && lastDirection != DOWN) {
		lastDirection = UP;
	}

	if ((GetAsyncKeyState(VK_DOWN) & 0x8000) && lastDirection != UP) {
		lastDirection = DOWN;
	}

	if ((GetAsyncKeyState(VK_LEFT) & 0x8000) && lastDirection != RIGHT) {
		lastDirection = LEFT;
	}

	if ((GetAsyncKeyState(VK_RIGHT) & 0x8000) && lastDirection != LEFT) {
		lastDirection = RIGHT;
	}

	Sleep(10);
	checkKeysPressed(NULL);
}

void defeat() {
	system("cls");
	system("color 04");
    printf("You lose!\n\nYour length: %d\n\n", snake.length);

	Beep(250, 400);
	Beep(200, 500);
	Beep(150, 1000);

	system("pause");

    exit(0);
}

void victory() {
	system("cls");
	system("color 0a");
    printf("You win!\n\nYour length: %d (the whole map!)\n\n", snake.length);

	Beep(300, 300);
	Beep(400, 200);
	Beep(500, 1000);

	system("pause");

    exit(0);
}
