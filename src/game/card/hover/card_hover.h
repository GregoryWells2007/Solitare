#pragma once
#include "game/card/card.h"
#include "engine.h"

typedef struct card_hover {
    input_manager* input_manager;
} card_hover;

bool test_card_hover(card_hover* hover, card* card_to_test);