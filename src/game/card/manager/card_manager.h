#pragma once
#include "engine.h"
#include "game/card/hover/card_hover.h"
#include "game/card/card.h"
#include "game/card/renderer/card_renderer.h"
#include "game/board/board.h"

#include "held_card.h"
#include "card_pile.h"

#include "card_row.h"

typedef struct card_manager {
    card** cards;
    
    card_hover* hover;
    card_renderer* renderer;

    held_card_data* held_card;

    board* loaded_board;

    card_row* row_1;
    card_row* row_2;
    card_row* row_3;
    card_row* row_4;
    card_row* row_5;
    card_row* row_6;
    card_row* row_7;

    card** card_stack_cards;

    card* card_stack_show_1;
    card* card_stack_show_2;
    card** rest_of_cards;
    int cards_in_third_stack;
    int max_cards_in_stack;
    int cards_in_stack;

    card_pile clubs_pile;
    card_pile spades_pile;
    card_pile hearts_pile;
    card_pile diamonds_pile;

} card_manager;

void hold_card(card* manager);

void create_piles(card_manager* manager);

void init_card_manager(card_manager* manager);
void create_cards(card_manager* manager);
void update_card_manager(card_manager* manager); 

void cleanup_card_manager(card_manager* manager);