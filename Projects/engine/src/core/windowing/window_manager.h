#pragma once
#include "engine_api.h"
#include "window.h"

typedef struct window_manager {
    window* main_window;

    window** windows;
    int windows_count;
} window_manager;

HEADER_DEF window_manager window_manager_create() {
    window_manager new_window_manager = (window_manager){};
    new_window_manager.main_window = NULL;

    new_window_manager.windows = NULL;
    new_window_manager.windows_count = 0;
    return new_window_manager;
}

HEADER_DEF void window_manager_set_main_window(window_manager* win_manager, window* window) {
    if (win_manager->main_window != NULL) {
        printf("main window already set you can not reset the main window\n");
        return;
    }

    win_manager->main_window = window;
}

HEADER_DEF void window_manager_add_window(window_manager* win_manager, window* window) {
    if (win_manager->main_window == NULL) {
        printf("You need to create the main window first\n");
        return;
    }

    win_manager->windows = realloc(win_manager->windows, win_manager->windows_count + 1);
    win_manager->windows[win_manager->windows_count] = window;
    win_manager->windows_count++;
}

HEADER_DEF void window_manager_update(window_manager* win_manager) {
    window_update(win_manager->main_window);
    for (int i = 0; i < win_manager->windows_count; i++)
        window_update(win_manager->windows[i]);
}   