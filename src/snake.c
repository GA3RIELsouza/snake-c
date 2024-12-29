#include "../include/snake.h"
#include "../include/consts.h"

void init_snake(Snake *snake, Coordinates coordinates) {
    init_body(&(snake->head), coordinates);
    snake->length = 1;
}

void move_snake(Snake *snake, Direction direction) {
    Coordinates newCoordinates = snake->head.coordinates;

    switch (direction) {
        case UP:
            if (snake->head.coordinates.x == 0) {
                newCoordinates.x = (map_length - 1);
            } else {
                newCoordinates.x--;
            }
            break;

        case DOWN:
            if (snake->head.coordinates.x == (map_length - 1)) {
                newCoordinates.x = 0;
            } else {
                newCoordinates.x++;
            }
            break;
        
        case LEFT:
            if (snake->head.coordinates.y == 0) {
                newCoordinates.y = (map_length - 1);
            } else {
                newCoordinates.y--;
            }
            break;
        
        case RIGHT:
            if (snake->head.coordinates.y == (map_length - 1)) {
                newCoordinates.y = 0;
            } else {
                newCoordinates.y++;
            }
            break;
    }

    move_body(&(snake->head), newCoordinates);
}

void grow_snake(Snake *snake) {
    grow_body(&(snake->head));
    snake->length = snake->length + 1;
}
