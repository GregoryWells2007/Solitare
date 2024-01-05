#pragma once
#include "engine.h"
#include "game/card/hover/card_hover.h"
#include "game/card/card.h"
#include "game/card/renderer/card_renderer.h"

typedef struct card_manager {
    card** cards;
    
    card_hover* hover;
    card_renderer* renderer;

    vector2 card_held_offset;
    bool card_is_currently_held;
} card_manager;

void init_card_manager(card_manager* manager);
void create_cards(card_manager* manager);
void update_card_manager(card_manager* manager); 