#pragma once
#include "GLFW/glfw3.h"
#include "types/multi4.h"

typedef struct window_data {
    int sizeX;
    int sizeY;
    char* name;
} window_data;

typedef struct window {
    GLFWwindow* window;
} window;

void init_windows();
void close_windows();
void update_windows();

void init_opengl();

window create_window(window_data data);

void clear_window(window* window, color window_color);
int isOpen(window* window);