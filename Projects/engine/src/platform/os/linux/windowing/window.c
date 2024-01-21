#include "engine_api.h"

#if OS == OS_LINUX
#include "src/core/windowing/window.h"
#include "GLFW/glfw3.h"

struct platform_window {
    GLFWwindow* window;
};

void platform_window_create(window* window) {
    window->platform_window = malloc(sizeof(struct platform_window));

    if (!glfwInit())
        printf("Failed to initlize GLFW\n");
    window->platform_window->window = glfwCreateWindow(500, 500, "Title", NULL, NULL);
    if (!window->platform_window->window)
        printf("Window failed to open\n");
}

void platform_window_open(window* window) {
    glfwMakeContextCurrent(window->platform_window->window);
}

void platform_window_update(window* window) {
    glfwSwapBuffers(window->platform_window->window);
    glfwPollEvents();
}

void platform_window_close(window* window) {
    glfwDestroyWindow(window->platform_window->window);
}

#endif
