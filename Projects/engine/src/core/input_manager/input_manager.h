#pragma once
#include "engine_api.h"
#include "src/types/vector2.h"

typedef struct input_manager {
    ivec2 mouse_position;
} input_manager;

HEADER_DEF input_manager input_manager_create() { return (input_manager) { 0, 0 }; }
void input_manager_set_mouse_pos(input_manager* manager, ivec2 mosue_pos);
ivec2 input_manager_get_mouse_pos(input_manager* manager);