#pragma once
#include "engine.h"

#include "../card_renderer/card_renderer.h"
#include "../../board/board.h"

struct card_data {
    int number;
    bool flipped;
};

typedef struct card_manager {
    linked_list cards_in_stack;
    int stack_flip_position;

    linked_list card_rows[7];

    input_manager* input; 

    board* board;
    card_renderer* card_renderer;
} card_manager;

void card_manager_init(card_manager* manager);
void card_manager_draw_cards(card_manager* manager);
void card_manager_flip_stack(card_manager* manager);
void card_manager_remove_from_stack(card_manager* manager);