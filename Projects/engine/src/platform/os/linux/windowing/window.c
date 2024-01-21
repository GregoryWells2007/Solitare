#include "src/platform/platform.h"

#if OS == OS_LINUX
#include "src/core/windowing/window.h"
#include "GLFW/glfw3.h"

struct platform_window_props {
    GLFWwindow* window;
};

void platform_window_create(window* window) {

}

void platform_window_open(window* window) {

}

void platform_window_update(window* window) {

}

void platform_window_close(window* window) {

}

#endif
