#pragma once
#include "engine_api.h"
#include "window_items/window_data.h"
#include "window_items/window_properties.h"

#include "src/types/boolean.h"

typedef struct window window;

// platform window stuff
struct platform_window;
void platform_window_create(window* window);
void platform_window_open(window* window);
void platform_window_update(window* window);
void platform_window_close(window* window);

typedef struct window {
    window_data data;
    window_properties properties;

    bool is_open;

    struct platform_window* platform_window;
} window;

HEADER_DEF window window_create() {
    window new_window = (window) {};
    new_window.data = (window_data) { "New Window", (vector2){ 1280, 720 } };
    new_window.properties = (window_properties) {  };

    platform_window_create(&new_window);
    return new_window;
}
HEADER_DEF void window_open(window* win) {
    win->is_open = true;
    platform_window_open(win);
}
HEADER_DEF void window_update(window* win) {
    // i dont need to do anything here
    platform_window_update(win);
}
HEADER_DEF void window_close(window* win) {
    // i also dont need to do anything here
    platform_window_close(win);
}

HEADER_DEF bool window_is_open(window* win) { return win->is_open; }

HEADER_DEF window_data* window_get_data(window* win) { return &win->data; }
HEADER_DEF window_properties* window_get_properties(window* win) { return &win->properties; }
