#include "../include/snake.h"
#include "../include/consts.h"

void initSnake(Snake* snake, Coordinates coordinates) {
    initBody(&(snake->head), coordinates);
    snake->length = 1;
}

void moveSnake(Snake* snake, Direction direction) {
    Coordinates newCoordinates = snake->head.coordinates;

    switch (direction) {
        case UP:
            if (snake->head.coordinates.x == 0) {
                newCoordinates.x = (mapLength - 1);
            } else {
                newCoordinates.x--;
            }
            break;

        case DOWN:
            if (snake->head.coordinates.x == (mapLength - 1)) {
                newCoordinates.x = 0;
            } else {
                newCoordinates.x++;
            }
            break;
        
        case LEFT:
            if (snake->head.coordinates.y == 0) {
                newCoordinates.y = (mapLength - 1);
            } else {
                newCoordinates.y--;
            }
            break;
        
        case RIGHT:
            if (snake->head.coordinates.y == (mapLength - 1)) {
                newCoordinates.y = 0;
            } else {
                newCoordinates.y++;
            }
            break;
    }

    moveBody(&(snake->head), newCoordinates);
}

void growSnake(Snake* snake) {
    growBody(&(snake->head));
    snake->length = snake->length + 1;
}
