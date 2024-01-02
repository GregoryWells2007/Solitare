#pragma once
#include "GLFW/glfw3.h"

typedef struct window_data {
    int sizeX;
    int sizeY;
    char* name;
} window_data;

typedef struct window {
    GLFWwindow* window;
} window;

void init_window();
void close_window();

window create_window(window_data data);
int isOpen(window* window);