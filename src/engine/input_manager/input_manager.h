#pragma once
#include "engine/types/multi2.h"

typedef struct input_manager {
    vector2 mouse_position;
} input_manager;

void set_mouse_pos(input_manager* input, vector2 pos);