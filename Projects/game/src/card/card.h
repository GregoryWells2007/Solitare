#pragma once
#include "engine.h"
#include <stdbool.h>

typedef enum card_face {
    clubs = 0, spades = 1, hearts = 2, diamonds = 3
} card_face;

typedef enum card_value {
    one = 0, two = 1, three = 2, four = 3, five = 4, six = 5, seven = 6, eight = 7, nine = 8, ten = 9,
    jack = 10, queen = 11, king = 12
} card_value;

typedef struct card_data {
    card_value value;
    card_face type;
} card_data;

typedef struct card {
    card_data data;
    vector2 position;
    int scale;

    bool is_moveable;

    bool flipped;

    bool held;
    bool mouse_over;
} card;

int card_data_to_number(card_data data);