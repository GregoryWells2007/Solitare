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
    window->platform_window->window = glfwCreateWindow(window->data.size.x, window->data.size.y, window->data.title, NULL, NULL);

    if (!window->platform_window->window)
        printf("Window failed to open\n");
    glfwHideWindow(window->platform_window->window);
}

void platform_window_open(window* window) {
    

    glfwShowWindow(window->platform_window->window);
}

void platform_window_update(window* window) {
    glfwMakeContextCurrent(window->platform_window->window);

    glfwSwapBuffers(window->platform_window->window);
    glfwPollEvents();
}

void platform_window_close(window* window) {
    glfwDestroyWindow(window->platform_window->window);
}

#endif
