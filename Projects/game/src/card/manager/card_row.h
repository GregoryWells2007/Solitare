#pragma once
#include "game/card/card.h"
#include "held_card.h"



typedef struct card_row {
    card** cards;
    int card_count;
    int first_card_shown;
    card_area area_id;
} card_row;