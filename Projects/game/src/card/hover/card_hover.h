#pragma once
#include "src/card/card.h"
#include "engine.h"

typedef struct card_hover {
    input_manager* input_manager;
} card_hover;

bool test_card_hover(card_hover* hover, card* card_to_test);
bool in_board_area(card_hover* hover, vector2 board_area);
bool test_card_in_area(card_hover* hover, card* card_to_test, vector2 board_area);
bool test_card_collision(card_hover* hover, card* card1, card* card2);