#include "card_manager.h"
#include "time.h"

bool mouse_in_bounds(ivec2 card_position, ivec2 mouse_positon) {
    return  (((-1.125f) * 40.0f) + card_position.x) < mouse_positon.x && 
            ((( 1.125f) * 40.0f) + card_position.x) > mouse_positon.x &&

            ((( 1.750f) * 40.0f) + card_position.y) > mouse_positon.y &&
            (((-1.750f) * 40.0f) + card_position.y) < mouse_positon.y;
}

static bool card_already_hovered = false;

typedef struct card_render {
    ivec2 position;
    ivec3 card_data;
} card_render;

void card_manager_draw_card(card_manager* manager, ivec2 position, int card_id) {
    bool hoverd = mouse_in_bounds(position, input_manager_get_mouse_pos(manager->input)) && !card_already_hovered;

    card_render* new_card_render = malloc(sizeof(card_render));
    new_card_render->card_data = (ivec3){ card_id, hoverd, hoverd && input_manager_get_mouse_down(manager->input) };
    new_card_render->position = position;
    array_list_set(&manager->cards_to_render, manager->card_draw_count, new_card_render);

    manager->card_draw_count++;

    if (hoverd) card_already_hovered = true;
}

void render_cards(card_manager* manager) {
    for (int i = manager->card_draw_count - 1; i >= 0; i--) {
        card_render* rn = array_list_get(&manager->cards_to_render, i);

        card_renderer_draw_card(
            manager->card_renderer, 
            (vec2){ rn->position.x, rn->position.y }, 
            rn->card_data
        );     
    }

    manager->card_draw_count = 0;
}

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

    manager->cards_to_render = array_list_create();
}

void card_manager_draw_cards(card_manager* manager) {
    //manager->cards_to_render = array_list_create();

    card_already_hovered = false;
    // draw cards in stack

    if (manager->stack_flip_position < linked_list_size(&manager->cards_in_stack)) {
        board_area* position = (board_area*)array_list_get(&manager->board->areas, 11);
        card_manager_draw_card(manager, position->position, 52);
    }

    // draw card rows

    for (int k = 0; k < 7; k++) {
        for (int i = linked_list_size(&manager->card_rows[k]) - 1; i >= 0; i--) {
            struct card_data* current_card_data = (struct card_data*)linked_list_get(&manager->card_rows[k], i);
            int number = current_card_data->number;
            if (current_card_data->flipped)
                number = 52;

            board_area* position = (board_area*)array_list_get(&manager->board->areas, 4 + k);
            card_manager_draw_card(manager, (ivec2){ position->position.x, position->position.y - (i * 20) }, number);
        }
    }


    int k = 0;
    for (int i = manager->stack_flip_position - 1; i >= 0; i--) {
        if ((manager->stack_flip_position - 1) - i > 3) continue;

        if (manager->stack_flip_position == 1) {
            k = 2;
        } else if (manager->stack_flip_position == 2) {
            k = 1 + i;
        } else {
            int i2 = i + 1;
            if (i2 == manager->stack_flip_position)
                k = 2;
            else if (i2 == manager->stack_flip_position - 1) {
                k = 1;
            } else {
                k = 0;
            }
        }

        struct card_data* current_card_data = (struct card_data*)linked_list_get(&manager->cards_in_stack, i);

        int offset = 160 - (30 * k);

        board_area* position = (board_area*)array_list_get(&manager->board->areas, 11);
        card_manager_draw_card(manager, (ivec2){ position->position.x - offset, position->position.y }, current_card_data->number);
    }

    //card_manager_draw_card(manager, (ivec2){ manager->input->mouse_position.x, manager->input->mouse_position.y }, 52 );

    render_cards(manager);
}

void card_manager_flip_stack(card_manager* manager) {
    manager->stack_flip_position++;

    if (manager->stack_flip_position > linked_list_size(&manager->cards_in_stack)) {
        manager->stack_flip_position = 0;
    }
}

void card_manager_remove_from_stack(card_manager* manager) {
    manager->stack_flip_position--;
    linked_list_remove(&manager->cards_in_stack, manager->stack_flip_position);
}