#include "card_manager.h"

void create_cards(card_manager* manager) {
    for (int x = 0; x < 4; x++) {
        for (int y = 0; y < 13; y++) {
            card_data new_card_data = {};
            
            new_card_data.type = x;
            new_card_data.value = y;

            card* new_card = malloc(sizeof(card));
            new_card->data = new_card_data;
            new_card->position = (vector2){ (y * 95.0f) - 550.0f, (x * -145.0f) + 240.0f };
            new_card->scale = 40.0f;
            new_card->mouse_over = 0;
            linked_list_add(&manager->cards, (void*)(new_card));
        }
    }
}

void update_card_manager(card_manager* manager) {
    for (int i = 0; i < linked_list_size(&manager->cards); i++) {
        card* current_card = linked_list_get(&manager->cards, i);
        current_card->mouse_over = 0;
        test_card_hover(manager->hover, current_card);
        draw_card(manager->renderer, current_card);
    }
}