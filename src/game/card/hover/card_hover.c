#include "card_hover.h"

bool test_card_hover(card_hover* hover, card* card_to_test) {
    float real_mouse_x = (((hover->input_manager->mouse_position.x / 1280.0f) * 2) - 1) * 640;
    float real_mouse_y = -((((hover->input_manager->mouse_position.y / 720.0f) * 2) - 1) * 360);

    float card_size_x = 2.25f * card_to_test->scale;
    float card_size_y = 3.5f * card_to_test->scale;

    float card_bounds_left = card_to_test->position.x - (card_size_x / 2.0f);
    float card_bounds_right = card_to_test->position.x + (card_size_x / 2.0f);

    float card_bounds_top = card_to_test->position.y + (card_size_y / 2.0f);
    float card_bounds_bottom = card_to_test->position.y - (card_size_y / 2.0f);

    card_to_test->mouse_over = false;

    if (real_mouse_x > card_bounds_left && real_mouse_x < card_bounds_right &&
        real_mouse_y > card_bounds_bottom && real_mouse_y < card_bounds_top)
        card_to_test->mouse_over = true;

    return card_to_test->mouse_over;
}

bool in_board_area(card_hover* hover, vector2 board_area) {
    float real_mouse_x = (((hover->input_manager->mouse_position.x / 1280.0f) * 2) - 1) * 640;
    float real_mouse_y = -((((hover->input_manager->mouse_position.y / 720.0f) * 2) - 1) * 360);

    float card_size_x = 2.25f * 40.0f;
    float card_size_y = 3.5f * 40.0f;

    float card_bounds_left = board_area.x - (card_size_x / 2.0f);
    float card_bounds_right = board_area.x + (card_size_x / 2.0f);

    float card_bounds_top = board_area.y + (card_size_y / 2.0f);
    float card_bounds_bottom = board_area.y - (card_size_y / 2.0f);

    bool mouse_inside = false;

    if (real_mouse_x > card_bounds_left && real_mouse_x < card_bounds_right &&
        real_mouse_y > card_bounds_bottom && real_mouse_y < card_bounds_top)
        mouse_inside = true;

    return mouse_inside;   
}