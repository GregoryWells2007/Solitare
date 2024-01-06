#pragma once
#include "GLFW/glfw3.h"
#include "engine/types/multi4.h"
#include "engine/input_manager/input_manager.h"

typedef struct window_data {
    int sizeX;
    int sizeY;
    char* name;
} window_data;

typedef struct window {
    GLFWwindow* window;
    input_manager* input;
} window;

void init_windows();
void close_windows();
void update_windows();

void init_opengl();

window create_window(window_data data);

float get_time();

void draw_window(window* window);
void clear_window(window* window, color window_color);
int isOpen(window* window);