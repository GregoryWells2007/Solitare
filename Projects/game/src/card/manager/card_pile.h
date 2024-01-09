#pragma once
#include "engine.h"
#include "src/card/card.h"

typedef struct card_pile {
    card** cards;
    int count;

    card_face face;

    vector2 area;
} card_pile;