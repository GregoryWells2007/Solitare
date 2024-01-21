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

void platform_window_create(window* window) {
    window->platform_window = malloc(sizeof(struct platform_window));

    if (!glfwInit())
        printf("Failed to initlize GLFW\n");

    glfwWindowHint(GLFW_RESIZABLE, window->properties.is_resizable);
    
    window->platform_window->window = glfwCreateWindow(window->data.size.x, window->data.size.y, window->data.title, NULL, NULL);
    if (window->properties.is_maximized) {
        glfwSetWindowAttrib(window->platform_window->window, GLFW_DECORATED, GLFW_FALSE);
        GLFWmonitor* monitor = get_current_monitor(window->platform_window->window);

        int x_pos, y_pos;
        glfwGetMonitorPos(monitor, &x_pos, &y_pos);
        
        const GLFWvidmode* mode = glfwGetVideoMode(monitor);
        int x_size = mode->width, y_size = mode->height;

        glfwSetWindowPos(window->platform_window->window, x_pos, y_pos);
        glfwSetWindowSize(window->platform_window->window, x_size, y_size);
        
    }


    if (!window->platform_window->window)
        printf("Window failed to open\n");
    glfwHideWindow(window->platform_window->window);
    
    //glfwSetWindowAttrib(window->platform_window->window, GLFW_RESIZABLE, GLFW_FALSE);
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

void platform_window_set_size(window* window, int width, int height) { if (!window->properties.is_maximized) glfwSetWindowSize(window->platform_window->window, width, height); }
void platform_window_set_title(window* window, char* title) { glfwSetWindowTitle(window->platform_window->window, title ); }

void platform_window_set_resizable(window* window, bool resizable) {}
void platform_window_set_maximized(window* window, bool maximized) {}

#endif
