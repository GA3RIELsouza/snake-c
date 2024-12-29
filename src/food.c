#include "../include/food.h"

#include "../include/consts.h"

void randomize_food_coordinates(Food *food) {
    init_coordinates(&(food->coordinates),
        (short int)(rand() % map_length),
        (short int)(rand() % map_length));
}

bool is_food_in_coordinates(Food* food, Coordinates coordinates) {
    return compare_coordinates(food->coordinates, coordinates);
}

void move_food(Food *food, Coordinates coordinates) {
    food->coordinates = coordinates;
}
