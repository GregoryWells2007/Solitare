#include "card_manager.h"

void assign_cards_to_rows(card_manager* manager) {
    int* numbers_to_use_list = malloc(sizeof(int) * 52);
    for (int k = 0; k < 52; k++)
        numbers_to_use_list[k] = k;

    manager->row_1_cards = malloc(sizeof(card) * 13);
    for (int k = 1; k < 13; k++)
        manager->row_1_cards[k] = NULL;
    manager->row_1_cards[0] = manager->cards[numbers_to_use_list[0]];


    manager->row_2_cards = malloc(sizeof(card) * 13);
    for (int k = 2; k < 13; k++)
        manager->row_2_cards[k] = NULL;
    manager->row_2_cards[0] = manager->cards[numbers_to_use_list[1]];
    manager->row_2_cards[1] = manager->cards[numbers_to_use_list[2]];

    manager->row_3_cards = malloc(sizeof(card) * 13);
    for (int k = 3; k < 13; k++)
        manager->row_3_cards[k] = NULL;
    manager->row_3_cards[0] = manager->cards[numbers_to_use_list[3]];
    manager->row_3_cards[1] = manager->cards[numbers_to_use_list[4]];
    manager->row_3_cards[2] = manager->cards[numbers_to_use_list[5]];

    manager->row_4_cards = malloc(sizeof(card) * 13);
    for (int k = 4; k < 13; k++)
        manager->row_4_cards[k] = NULL;
    manager->row_4_cards[0] = manager->cards[numbers_to_use_list[6]];
    manager->row_4_cards[1] = manager->cards[numbers_to_use_list[7]];
    manager->row_4_cards[2] = manager->cards[numbers_to_use_list[8]];
    manager->row_4_cards[3] = manager->cards[numbers_to_use_list[9]];

    manager->row_5_cards = malloc(sizeof(card) * 13);
    for (int k = 5; k < 13; k++)
        manager->row_5_cards[k] = NULL;
    manager->row_5_cards[0] = manager->cards[numbers_to_use_list[10]];
    manager->row_5_cards[1] = manager->cards[numbers_to_use_list[11]];
    manager->row_5_cards[2] = manager->cards[numbers_to_use_list[12]];
    manager->row_5_cards[3] = manager->cards[numbers_to_use_list[13]];
    manager->row_5_cards[4] = manager->cards[numbers_to_use_list[14]];

    manager->row_6_cards = malloc(sizeof(card) * 13);
    for (int k = 6; k < 13; k++)
        manager->row_6_cards[k] = NULL;
    manager->row_6_cards[0] = manager->cards[numbers_to_use_list[15]];
    manager->row_6_cards[1] = manager->cards[numbers_to_use_list[16]];
    manager->row_6_cards[2] = manager->cards[numbers_to_use_list[17]];
    manager->row_6_cards[3] = manager->cards[numbers_to_use_list[18]];
    manager->row_6_cards[4] = manager->cards[numbers_to_use_list[19]];
    manager->row_6_cards[5] = manager->cards[numbers_to_use_list[20]];

    manager->row_7_cards = malloc(sizeof(card) * 13);
    for (int k = 7; k < 13; k++)
        manager->row_7_cards[k] = NULL;
    manager->row_7_cards[0] = manager->cards[numbers_to_use_list[21]];
    manager->row_7_cards[1] = manager->cards[numbers_to_use_list[22]];
    manager->row_7_cards[2] = manager->cards[numbers_to_use_list[23]];
    manager->row_7_cards[3] = manager->cards[numbers_to_use_list[24]];
    manager->row_7_cards[4] = manager->cards[numbers_to_use_list[25]];
    manager->row_7_cards[5] = manager->cards[numbers_to_use_list[26]];
    manager->row_7_cards[6] = manager->cards[numbers_to_use_list[27]];

    // assign stuff to the stack
    manager->card_stack_cards = malloc(sizeof(card) * 25);
    for (int i = 0; i < 25; i++) {
        manager->card_stack_cards[i] = manager->cards[numbers_to_use_list[i + 27]];
    }

    free(numbers_to_use_list);
}

void set_card_row_positions(card_manager* manager) {
    for (int i = 0; i < 13; i++) {
        if (manager->row_1_cards[i] != NULL)
            manager->row_1_cards[i]->position = manager->loaded_board->board_cards_position_1;
        if (manager->row_2_cards[i] != NULL)
            manager->row_2_cards[i]->position = manager->loaded_board->board_cards_position_2;
        if (manager->row_3_cards[i] != NULL)
            manager->row_3_cards[i]->position = manager->loaded_board->board_cards_position_3;
        if (manager->row_4_cards[i] != NULL)
            manager->row_4_cards[i]->position = manager->loaded_board->board_cards_position_4;
        if (manager->row_5_cards[i] != NULL)
            manager->row_5_cards[i]->position = manager->loaded_board->board_cards_position_5;
        if (manager->row_6_cards[i] != NULL)
            manager->row_6_cards[i]->position = manager->loaded_board->board_cards_position_6;
        if (manager->row_7_cards[i] != NULL)
            manager->row_7_cards[i]->position = manager->loaded_board->board_cards_position_7;
        printf("\n");
    }   

    for (int i = 0; i < 25; i++) {
        manager->card_stack_cards[i]->position = manager->loaded_board->card_stack_position;
    }
}

void create_cards(card_manager* manager) {
    manager->cards = malloc(sizeof(card) * 52);

    int index = 0;

    for (int x = 0; x < 4; x++) {
        for (int y = 0; y < 13; y++) {
            card_data new_card_data = {};
            
            new_card_data.type = x;
            new_card_data.value = y;

            card* new_card = malloc(sizeof(card));
            new_card->data = new_card_data;
            new_card->position = (vector2){ 0, 0 };
            new_card->scale = 40.0f;
            new_card->mouse_over = 0;
            new_card->held = 0;
            new_card->flipped = false;

            manager->cards[index] = new_card;
            index++;
        }
    }

    assign_cards_to_rows(manager);
    set_card_row_positions(manager);
}

void move_card_to_top(card_manager* manager, int index) {
    if (index == 0)
        return;

    card* card_to_copy = manager->cards[index];

    for (int i = index; i >= 0; i--)
        manager->cards[i] = manager->cards[i - 1];

    manager->cards[0] = card_to_copy;
}   

void update_card_manager(card_manager* manager) {
    bool card_already_hovered = false;

    for (int i = 0; i < 52; i++) {
        card* current_card = manager->cards[i];
        current_card->mouse_over = 0;
        if (!card_already_hovered && !manager->card_is_currently_held) {
            test_card_hover(manager->hover, current_card);
            if (current_card->mouse_over)
                card_already_hovered = true;
        }

        if (!manager->card_is_currently_held) {
            current_card->held = 0;
            if (current_card->mouse_over && manager->hover->input_manager->mouse_down) {
                current_card->held = 1;
                manager->card_is_currently_held = true;

                float real_mouse_x = (((manager->hover->input_manager->mouse_position.x / 1280.0f) * 2) - 1) * 640;
                float real_mouse_y = -((((manager->hover->input_manager->mouse_position.y / 720.0f) * 2) - 1) * 360);

                manager->card_held_offset.x = real_mouse_x - current_card->position.x;
                manager->card_held_offset.y = real_mouse_y - current_card->position.y;

                move_card_to_top(manager, i);
            }
        } else if (current_card->held) {
            if (manager->hover->input_manager->mouse_down) {
                float real_mouse_x = (((manager->hover->input_manager->mouse_position.x / 1280.0f) * 2) - 1) * 640;
                float real_mouse_y = -((((manager->hover->input_manager->mouse_position.y / 720.0f) * 2) - 1) * 360);

                real_mouse_x -= manager->card_held_offset.x;
                real_mouse_y -= manager->card_held_offset.y;

                current_card->position.x = real_mouse_x;
                current_card->position.y = real_mouse_y;
            } else {
                current_card->held = 0;
                manager->card_is_currently_held = false;
            }
        }
    }

    for (int i = 51; i >= 0; i--) {
        draw_card(manager->renderer, manager->cards[i]);
    }
}