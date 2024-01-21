#pragma once
#include "window_items/window_data.h"
#include "window_items/window_properties.h"

#include "src/types/boolean.h"

typedef struct window {
    window_data data;
    window_properties properties;

    bool is_open;
} window;

window window_create();
void window_open(window* win);
void window_update(window* win);
void window_close(window* win);

extern bool window_is_open(window* win) { return win->is_open; }

extern window_data* window_get_data(window* win) { return &win->data; }
extern window_properties* window_get_properties(window* win) { return &win->properties; }
