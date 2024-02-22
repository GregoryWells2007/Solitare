#pragma once
#include "engine_api.h"
#include "src/types/vector2.h"

typedef struct input_manager {
    ivec2 mouse_position;

    bool mouse_down;
    bool mouse_clicked;
} input_manager;

HEADER_DEF input_manager input_manager_create() { return (input_manager) { }; }
void input_manager_set_mouse_pos(input_manager* manager, ivec2 mosue_pos);
ivec2 input_manager_get_mouse_pos(input_manager* manager);

void input_manager_click_mouse(input_manager* manager);
void input_manager_release_mouse(input_manager* manager);
HEADER_DEF bool input_manager_get_mouse_clicked(input_manager* manager) { return manager->mouse_clicked; }
HEADER_DEF bool input_manager_get_mouse_down(input_manager* manager) { return manager->mouse_down; }