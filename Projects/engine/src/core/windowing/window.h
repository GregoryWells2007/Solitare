#pragma once
#include "engine_api.h"
#include "window_items/window_data.h"
#include "window_items/window_properties.h"

#include "src/core/screen_renderer/screen_renderer.h"

#include "src/types/boolean.h"

typedef struct window window;

// platform window stuff
struct platform_window;
void platform_window_create(window* window);
void platform_window_open(window* window);
void platform_window_update(window* window);
void platform_window_close(window* window);

void platform_window_set_size(window* window, int width, int height);
void platform_window_set_title(window* window, char* title);

void platform_window_set_resizable(window* window, bool resizable);
void platform_window_set_maximized(window* window, bool maximized);
void platform_window_set_decorated(window* window, bool decorated);

typedef struct window {
    // idfk man
    window* main_window;


    window_data data;
    window_properties properties;

    screen_renderer* renderer;

    bool is_open;

    vector2 current_size;

    struct platform_window* platform_window;
} window;

HEADER_DEF window window_create() {
    window new_window = (window) {};
    new_window.data = (window_data) { "New Window", (vector2){ 1280, 720 } };
    new_window.properties = (window_properties) { true, false, false };
    new_window.main_window = NULL;
    new_window.renderer = NULL;
    return new_window;
}
HEADER_DEF void window_open(window* win) {
    platform_window_create(win);

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
HEADER_DEF void window_update_data(window* win) {
    if (!win->is_open)
        return;

    platform_window_set_size(win, win->data.size.x, win->data.size.y);
    platform_window_set_title(win, win->data.title);
}
HEADER_DEF void window_update_properties(window* win) {
    if (!win->is_open)
        return;

    platform_window_set_resizable(win, win->properties.is_resizable);
    platform_window_set_maximized(win, win->properties.is_maximized);
    platform_window_set_decorated(win, win->properties.is_decorated);
}

HEADER_DEF bool window_is_open(window* win) { return win->is_open; }

HEADER_DEF window_data* window_get_data(window* win) { return &win->data; }
HEADER_DEF window_properties* window_get_properties(window* win) { return &win->properties; }
