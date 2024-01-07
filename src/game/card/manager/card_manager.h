#pragma once
#include "engine.h"
#include "game/card/hover/card_hover.h"
#include "game/card/card.h"
#include "game/card/renderer/card_renderer.h"
#include "game/board/board.h"

typedef enum card_area {
    stack, row1, row2, row3, row4, row5, row6, row7
} card_area;

typedef struct held_card_data {
    card_area held_card_area;
    card* held_card;
} held_card_data;

typedef struct card_manager {
    card** cards;
    
    card_hover* hover;
    card_renderer* renderer;

    vector2 card_held_offset;
    bool card_is_currently_held;

    board* loaded_board;

    card** row_1_cards;
    card** row_2_cards;
    card** row_3_cards;
    card** row_4_cards;
    card** row_5_cards;
    card** row_6_cards;
    card** row_7_cards;

    card** card_stack_cards;

    card* card_stack_show_1;
    card* card_stack_show_2;
    card** rest_of_cards;
    int cards_in_third_stack;

    // card* spades_stack;
    // card* clubs_stack;

} card_manager;

void hold_card(card* manager);

void init_card_manager(card_manager* manager);
void create_cards(card_manager* manager);
void update_card_manager(card_manager* manager); 