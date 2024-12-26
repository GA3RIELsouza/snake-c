#include <stdio.h>
#include <windows.h>

#include "../include/coordinates.h"
#include "../include/game.h"
#include "../include/consts.h"
#include "../include/food.h"

int main() {
    lastDirection = RIGHT;

    Coordinates startingCoordinates;
    startingCoordinates.x = 0;
    startingCoordinates.y = 0;

    initSnake(&snake, startingCoordinates);
	randomizeFood(&food);

    return gameLoop();
}

int gameLoop() {
	lastDirection = checkKeyPressed();
	moveSnake(&snake, lastDirection);

	renderMap();

	bool snakeIsBitingItself = false;

	if (snake.length >= 5) {
		snakeIsBitingItself = isBodyInCoordinates(snake.head.son, snake.head.coordinates);
	}

	if (snakeIsBitingItself) {
		return defeat();
	}

	bool snakeIsEatingFood = isFoodInCoordinates(&food, snake.head.coordinates);

	if (snakeIsEatingFood) {
		growSnake(&snake);

		Beep(500, movementSoundMillis);

		do {
			randomizeFood(&food);
		} while (isBodyInCoordinates(&(snake.head), food.coordinates));
	} else {
		Beep(400, movementSoundMillis);
	}

	if (snake.length == mapLength * mapLength) {
		return victory();
	}

	Sleep(millisBetweenMovements - movementSoundMillis);
	system("cls");
	return gameLoop();
}

void renderMap() {
	Coordinates coordinates;

    for (int x = 0; x < mapLength; x++) {
        for (int y = 0; y < mapLength; y++) {
			initCoordinates(&coordinates, x, y);

			if (isBodyInCoordinates(&(snake.head), coordinates)) {
				printf("O ");
			} else if (isFoodInCoordinates(&food, coordinates)) {
				printf("x ");
			} else {
				printf(". ");
			}
        }
        printf("\n");
    }
}

Direction checkKeyPressed() {
	if ((GetAsyncKeyState(VK_UP) & 0x8000) && lastDirection != DOWN) {
		return UP;
	}

	if ((GetAsyncKeyState(VK_DOWN) & 0x8000) && lastDirection != UP) {
		return DOWN;
	}

	if ((GetAsyncKeyState(VK_LEFT) & 0x8000) && lastDirection != RIGHT) {
		return LEFT;
	}

	if ((GetAsyncKeyState(VK_RIGHT) & 0x8000) && lastDirection != LEFT) {
		return RIGHT;
	}

	return lastDirection;
}

int defeat() {
	system("cls");
    printf("You lose!\n");

	Beep(250, 400);
	Beep(200, 500);
	Beep(150, 1000);

    return 1;
}

int victory() {
	system("cls");
    printf("You win!\n");

	Beep(300, 300);
	Beep(400, 200);
	Beep(500, 1000);

    return 0;
}
