#include "card_manager.h"
#include <stdio.h> 
#include <stdlib.h> 
#include <time.h> 
#include "math.h"

//#define LOG_DATA

void init_card_manager(card_manager* manager) {
    manager->held_card = malloc(sizeof(held_card_data));
    manager->held_card->held_card = NULL;
    manager->held_card->held_card_area = no_area;
    manager->held_card->card_held_offset = (vector2){ 0, 0 };
    manager->held_card->other_held_cards_count = 0;
    manager->held_card->other_held_cards = malloc(sizeof(card) * 13);
}
void create_piles(card_manager* manager) {
    manager->clubs_pile = (card_pile){};
    manager->clubs_pile.cards = malloc(sizeof(card) * 13);
    for (int i = 0; i < 13; i++)
        manager->clubs_pile.cards[i] = NULL;
    manager->clubs_pile.face = clubs;
    manager->clubs_pile.count = 0;
    manager->clubs_pile.area = manager->loaded_board->board_clubs_position;


    manager->spades_pile = (card_pile){};
    manager->spades_pile.cards = malloc(sizeof(card) * 13);
    for (int i = 0; i < 13; i++)
        manager->spades_pile.cards[i] = NULL;
    manager->spades_pile.face = spades;
    manager->spades_pile.count = 0;
    manager->spades_pile.area = manager->loaded_board->board_spades_position;


    manager->hearts_pile = (card_pile){};
    manager->hearts_pile.cards = malloc(sizeof(card) * 13);
    for (int i = 0; i < 13; i++)
        manager->hearts_pile.cards[i] = NULL;
    manager->hearts_pile.face = hearts;
    manager->hearts_pile.count = 0;
    manager->hearts_pile.area = manager->loaded_board->board_hearts_position;


    manager->diamonds_pile = (card_pile){};
    manager->diamonds_pile.cards = malloc(sizeof(card) * 13);
    for (int i = 0; i < 13; i++)
        manager->diamonds_pile.cards[i] = NULL;
    manager->diamonds_pile.face = diamonds;
    manager->diamonds_pile.count = 0;
    manager->diamonds_pile.area = manager->loaded_board->board_diamonds_position;
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

    manager->row_1 = malloc(sizeof(card_row));
    manager->row_2 = malloc(sizeof(card_row));
    manager->row_3 = malloc(sizeof(card_row));
    manager->row_4 = malloc(sizeof(card_row));
    manager->row_5 = malloc(sizeof(card_row));
    manager->row_6 = malloc(sizeof(card_row));
    manager->row_7 = malloc(sizeof(card_row));

    manager->row_1->cards = malloc(sizeof(card) * 13);
    manager->row_1->card_count = 1;
    manager->row_1->first_card_shown = 0;
    manager->row_1->area_id = row1;
    for (int k = 0; k < 13; k++)
        manager->row_1->cards[k] = NULL;
    manager->row_1->cards[0] = manager->cards[numbers_to_use_list[0]];


    manager->row_2->cards = malloc(sizeof(card) * 13);
    manager->row_2->card_count = 2;
    manager->row_2->first_card_shown = 1;
    manager->row_2->area_id = row2;
    for (int k = 0; k < 13; k++)
        manager->row_2->cards[k] = NULL;
    manager->row_2->cards[0] = manager->cards[numbers_to_use_list[1]];
    manager->row_2->cards[1] = manager->cards[numbers_to_use_list[2]];

    manager->row_3->cards = malloc(sizeof(card) * 13);
    manager->row_3->card_count = 3;
    manager->row_3->first_card_shown = 2;
    manager->row_3->area_id = row3;
    for (int k = 0; k < 13; k++)
        manager->row_3->cards[k] = NULL;
    manager->row_3->cards[0] = manager->cards[numbers_to_use_list[3]];
    manager->row_3->cards[1] = manager->cards[numbers_to_use_list[4]];
    manager->row_3->cards[2] = manager->cards[numbers_to_use_list[5]];

    manager->row_4->cards = malloc(sizeof(card) * 13);
    manager->row_4->card_count = 4;
    manager->row_4->first_card_shown = 3;
    manager->row_4->area_id = row4;
    for (int k = 0; k < 13; k++)
        manager->row_4->cards[k] = NULL;
    manager->row_4->cards[0] = manager->cards[numbers_to_use_list[6]];
    manager->row_4->cards[1] = manager->cards[numbers_to_use_list[7]];
    manager->row_4->cards[2] = manager->cards[numbers_to_use_list[8]];
    manager->row_4->cards[3] = manager->cards[numbers_to_use_list[9]];

    manager->row_5->cards = malloc(sizeof(card) * 13);
    manager->row_5->card_count = 5;
    manager->row_5->first_card_shown = 4;
    manager->row_5->area_id = row5;
    for (int k = 0; k < 13; k++)
        manager->row_5->cards[k] = NULL;
    manager->row_5->cards[0] = manager->cards[numbers_to_use_list[10]];
    manager->row_5->cards[1] = manager->cards[numbers_to_use_list[11]];
    manager->row_5->cards[2] = manager->cards[numbers_to_use_list[12]];
    manager->row_5->cards[3] = manager->cards[numbers_to_use_list[13]];
    manager->row_5->cards[4] = manager->cards[numbers_to_use_list[14]];

    manager->row_6->cards = malloc(sizeof(card) * 13);
    manager->row_6->card_count = 6;
    manager->row_6->first_card_shown = 5;
    manager->row_6->area_id = row6;
    for (int k = 0; k < 13; k++)
        manager->row_6->cards[k] = NULL;
    manager->row_6->cards[0] = manager->cards[numbers_to_use_list[15]];
    manager->row_6->cards[1] = manager->cards[numbers_to_use_list[16]];
    manager->row_6->cards[2] = manager->cards[numbers_to_use_list[17]];
    manager->row_6->cards[3] = manager->cards[numbers_to_use_list[18]];
    manager->row_6->cards[4] = manager->cards[numbers_to_use_list[19]];
    manager->row_6->cards[5] = manager->cards[numbers_to_use_list[20]];

    manager->row_7->cards = malloc(sizeof(card) * 13);
    manager->row_7->card_count = 7;
    manager->row_7->first_card_shown = 6;
    manager->row_7->area_id = row7;
    for (int k = 0; k < 13; k++)
        manager->row_7->cards[k] = NULL;
    manager->row_7->cards[0] = manager->cards[numbers_to_use_list[21]];
    manager->row_7->cards[1] = manager->cards[numbers_to_use_list[22]];
    manager->row_7->cards[2] = manager->cards[numbers_to_use_list[23]];
    manager->row_7->cards[3] = manager->cards[numbers_to_use_list[24]];
    manager->row_7->cards[4] = manager->cards[numbers_to_use_list[25]];
    manager->row_7->cards[5] = manager->cards[numbers_to_use_list[26]];
    manager->row_7->cards[6] = manager->cards[numbers_to_use_list[27]];


    // assign stuff to the stack
    manager->cards_in_third_stack = 0;
    manager->rest_of_cards = malloc(sizeof(card) * 22);
    manager->card_stack_cards = malloc(sizeof(card) * 24);
    manager->max_cards_in_stack = 24;
    manager->cards_in_stack = 24;
    for (int i = 0; i < 24; i++) {
        manager->card_stack_cards[i] = manager->cards[numbers_to_use_list[i + 28]];
    }

    free(numbers_to_use_list);
}

void update_row(card_manager* manager, card_row* row) {
    vector2 row_position = { 0, 0 };
    switch (row->area_id) {
    case row1: row_position = manager->loaded_board->board_cards_position_1; break;
    case row2: row_position = manager->loaded_board->board_cards_position_2; break;
    case row3: row_position = manager->loaded_board->board_cards_position_3; break;
    case row4: row_position = manager->loaded_board->board_cards_position_4; break;
    case row5: row_position = manager->loaded_board->board_cards_position_5; break;
    case row6: row_position = manager->loaded_board->board_cards_position_6; break;
    case row7: row_position = manager->loaded_board->board_cards_position_7; break;
    }

    for (int i = 0; i < row->card_count; i++) {
        row->cards[i]->position = row_position;
        row->cards[i]->position.y -= (i * 20);

        if (i >= row->first_card_shown) {
            row->cards[i]->flipped = false;
            row->cards[i]->is_moveable = true;
        }
        else
            row->cards[i]->flipped = true;

        move_card_to_top(manager, row->cards[i]);

        if (manager->held_card->held_card != NULL)
            if (manager->held_card->held_card == row->cards[i])
                manager->held_card->held_card_area = row->area_id;
    }
}

void set_card_row_positions(card_manager* manager) {
   update_row(manager, manager->row_1);
   update_row(manager, manager->row_2);
   update_row(manager, manager->row_3);
   update_row(manager, manager->row_4);
   update_row(manager, manager->row_5);
   update_row(manager, manager->row_6);
   update_row(manager, manager->row_7);

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
    for (int i = manager->max_cards_in_stack - 1; i >= 0; i--) {
        if (manager->card_stack_cards[i] == NULL)
            continue;

        move_card_to_top(manager, manager->card_stack_cards[i]);
    }

    card* first_card = NULL;
    for (int k = 0; k < 24; k++) {
        if (manager->card_stack_cards[k] == NULL) {
            continue;
        }
        
        first_card = manager->card_stack_cards[k];
        break;
    }

    card* last_card = NULL;
    for (int k = 23; k >= 0; k--) {
        if (manager->card_stack_cards[k] == NULL)
            continue;
        
        last_card = manager->card_stack_cards[k];
        break;
    }

    if (manager->held_card->held_card == last_card)
        manager->held_card->held_card_area = stack;

    bool in_card_area = in_board_area(manager->hover, manager->loaded_board->card_stack_position);
    if (in_card_area && manager->hover->input_manager->mouse_clicked) {
        int add_amonnt = (manager->card_stack_show_1 != NULL) + (manager->card_stack_show_2 != NULL);
        #ifdef LOG_DATA
        printf("\nStuff for the item reset, %i, %i\n", (manager->cards_in_third_stack + add_amonnt), manager->cards_in_stack);
        #endif
        if ((manager->cards_in_third_stack + add_amonnt) == manager->cards_in_stack) {
            manager->card_stack_show_1 = NULL;
            manager->card_stack_show_2 = NULL;
            for (int k = 0; k < 24; k++) {
                manager->rest_of_cards[k] = NULL;
            }
            manager->cards_in_third_stack = 0;
            for (int i = 0; i < 24; i++) {
                if (manager->card_stack_cards[i] == NULL)
                    continue;
                manager->card_stack_cards[i]->flipped = true;
            }
        } else {
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
            while (manager->card_stack_cards[0] == NULL)
                rotate_stack_array(manager);
        }
    }

    first_card->mouse_over = false;
}
void position_card_stacks(card_manager* manager) {
    if (manager->cards_in_stack == 0)
        return;

    for (int i = 0; i < 24; i++) {
        if (manager->card_stack_cards[i] == NULL)
            continue;
        manager->card_stack_cards[i]->position = manager->loaded_board->card_stack_position;
    }

    for (int k = 0; k < manager->cards_in_third_stack; k++) {
        manager->rest_of_cards[k]->position.x = (manager->loaded_board->card_stack_position.x - 200.0f);
        manager->rest_of_cards[k]->is_moveable = false;
        move_card_to_top(manager, manager->rest_of_cards[k]);
    }

    if (manager->card_stack_show_2 != NULL) {
        manager->card_stack_show_2->position.x = (manager->loaded_board->card_stack_position.x - 150.0f);
        manager->card_stack_show_2->is_moveable = false;
        move_card_to_top(manager, manager->card_stack_show_2);
    }

    if (manager->card_stack_show_1 != NULL) {
        manager->card_stack_show_1->position.x = (manager->loaded_board->card_stack_position.x - 100.0f);
        manager->card_stack_show_1->is_moveable = true;
        move_card_to_top(manager, manager->card_stack_show_1);
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

int get_last_index(card** cards) {
    if (cards[0] == NULL)
        return 0;

    for (int q = 0; q < 13; q++) {
        if (cards[q] == NULL)
            return q - 1;
    }
}

card** get_top_row_cards(card_manager* manager) {
    card** new_cards = malloc(sizeof(card) * 7);
    for (int q = 0; q < 7; q++)
        new_cards[q] = NULL;

    new_cards[0] = manager->row_1->cards[get_last_index(manager->row_1->cards)];
    new_cards[1] = manager->row_2->cards[get_last_index(manager->row_2->cards)];
    new_cards[2] = manager->row_3->cards[get_last_index(manager->row_3->cards)];
    new_cards[3] = manager->row_4->cards[get_last_index(manager->row_4->cards)];
    new_cards[4] = manager->row_5->cards[get_last_index(manager->row_5->cards)];
    new_cards[5] = manager->row_6->cards[get_last_index(manager->row_6->cards)];
    new_cards[6] = manager->row_7->cards[get_last_index(manager->row_7->cards)];

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

void remove_card_from_stack(card_manager* manager) {
    int last_card_index = 0;
    for (int i = 23; i >= 0; i--) {
        if (manager->card_stack_cards[i] == NULL)
            continue;
        else {
            last_card_index = i;
            break;
        }
    }

    manager->card_stack_cards[last_card_index] = NULL;
    manager->cards_in_stack--;

    if (manager->card_stack_show_2 == NULL) {
        manager->card_stack_show_1 = NULL;
    } else if (manager->cards_in_third_stack == 0) {
        manager->card_stack_show_1 = manager->card_stack_show_2;
        manager->card_stack_show_2 = NULL;

        move_card_to_top(manager, manager->card_stack_show_1);
    } else {
        if (manager->cards_in_third_stack == 1) {
            manager->cards_in_third_stack = 0;

            manager->card_stack_show_1 = manager->card_stack_show_2;
            manager->card_stack_show_2 = manager->rest_of_cards[0];
            manager->rest_of_cards[0] = NULL;

            move_card_to_top(manager, manager->card_stack_show_2);
            move_card_to_top(manager, manager->card_stack_show_1);
        } else {

            manager->card_stack_show_1 = manager->card_stack_show_2;

            int nextValidIndex = 0;
            for (int q = 0; q < manager->cards_in_third_stack; q++) {
                if (manager->rest_of_cards[q] != NULL) {
                    nextValidIndex = q;
                    break;
                } 
            }

            manager->card_stack_show_2 = manager->rest_of_cards[nextValidIndex];

            for (int i = 0; i < manager->cards_in_third_stack - 1; i++) {
                manager->rest_of_cards[i] = manager->rest_of_cards[i + 1];
            }
            manager->cards_in_third_stack--;

            move_card_to_top(manager, manager->card_stack_show_2);
            move_card_to_top(manager, manager->card_stack_show_1);

        }
    }
}

void remove_card_from_row(card_manager* manager, card_row* row) {
    if (row->card_count >= 2)
        if (row->cards[row->card_count - 2]->flipped == true)
            row->first_card_shown--;

    row->card_count--;
    row->cards[row->card_count] = NULL;
}

void remove_held_card_from_area(card_manager* manager) {
    if (manager->held_card->held_card_area == stack) {
        remove_card_from_stack(manager);
    }
    else {
        for (int i = 0; i < manager->held_card->other_held_cards_count + 1; i++) {
            switch (manager->held_card->held_card_area) {
            case row1: remove_card_from_row(manager, manager->row_1); break;
            case row2: remove_card_from_row(manager, manager->row_2); break;
            case row3: remove_card_from_row(manager, manager->row_3); break;
            case row4: remove_card_from_row(manager, manager->row_4); break;
            case row5: remove_card_from_row(manager, manager->row_5); break;
            case row6: remove_card_from_row(manager, manager->row_6); break;
            case row7: remove_card_from_row(manager, manager->row_7); break;
            }
        }
    }

    
}

void drop_held_card(card_manager* manger) {
    if (manger->held_card->held_card == NULL)
        return;

    manger->held_card->held_card = NULL;
    manger->held_card->held_card_area = no_area;
    manger->held_card->other_held_cards_count = 0;
}

void see_if_held_card_can_be_dropped_in_pile(card_manager* manager) {
    //printf("The currently held card is of type: %i\n", manager->held_card->held_card->data.type);

    if (manager->hover->input_manager->mouse_down) 
        return;

    if (manager->held_card->held_card->data.type == clubs) {
        if (test_card_in_area(manager->hover, manager->held_card->held_card, manager->clubs_pile.area)) {
            if (manager->clubs_pile.count == manager->held_card->held_card->data.value) {
                remove_held_card_from_area(manager);

                manager->clubs_pile.cards[manager->clubs_pile.count] = manager->held_card->held_card;
                manager->clubs_pile.count++;
                
                drop_held_card(manager);
            }
        }
    } else if (manager->held_card->held_card->data.type == spades) {
        if (test_card_in_area(manager->hover, manager->held_card->held_card, manager->spades_pile.area)) {
            if (manager->spades_pile.count == manager->held_card->held_card->data.value) {
                remove_held_card_from_area(manager);

                manager->spades_pile.cards[manager->spades_pile.count] = manager->held_card->held_card;
                manager->spades_pile.count++;

                drop_held_card(manager);
            }
        }
    } else if (manager->held_card->held_card->data.type == hearts) {
        if (test_card_in_area(manager->hover, manager->held_card->held_card, manager->hearts_pile.area)) {
            if (manager->hearts_pile.count == manager->held_card->held_card->data.value) {
                remove_held_card_from_area(manager);

                manager->hearts_pile.cards[manager->hearts_pile.count] = manager->held_card->held_card;
                manager->hearts_pile.count++;

                drop_held_card(manager);
            }
        }
    } else if (manager->held_card->held_card->data.type == diamonds) {
        if (test_card_in_area(manager->hover, manager->held_card->held_card, manager->diamonds_pile.area)) {
            if (manager->diamonds_pile.count == manager->held_card->held_card->data.value) {
                remove_held_card_from_area(manager);

                manager->diamonds_pile.cards[manager->diamonds_pile.count] = manager->held_card->held_card;
                manager->diamonds_pile.count++;
                
                drop_held_card(manager);
            }
        }
    }
}

void update_card_pile(card_manager* manager, card_pile* pile) {
    vector2 card_pile_position = (vector2){-100, -100};
    
    switch (pile->face) {
    case clubs: card_pile_position = manager->loaded_board->board_clubs_position; break;
    case spades: card_pile_position = manager->loaded_board->board_spades_position; break;
    case hearts: card_pile_position = manager->loaded_board->board_hearts_position; break;
    case diamonds: card_pile_position = manager->loaded_board->board_diamonds_position; break;
    }

    for (int i = 0; i < pile->count; i++) {
        pile->cards[i]->position = card_pile_position;
        pile->cards[i]->is_moveable = false;
    }
}

void update_card_piles(card_manager* manager) {
    update_card_pile(manager, &manager->clubs_pile);
    update_card_pile(manager, &manager->spades_pile);
    update_card_pile(manager, &manager->hearts_pile);
    update_card_pile(manager, &manager->diamonds_pile);
}

void move_card_to_other_rows(card_manager* manager) {
    if (manager->held_card->held_card == NULL)
        return;

    card* current_card = manager->held_card->held_card;
    #ifdef LOG_DATA
    printf("Card ID: %i\n", current_card);
    #endif

    card** cards_to_collide_with = get_top_row_cards(manager);
    #ifdef LOG_DATA
    printf("Cards IDS: %i, %i, %i, %i, %i, %i, %i\n", 
        cards_to_collide_with[0], cards_to_collide_with[1], cards_to_collide_with[2], cards_to_collide_with[3],
        cards_to_collide_with[4], cards_to_collide_with[5], cards_to_collide_with[6]);
    #endif

    float distances[7] = { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };
    vector2 postion_to_collide_with = {};
    for (int q = 0; q < 7; q++) {
        if (cards_to_collide_with[q] != NULL) {
            distances[q] = get_distance(current_card->position, cards_to_collide_with[q]->position);
            if (cards_to_collide_with[q] == current_card)
                distances[q] = INT64_MAX;

            if (!is_opposite_color(cards_to_collide_with[q]->data.type, current_card->data.type))
                distances[q] = INT64_MAX;

            if (cards_to_collide_with[q]->data.value != (current_card->data.value + 1))
                distances[q] = INT64_MAX;
        } else {

            switch (q) {
                case 0: postion_to_collide_with = manager->loaded_board->board_cards_position_1; break;
                case 1: postion_to_collide_with = manager->loaded_board->board_cards_position_2; break;
                case 2: postion_to_collide_with = manager->loaded_board->board_cards_position_3; break;
                case 3: postion_to_collide_with = manager->loaded_board->board_cards_position_4; break;
                case 4: postion_to_collide_with = manager->loaded_board->board_cards_position_5; break;
                case 5: postion_to_collide_with = manager->loaded_board->board_cards_position_6; break;
                case 6: postion_to_collide_with = manager->loaded_board->board_cards_position_7; break; 
            }

            distances[q] = get_distance(current_card->position, postion_to_collide_with);
            if (current_card->data.value != king)
                distances[q] = INT64_MAX;
        }
    }

    #ifdef LOG_DATA
    printf("Distances: {%f, %f, %f, %f, %f, %f, %f}\n", 
        distances[0], distances[1], distances[2], distances[3], distances[4], distances[5], distances[6]);
    #endif

    int lowest_distance_index = lowest_distance(distances, 7);
    if (distances[lowest_distance_index] == INT64_MAX)
        return;

    if (cards_to_collide_with[lowest_distance_index] != NULL) {

        if (test_card_collision(manager->hover, current_card, cards_to_collide_with[lowest_distance_index]) && !manager->hover->input_manager->mouse_down) {
            remove_held_card_from_area(manager);

            card_row* row_to_add_to = NULL;
            switch (lowest_distance_index) {
                case 0: row_to_add_to = manager->row_1; break;
                case 1: row_to_add_to = manager->row_2; break;
                case 2: row_to_add_to = manager->row_3; break;
                case 3: row_to_add_to = manager->row_4; break;
                case 4: row_to_add_to = manager->row_5; break;
                case 5: row_to_add_to = manager->row_6; break;
                case 6: row_to_add_to = manager->row_7; break; 
            }

            row_to_add_to->cards[row_to_add_to->card_count] = current_card;
            row_to_add_to->card_count++;

            for (int i = 0; i < manager->held_card->other_held_cards_count; i++) {
                row_to_add_to->cards[row_to_add_to->card_count] = manager->held_card->other_held_cards[i];
                row_to_add_to->card_count++;
            }

            drop_held_card(manager);
        }
    } else {
        if (test_card_in_area(manager->hover, current_card, postion_to_collide_with) && !manager->hover->input_manager->mouse_down) {
            remove_held_card_from_area(manager);

            card_row* row_to_add_to = NULL;
            switch (lowest_distance_index) {
                case 0: row_to_add_to = manager->row_1; break;
                case 1: row_to_add_to = manager->row_2; break;
                case 2: row_to_add_to = manager->row_3; break;
                case 3: row_to_add_to = manager->row_4; break;
                case 4: row_to_add_to = manager->row_5; break;
                case 5: row_to_add_to = manager->row_6; break;
                case 6: row_to_add_to = manager->row_7; break; 
            }

            row_to_add_to->cards[0] = current_card;
            row_to_add_to->card_count++;

            for (int i = 0; i < manager->held_card->other_held_cards_count; i++) {
                row_to_add_to->cards[row_to_add_to->card_count] = manager->held_card->other_held_cards[i];
                row_to_add_to->card_count++;
            }

            drop_held_card(manager);
        }
    }
}

void update_held_card(card_manager* manager) {
    if (manager->held_card->held_card == NULL)
        return;

    #ifdef LOG_DATA
    printf("started updating the held card\n");
    #endif

    float real_mouse_x = (((manager->hover->input_manager->mouse_position.x / 1280.0f) * 2) - 1) * 640;
    float real_mouse_y = -((((manager->hover->input_manager->mouse_position.y / 720.0f) * 2) - 1) * 360);

    real_mouse_x -= manager->held_card->card_held_offset.x;
    real_mouse_y -= manager->held_card->card_held_offset.y;
    manager->held_card->held_card->position = (vector2){ real_mouse_x, real_mouse_y };
    manager->held_card->held_card->held = 1;

    move_card_to_top(manager, manager->held_card->held_card);

    for (int i = 0; i < manager->held_card->other_held_cards_count; i++) {
        manager->held_card->other_held_cards[i]->position = manager->held_card->held_card->position; 
        manager->held_card->other_held_cards[i]->position.y -= (20 * (i + 1));
        move_card_to_top(manager, manager->held_card->other_held_cards[i]);
    }
    
    #ifdef LOG_DATA
    printf("held cards count: %i\n", manager->held_card->other_held_cards_count);
    #endif

    if (manager->held_card->other_held_cards_count == 0)
        see_if_held_card_can_be_dropped_in_pile(manager);

    #ifdef LOG_DATA
    printf("we saw if we could drop it in a pile\n");
    #endif

    if (manager->held_card->held_card != NULL) 
        move_card_to_other_rows(manager);

    #ifdef LOG_DATA
    printf("and we saw if we could drop it in another row\n");
    #endif

    if (!manager->hover->input_manager->mouse_down) {
        manager->held_card->held_card = NULL;
    }

    #ifdef LOG_DATA
    printf("Finised updating the held card\n");
    #endif
}

void get_cards_below_grabbed_card(card_manager* manager) {
    if (manager->held_card->held_card == NULL)
        return;

     manager->held_card->other_held_cards_count = 0;

    if (manager->held_card->held_card_area == stack)
        return;

    card_row* row_card_is_in = NULL;
    switch (manager->held_card->held_card_area) {
    case row1: row_card_is_in = manager->row_1; break;
    case row2: row_card_is_in = manager->row_2; break;
    case row3: row_card_is_in = manager->row_3; break;
    case row4: row_card_is_in = manager->row_4; break;
    case row5: row_card_is_in = manager->row_5; break;
    case row6: row_card_is_in = manager->row_6; break;
    case row7: row_card_is_in = manager->row_7; break;
    }

    if (row_card_is_in == NULL)
        return;

    manager->held_card->other_held_cards_count = 0;
    for (int i = 0; i < 13; i++)
        manager->held_card->other_held_cards[i] = NULL;

    if (row_card_is_in->cards[row_card_is_in->card_count - 1] != manager->held_card->held_card) {
        int amount_to_add = 0;
        int last_index = 0;
        for (int i = row_card_is_in->card_count - 1; i >= 0; i--) {
            if (row_card_is_in->cards[i] == manager->held_card->held_card)
                break;

            last_index = i;

            amount_to_add++;
        }

        for (int i = 0; i < amount_to_add; i++) {
            manager->held_card->other_held_cards[manager->held_card->other_held_cards_count] = row_card_is_in->cards[last_index + i];
            manager->held_card->other_held_cards_count++;
        }
    }
}

void update_card_manager(card_manager* manager) {
    bool card_already_hovered = false;

    if (manager->cards_in_stack > 0) {
        check_stack_clicked(manager);
        position_card_stacks(manager);
    }

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

            float real_mouse_x = (((manager->hover->input_manager->mouse_position.x / 1280.0f) * 2) - 1) * 640;
            float real_mouse_y = -((((manager->hover->input_manager->mouse_position.y / 720.0f) * 2) - 1) * 360);

            float card_held_offset_x = real_mouse_x - current_card->position.x;
            float card_held_offset_y = real_mouse_y - current_card->position.y;

            manager->held_card->card_held_offset = (vector2){ card_held_offset_x, card_held_offset_y };

         }
    }

    set_card_row_positions(manager);

    update_card_piles(manager);
    get_cards_below_grabbed_card(manager);
    update_held_card(manager);

    for (int i = 51; i >= 0; i--) {
        draw_card(manager->renderer, manager->cards[i]);
    }
}

void cleanup_card_manager(card_manager* manager) {
    free(manager->row_1);
    free(manager->row_2);
    free(manager->row_3);
    free(manager->row_4);
    free(manager->row_5);
    free(manager->row_6);
    free(manager->row_7);

    free(manager->card_stack_cards);

    free(manager->card_stack_show_1);
    free(manager->card_stack_show_2);
    free(manager->rest_of_cards);

    free(manager->cards);
}