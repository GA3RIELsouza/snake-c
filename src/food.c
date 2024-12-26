#include "../include/food.h"

#include "../include/consts.h"

void randomizeFood(Food *food) {
    initCoordinates(&(food->coordinates),
        (short int)(rand() % mapLength),
        (short int)(rand() % mapLength));
}

bool isFoodInCoordinates(Food* food, Coordinates coordinates) {
    return compareCoordinates(food->coordinates, coordinates);
}

void moveFood(Food *food, Coordinates coordinates) {
    food->coordinates = coordinates;
}
