#include "engine_api.h"

#if OS == OS_LINUX
#include "src/core/windowing/window.h"
#include "GLFW/glfw3.h"

// no fucking clue what this does 
// https://stackoverflow.com/questions/21421074/how-to-create-a-full-screen-window-on-the-current-monitor-with-glfw
static int mini(int x, int y) { return x < y ? x : y; }
static int maxi(int x, int y) { return x > y ? x : y; }
GLFWmonitor* get_current_monitor(GLFWwindow *window) {
    int nmonitors, i;
    int wx, wy, ww, wh;
    int mx, my, mw, mh;
    int overlap, bestoverlap;
    GLFWmonitor *bestmonitor;
    GLFWmonitor **monitors;
    const GLFWvidmode *mode;

    bestoverlap = 0;
    bestmonitor = NULL;

    glfwGetWindowPos(window, &wx, &wy);
    glfwGetWindowSize(window, &ww, &wh);
    monitors = glfwGetMonitors(&nmonitors);
    if (nmonitors == 1)
        return monitors[0]; 

    for (i = 0; i < nmonitors; i++) {
        mode = glfwGetVideoMode(monitors[i]);
        glfwGetMonitorPos(monitors[i], &mx, &my);
        mw = mode->width;
        mh = mode->height;

        overlap =
            maxi(0, mini(wx + ww, mx + mw) - maxi(wx, mx)) *
            maxi(0, mini(wy + wh, my + mh) - maxi(wy, my));

        if (bestoverlap < overlap) {
            bestoverlap = overlap;
            bestmonitor = monitors[i];
        }
    }

    return bestmonitor;
}

struct platform_window {
    GLFWwindow* window;
};

void glfw_maximize_window(window* main_window) {
    printf("maximising window\n");

    GLFWwindow* window = main_window->platform_window->window;

    glfwSetWindowAttrib(window, GLFW_DECORATED, GLFW_FALSE);
    GLFWmonitor* monitor = get_current_monitor(window);

    int x_pos, y_pos;
    glfwGetMonitorPos(monitor, &x_pos, &y_pos);
    
    const GLFWvidmode* mode = glfwGetVideoMode(monitor);
    int x_size = mode->width, y_size = mode->height;

    glfwSetWindowPos(window, x_pos, y_pos);
    glfwSetWindowSize(window, x_size, y_size);

    main_window->current_size.x = x_size;
    main_window->current_size.y = y_size;
}



void glfw_unmaximize_window(window* main_window) {
    printf("unmaximising window\n");

    GLFWwindow* window = main_window->platform_window->window;

    glfwSetWindowAttrib(window, GLFW_DECORATED, GLFW_TRUE);
    GLFWmonitor* monitor = get_current_monitor(window);
    
    int monitor_x_pos, monitor_y_pos;
    glfwGetMonitorPos(monitor, &monitor_x_pos, &monitor_y_pos);

    int window_x_size = main_window->data.size.x, window_y_size = main_window->data.size.y;
    const GLFWvidmode* mode = glfwGetVideoMode(monitor);
    int x_size = (mode->width / 2) - (window_x_size / 2), y_size = (mode->height / 2) - (window_y_size / 2);

    glfwSetWindowPos(window, x_size + monitor_x_pos, y_size + monitor_y_pos);
    glfwSetWindowSize(window, main_window->data.size.x, main_window->data.size.y);

    main_window->current_size.x = window_x_size;
    main_window->current_size.y = window_y_size;
}

void platform_window_create(window* window) {
    window->platform_window = malloc(sizeof(struct platform_window));

    if (!glfwInit())
        printf("Failed to initlize GLFW\n");
    
    window->platform_window->window = glfwCreateWindow(100, 100, "test", NULL, NULL);

    if (!window->platform_window->window)
        printf("Window failed to open\n");
    glfwHideWindow(window->platform_window->window);

    window_update_data(window);
    window_update_properties(window);

    if (window->properties.is_maximized)
        glfw_maximize_window(window);
}

void platform_window_open(window* window) {
    glfwShowWindow(window->platform_window->window);
}

void platform_window_update(window* window) {
    glfwMakeContextCurrent(window->platform_window->window);

    glfwSwapBuffers(window->platform_window->window);
    glfwPollEvents();

    if (glfwWindowShouldClose(window->platform_window->window)) window->is_open = false;
}

void platform_window_close(window* window) {
    glfwDestroyWindow(window->platform_window->window);
}

void platform_window_set_size(window* window, int width, int height) {
    if (window->properties.is_maximized)
        return;

    glfwSetWindowSize(window->platform_window->window, width, height);
    window->current_size.x = width;
    window->current_size.y = width;
}
void platform_window_set_title(window* window, char* title) { glfwSetWindowTitle(window->platform_window->window, title); }

void platform_window_set_resizable(window* window, bool resizable) {
    if (resizable || window->properties.is_maximized)
        return;
    
    glfwSetWindowSizeLimits(window->platform_window->window, window->data.size.x, window->data.size.y, window->data.size.x, window->data.size.y);
    glfwSetWindowSize(window->platform_window->window, window->data.size.x, window->data.size.y);
}
void platform_window_set_maximized(window* window, bool maximized) { 
    printf("\n\n%i\n\n", maximized);

    glfwSetWindowAttrib(window->platform_window->window, GLFW_MAXIMIZED, maximized); 
    if (maximized)
        glfw_maximize_window(window);
    else {
        glfw_unmaximize_window(window);
    }
}

#endif
