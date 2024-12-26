#include <stdio.h>
#include <windows.h>
#include <pthread.h>

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

	pthread_t keysThread;
	pthread_create(&keysThread, NULL, checkKeysPressed, NULL);

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

	pthread_t mapThread;
	pthread_create(&mapThread, NULL, renderMap, NULL);

	bool snakeIsEatingFood = isFoodInCoordinates(&food, snake.head.coordinates);

	pthread_t beepThread;

	if (snakeIsEatingFood) {
		growSnake(&snake);

		pthread_create(&beepThread, NULL, beep, (void *)&eatingFoodFrequency);

		for (int i = 0; isBodyInCoordinates(&(snake.head), food.coordinates); i++) {
			if (i % 5 == 0) {
				moveFood(&food, getTail(&(snake.head))->coordinates);
			} else {
				randomizeFood(&food);
			}
		}
	} else {
		pthread_create(&beepThread, NULL, beep, (void *)&normalMovementFrequency);
	}

	Sleep(millisBetweenMovements);

	pthread_join(mapThread, NULL);
	pthread_join(beepThread, NULL);

	gameLoop();
}

void *renderMap() {
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

void *beep(void *frequencyPointer) {
	int *frequency = (int *)frequencyPointer;

	Beep(*frequency, movementSoundMillis);
}

void *checkKeysPressed() {
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
	checkKeysPressed();
}

void defeat() {
	system("cls");
    printf("You lose!\n");

	Beep(250, 400);
	Beep(200, 500);
	Beep(150, 1000);

    exit(0);
}

void victory() {
	system("cls");
    printf("You win!\n");

	Beep(300, 300);
	Beep(400, 200);
	Beep(500, 1000);

    exit(0);
}
