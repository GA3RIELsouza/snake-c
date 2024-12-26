#include "../include/food.h"

#include "../include/consts.h"

void randomizeFood(Food* food) {
    srand(time(NULL));

    initCoordinates(&(food->coordinates),
        (short int)(rand() % mapLength),
        (short int)(rand() % mapLength));
}

bool isFoodInCoordinates(Food* food, Coordinates coordinates) {
    return compareCoordinates(food->coordinates, coordinates);
}
