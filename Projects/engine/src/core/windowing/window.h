#pragma once
#include "engine_api.h"
#include "window_items/window_data.h"
#include "window_items/window_properties.h"

#include "src/types/boolean.h"

struct platform_window_props;

typedef struct window {
    window_data data;
    window_properties properties;

    bool is_open;

    struct platform_window_props* platform_properties;
} window;

window window_create();
void window_open(window* win);
void window_update(window* win);
void window_close(window* win);

HEADER_DEF bool window_is_open(window* win) { return win->is_open; }

HEADER_DEF window_data* window_get_data(window* win) { return &win->data; }
HEADER_DEF window_properties* window_get_properties(window* win) { return &win->properties; }
