#include "card_manager.h"
#include "time.h"

void card_manager_init(card_manager* manager) {
    manager->cards_in_stack = linked_list_create();
    for (int i = 0; i < 7; i++)
        manager->card_rows[i] = linked_list_create();

    int numbers[52];
    for (int k = 0; k < 52; k++) { numbers[k] = k; }

    time_t t;
    srand((unsigned)time(&t));
    for (int i = 0; i < 100; i++) {
        int i1 = (rand() % 52), i2 = (rand() % 52); 
        int n1 = numbers[i1], n2 = numbers[i2];

        numbers[i2] = n1;
        numbers[i1] = n2;
    }


    int index = 0;
    for (int i = 0; i < 7; i++) {
        for (int k = 0; k < i + 1; k++) {
            struct card_data* new_data = malloc(sizeof(struct card_data));
            new_data->flipped = false;
            new_data->number = numbers[index];

            if ((k + 1) < (i + 1)) {
                new_data->flipped = true;
            }

            linked_list_add(&manager->card_rows[i], new_data);     
            index++;
        }
    }

    for (int i = 0; i < 24; i++) {
        struct card_data* new_data = malloc(sizeof(struct card_data));
        new_data->flipped = true;
        new_data->number = numbers[index];

        linked_list_add(&manager->cards_in_stack, new_data);     
        index++;       
    }
}

void card_manager_draw_cards(card_manager* manager) {
    // draw cards in stack
    for (int i = 0; i < linked_list_size(&manager->cards_in_stack); i++) {
        struct card_data* current_card_data = (struct card_data*)linked_list_get(&manager->cards_in_stack, i);
        int number = current_card_data->number;
        if (current_card_data->flipped)
            number = 52;

        board_area* position = (board_area*)array_list_get(&manager->board->areas, 11);
        card_renderer_draw_card(manager->card_renderer, (vec2){ position->position.x, position->position.y }, number);
    }

    // draw card rows

    for (int k = 0; k < 7; k++) {
        for (int i = 0; i < linked_list_size(&manager->card_rows[k]); i++) {
            struct card_data* current_card_data = (struct card_data*)linked_list_get(&manager->card_rows[k], i);
            int number = current_card_data->number;
            if (current_card_data->flipped)
                number = 52;

            board_area* position = (board_area*)array_list_get(&manager->board->areas, 4 + k);
            card_renderer_draw_card(manager->card_renderer, (vec2){ position->position.x, position->position.y - (i * 20) }, number);
        }
    }
}