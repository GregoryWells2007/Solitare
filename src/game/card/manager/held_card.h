#pragma once
#include "engine.h"
#include "game/card/card.h"

typedef enum card_area {
    stack, 
    row1, row2, row3, row4, row5, row6, row7, 
    clubs_pile, spades_pile, hearts_pile, diamonds_pile,
    no_area
} card_area;

typedef struct held_card_data {
    card_area held_card_area;
    vector2 card_held_offset;
    card* held_card;

    int other_held_cards_count;
    card** other_held_cards;
} held_card_data;