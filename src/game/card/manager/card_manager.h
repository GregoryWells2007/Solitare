#pragma once
#include "engine.h"
#include "game/card/hover/card_hover.h"
#include "game/card/card.h"
#include "game/card/renderer/card_renderer.h"
#include "game/board/board.h"

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
} card_manager;

void init_card_manager(card_manager* manager);
void create_cards(card_manager* manager);
void update_card_manager(card_manager* manager); 