#include "card_manager.h"
#include <stdio.h> 
#include <stdlib.h> 
#include <time.h> 
#include "math.h"

void init_card_manager(card_manager* manager) {
    manager->held_card = malloc(sizeof(held_card_data));
    manager->held_card->held_card = NULL;
    manager->held_card->held_card_area = no_area;
    manager->held_card->card_held_offset = (vector2){ 0, 0 };
}

void create_piles(card_manager* manager) {
    manager->clubs_pile = (card_pile){};
    manager->clubs_pile.cards = malloc(sizeof(card) * 13);
    for (int i = 0; i < 13; i++)
        manager->clubs_pile.cards[i] = NULL;
    manager->clubs_pile.face = clubs;
    manager->clubs_pile.area = manager->loaded_board->board_clubs_position;

    // i need to setup the other boards later
    // manager->spades_pile = {};
    // manager->hearts_pile = {};
    // manager->diamonds_pile = {};
}

void move_card_to_top(card_manager* manager, card* card_to_top) {
    int index = 0;
    for (int i = 0; i < 52; i++) {
        if (card_data_to_number(manager->cards[i]->data) == card_data_to_number(card_to_top->data)) {
            index = i;
            break;
        }
    }

    if (index == 0)
        return;

    card* card_to_copy = manager->cards[index];

    for (int i = index; i >= 0; i--)
        manager->cards[i] = manager->cards[i - 1];

    manager->cards[0] = card_to_copy;
}   

void assign_cards_to_rows(card_manager* manager) {
    int* numbersLeft = malloc(sizeof(int) * 52);
    for (int k = 0; k < 52; k++)
        numbersLeft[k] = k;

    int* numbers_to_use_list = malloc(sizeof(int) * 52);
    for (int k = 0; k < 52; k++) {
        srand((time(NULL))); 
        int value = rand() % (52 - k); 
        numbers_to_use_list[k] = numbersLeft[value];

        numbersLeft[value] = -1;
        for (int g = value; g < 51; g++) {
            numbersLeft[g] = numbersLeft[g + 1]; 
        }
    }
    free(numbersLeft);

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
    manager->cards_in_third_stack = 0;
    manager->rest_of_cards = malloc(sizeof(card) * 22);
    manager->card_stack_cards = malloc(sizeof(card) * 24);
    for (int i = 0; i < 24; i++) {
        manager->card_stack_cards[i] = manager->cards[numbers_to_use_list[i + 28]];
    }

    free(numbers_to_use_list);
}

void set_card_row_positions(card_manager* manager) {
    for (int i = 0; i < 13; i++) {
        if (manager->row_1_cards[i] != NULL) {
            manager->row_1_cards[i]->position = manager->loaded_board->board_cards_position_1;
            manager->row_1_cards[i]->position.y -= (i * 20);

            if (manager->row_1_cards[i + 1] == NULL) {
                manager->row_1_cards[i]->flipped = false;
                manager->row_1_cards[i]->is_moveable = true;
            }
            else
                manager->row_1_cards[i]->flipped = true;
            move_card_to_top(manager, manager->row_1_cards[i]);
        }
        if (manager->row_2_cards[i] != NULL) {
            manager->row_2_cards[i]->position = manager->loaded_board->board_cards_position_2;
            manager->row_2_cards[i]->position.y -= (i * 20);

            if (manager->row_2_cards[i + 1] == NULL) {
                manager->row_2_cards[i]->flipped = false;
                manager->row_2_cards[i]->is_moveable = true;
            }
            else
                manager->row_2_cards[i]->flipped = true;

            move_card_to_top(manager, manager->row_2_cards[i]);
        }
        if (manager->row_3_cards[i] != NULL) {
            manager->row_3_cards[i]->position = manager->loaded_board->board_cards_position_3;
            manager->row_3_cards[i]->position.y -= (i * 20);

            if (manager->row_3_cards[i + 1] == NULL) {
                manager->row_3_cards[i]->flipped = false;
                manager->row_3_cards[i]->is_moveable = true;
            }
            else
                manager->row_3_cards[i]->flipped = true;
            
            move_card_to_top(manager, manager->row_3_cards[i]);
        }
        if (manager->row_4_cards[i] != NULL) {
            manager->row_4_cards[i]->position = manager->loaded_board->board_cards_position_4;
            manager->row_4_cards[i]->position.y -= (i * 20);

            if (manager->row_4_cards[i + 1] == NULL) {
                manager->row_4_cards[i]->flipped = false;
                manager->row_4_cards[i]->is_moveable = true;
            }
            else
                manager->row_4_cards[i]->flipped = true;

            move_card_to_top(manager, manager->row_4_cards[i]);
        }
        if (manager->row_5_cards[i] != NULL) {
            manager->row_5_cards[i]->position = manager->loaded_board->board_cards_position_5;
            manager->row_5_cards[i]->position.y -= (i * 20);

            if (manager->row_5_cards[i + 1] == NULL) {
                manager->row_5_cards[i]->flipped = false;
                manager->row_5_cards[i]->is_moveable = true;
            }
            else
                manager->row_5_cards[i]->flipped = true;

            move_card_to_top(manager, manager->row_5_cards[i]);
        }
        if (manager->row_6_cards[i] != NULL) {
            manager->row_6_cards[i]->position = manager->loaded_board->board_cards_position_6;
            manager->row_6_cards[i]->position.y -= (i * 20);

            if (manager->row_6_cards[i + 1] == NULL) {
                manager->row_6_cards[i]->flipped = false;
                manager->row_6_cards[i]->is_moveable = true;
            }
            else
                manager->row_6_cards[i]->flipped = true;

            move_card_to_top(manager, manager->row_6_cards[i]);
        }
        if (manager->row_7_cards[i] != NULL) {
            manager->row_7_cards[i]->position = manager->loaded_board->board_cards_position_7;
            manager->row_7_cards[i]->position.y -= (i * 20);

            if (manager->row_7_cards[i + 1] == NULL) {
                manager->row_7_cards[i]->flipped = false;
                manager->row_7_cards[i]->is_moveable = true;
            }
            else
                manager->row_7_cards[i]->flipped = true;

           move_card_to_top(manager, manager->row_7_cards[i]);
        }
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
            new_card->flipped = true;
            new_card->is_moveable = false;

            manager->cards[index] = new_card;
            index++;
        }
    }

    assign_cards_to_rows(manager);
    set_card_row_positions(manager);
}

void rotate_stack_array(card_manager* manager) {
    card* last_card = manager->card_stack_cards[0];
    for (int i = 0; i < 23; i++) {
        manager->card_stack_cards[i] = manager->card_stack_cards[i + 1];
    }
    manager->card_stack_cards[23] = last_card;
}

void check_stack_clicked (card_manager* manager) {
    card* first_card = manager->card_stack_cards[0];
    test_card_hover(manager->hover, first_card);

    if ((manager->hover->input_manager->mouse_clicked && first_card->mouse_over)) {
        if (manager->card_stack_show_1 == NULL) {
            manager->card_stack_show_1 = first_card;
        } else if (manager->card_stack_show_2 == NULL) {
            manager->card_stack_show_2 = manager->card_stack_show_1;
            manager->card_stack_show_1 = first_card;
        } else {
            manager->rest_of_cards[manager->cards_in_third_stack] = manager->card_stack_show_2;
            manager->card_stack_show_2 = manager->card_stack_show_1;
            manager->card_stack_show_1 = first_card;
            manager->cards_in_third_stack++;

        }

        first_card->flipped = false;
        move_card_to_top(manager, first_card);
        rotate_stack_array(manager);
    } else {
        if (manager->cards_in_third_stack == 22) {
            if (in_board_area(manager->hover, manager->loaded_board->card_stack_position) && manager->hover->input_manager->mouse_clicked) {    
                printf("resetting board\n");
                manager->card_stack_show_1 = NULL;
                manager->card_stack_show_2 = NULL;
                for (int k = 0; k < manager->cards_in_third_stack; k++) {
                    manager->rest_of_cards[k] = NULL;
                }
                manager->cards_in_third_stack = 0;
                for (int i = 0; i < 24; i++) {
                    manager->card_stack_cards[i]->flipped = true;
                }
            }
        }
    }

    first_card->mouse_over = false;
}
void position_card_stacks(card_manager* manager) {
    for (int i = 0; i < 24; i++) {
        manager->card_stack_cards[i]->position = manager->loaded_board->card_stack_position;
    }

    if (manager->card_stack_show_1 != NULL) {
        manager->card_stack_show_1->position.x = (manager->loaded_board->card_stack_position.x - 100.0f);
        manager->card_stack_show_1->is_moveable = true;
    }

    if (manager->card_stack_show_2 != NULL) {
        manager->card_stack_show_2->position.x = (manager->loaded_board->card_stack_position.x - 150.0f);
        manager->card_stack_show_2->is_moveable = false;
    }

    for (int k = 0; k < manager->cards_in_third_stack; k++) {
        manager->rest_of_cards[k]->position.x = (manager->loaded_board->card_stack_position.x - 200.0f);
        manager->rest_of_cards[k]->is_moveable = false;
    }
}

int lowest_distance(float* distances, int count) {
    float lowest_recorded_distance = INT32_MAX;
    int index = 0;

    for (int x = 0; x < count; x++) {
        if (distances[x] < lowest_recorded_distance) {
            lowest_recorded_distance = distances[x];
            index = x;
        }
    }
    return index;
}

void check_first_card_dropped(card_manager* manager) {
    if (manager->held_card->held_card_area != stack)
        return;

    card* held_card = manager->held_card->held_card;

    move_card_to_top(manager, held_card);

    float distances[4] = { 0.0f, 0.0f, 0.0f, 0.0f }; 
    distances[0] = get_distance(held_card->position, manager->loaded_board->board_spades_position); 
    distances[1] = get_distance(held_card->position, manager->loaded_board->board_clubs_position); 
    distances[2] = get_distance(held_card->position, manager->loaded_board->board_hearts_position); 
    distances[3] = get_distance(held_card->position, manager->loaded_board->board_diamonds_position); 

    int lowest_index = lowest_distance(distances, 4);

    if (lowest_index == 0) {
        if (test_card_in_area(manager->hover, held_card, manager->loaded_board->board_spades_position)) {
            //printf("droping on spades\n");
        }
    }

    if (lowest_index == 1) {
        if (test_card_in_area(manager->hover, held_card, manager->loaded_board->board_clubs_position)) {
            //printf("droping on clubs\n");
        }
    }

    if (lowest_index == 2) {
        if (test_card_in_area(manager->hover, held_card, manager->loaded_board->board_hearts_position)) {
            //printf("droping on hearts\n");
        }
    }

    if (lowest_index == 3) {
        if (test_card_in_area(manager->hover, held_card, manager->loaded_board->board_diamonds_position)) {
            //printf("droping on diamonds\n");
        }
    }

}

int get_last_index(card** cards) {
    for (int q = 0; q < 13; q++) {
        if (cards[q] == NULL)
            return q - 1;
    }
}

card** get_top_row_cards(card_manager* manager) {
    card** new_cards = malloc(sizeof(card) * 7);
    new_cards[0] = manager->row_1_cards[get_last_index(manager->row_1_cards)];
    new_cards[1] = manager->row_2_cards[get_last_index(manager->row_2_cards)];
    new_cards[2] = manager->row_3_cards[get_last_index(manager->row_3_cards)];
    new_cards[3] = manager->row_4_cards[get_last_index(manager->row_4_cards)];
    new_cards[4] = manager->row_5_cards[get_last_index(manager->row_5_cards)];
    new_cards[5] = manager->row_6_cards[get_last_index(manager->row_6_cards)];
    new_cards[6] = manager->row_7_cards[get_last_index(manager->row_7_cards)];
    return new_cards;
}

bool is_opposite_color(int type1, int type2) {
    int type_1 = -1, type_2 = -1;

    if (type1 == 0 || type1 == 1)
        type_1 = 0;
    else if (type1 == 2 || type1 == 3)
        type_1 = 1;

    if (type2 == 0 || type2 == 1)
        type_2 = 0;
    else if (type2 == 2 || type2 == 3)
        type_2 = 1;

    return type_1 != type_2;
}

void update_held_card(card_manager* manager) {
    if (manager->held_card->held_card == NULL)
        return;

    float real_mouse_x = (((manager->hover->input_manager->mouse_position.x / 1280.0f) * 2) - 1) * 640;
    float real_mouse_y = -((((manager->hover->input_manager->mouse_position.y / 720.0f) * 2) - 1) * 360);
    manager->held_card->held_card->position = (vector2){ real_mouse_x, real_mouse_y };
    manager->held_card->held_card->held = 1;

    move_card_to_top(manager, manager->held_card->held_card);

    if (!manager->hover->input_manager->mouse_down) {
        manager->held_card->held_card = NULL;
    }
}

void update_card_manager(card_manager* manager) {
    bool card_already_hovered = false;

    check_stack_clicked(manager);
    position_card_stacks(manager);
    set_card_row_positions(manager);

    for (int i = 0; i < 52; i++) {
        card* current_card = manager->cards[i];
        current_card->mouse_over = 0;
        current_card->held = 0;
        if (!card_already_hovered && manager->held_card->held_card == NULL) {
            test_card_hover(manager->hover, current_card);
            if (current_card->mouse_over)
                card_already_hovered = true;
        }

        if (!current_card->is_moveable)
            continue;
        if (current_card->flipped)
            continue;
        if (manager->held_card->held_card != NULL)
            continue;

         if (current_card->mouse_over && manager->hover->input_manager->mouse_clicked) {
            manager->held_card->held_card = current_card;
            // figure out card area later;

            float real_mouse_x = (((manager->hover->input_manager->mouse_position.x / 1280.0f) * 2) - 1) * 640;
            float real_mouse_y = -((((manager->hover->input_manager->mouse_position.y / 720.0f) * 2) - 1) * 360);

            float card_held_offset_x = real_mouse_x - current_card->position.x;
            float card_held_offset_y = real_mouse_y - current_card->position.y;
        

            manager->held_card->card_held_offset = (vector2){ card_held_offset_x, card_held_offset_y };
         }
    }

    check_first_card_dropped(manager);
    update_held_card(manager);

    // for (int k = 0; k < 52; k++) {
    //     if (!manager->cards[k]->held)
    //         continue;

    //     card* current_card = manager->cards[k];
    //     move_card_to_top(manager, current_card);

    //     card** cards_to_collide_with = get_top_row_cards(manager);
    //     float distances[7] = { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };
    //     for (int q = 0; q < 7; q++) {
    //         distances[q] = get_distance(current_card->position, cards_to_collide_with[q]->position);

    //         if (cards_to_collide_with[q] == current_card)
    //             distances[q] = INT32_MAX;

    //         if (!is_opposite_color(cards_to_collide_with[q]->data.type, current_card->data.type))
    //             distances[q] = INT32_MAX;

    //         if (cards_to_collide_with[q]->data.value != (current_card->data.value + 1))
    //             distances[q] = INT32_MAX;
    //     }

    //     printf("Distances: {%f, %f, %f, %f, %f, %f, %f}\n", 
    //         distances[0], distances[1], distances[2], distances[3], distances[4], distances[5], distances[6]);

    //     int lowest_distance_index = lowest_distance(distances, 7);
    //     if (test_card_collision(manager->hover, current_card, cards_to_collide_with[lowest_distance_index])) {
    //         printf("we can drop it here boys\n");
    //     }

    // }

    for (int i = 51; i >= 0; i--) {
        draw_card(manager->renderer, manager->cards[i]);
    }
}