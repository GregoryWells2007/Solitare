#include "glad/glad.h"
#include "window.h"
#include "stdio.h"

void init_window() {
    if (!glfwInit())
        printf("GLFW initilization failed\n");
}
void close_window() {
    glfwTerminate();
}

int isOpen(window* window) {
    return !glfwWindowShouldClose(window->window);
}