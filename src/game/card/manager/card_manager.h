#pragma once
#include "engine.h"
#include "game/card/hover/card_hover.h"
#include "game/card/card.h"
#include "game/card/renderer/card_renderer.h"
#include "game/board/board.h"

#include "held_card.h"
#include "card_pile.h"

typedef struct card_manager {
    card** cards;
    
    card_hover* hover;
    card_renderer* renderer;

    held_card_data* held_card;

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