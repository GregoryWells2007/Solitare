#include "engine_api.h"

#if OS == OS_LINUX

#if RAPI == RAPI_OPENGL
#include "glad/glad.h"
#endif

#include "src/core/windowing/window.h"
#include "GLFW/glfw3.h"


struct platform_window {
    GLFWwindow* window;
};

// imma rewite this shit later im just bored and kinda for forgot how this shit works
GLFWmonitor* glfw_get_window_monitor(window* main_window) {
    // GLFWwindow* window = main_window->platform_window->window;

    // int monitor_count = 0;
    // GLFWmonitor** monitors = glfwGetMonitors(&monitor_count);

    // GLFWmonitor* closest = monitors[0];

    // int window_pos_x, window_pos_y;
    // //glfwGetWindowPos(window, &window_pos_x, &window_pos_y);

    // int window_size_x = main_window->current_size.x, window_size_y = main_window->current_size.y;

    // int window_bounds[4] = {
    //     window_pos_x, window_pos_y, window_pos_x + window_size_x, window_pos_y + window_size_y
    // };
    // //printf("window bounds: %i, %i, %i, %i\n", window_bounds[0], window_bounds[1], window_bounds[2], window_bounds[3]);

    // for (int i = 0; i < monitor_count; i++) {
    //     int monitor_x_pos, monitor_y_pos;
    //     glfwGetMonitorPos(monitors[i], &monitor_x_pos, &monitor_y_pos);

    //     const GLFWvidmode* mode = glfwGetVideoMode(monitors[i]);
    //     int monitor_x_size = mode->width, monitor_y_size = mode->height;

    //     int current_monitor_bounds[4] = {
    //         monitor_x_pos, monitor_y_pos, monitor_x_pos + monitor_x_size, monitor_y_pos + monitor_y_size
    //     };

    //     //printf("monitor bounds: %i, %i, %i, %i\n", current_monitor_bounds[0], current_monitor_bounds[1], current_monitor_bounds[2], current_monitor_bounds[3]);

    //     float percent_in = 0.0f;

    //     int pixels_over_left_bound = min(0, current_monitor_bounds[0] - window_bounds[0]);
    //     int pixels_over_right_bound = min(0, -(current_monitor_bounds[2] - window_bounds[2]));

    //     int pixels_over_top_bound = min(0, current_monitor_bounds[1] - window_bounds[1]);
    //     int pixels_over_bottom_bound = min(0, -(current_monitor_bounds[3] - window_bounds[3]));

    //     // printf("pixels over bounds: %i, %i, %i, %i\n", pixels_over_left_bound, pixels_over_right_bound, pixels_over_top_bound, pixels_over_bottom_bound);
    //     // printf("percent of window in mointor: %f\n\n", percent_in);
    // }

    // //printf("\n");

    // return closest;
    int monitor_count = 0;
    return glfwGetMonitors(&monitor_count)[0];
}

void glfw_maximize_window(window* main_window) {
    GLFWwindow* window = main_window->platform_window->window;

    glfwSetWindowAttrib(window, GLFW_DECORATED, GLFW_FALSE);
    GLFWmonitor* monitor = glfw_get_window_monitor(main_window);

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
    GLFWwindow* window = main_window->platform_window->window;

    glfwSetWindowAttrib(window, GLFW_DECORATED, GLFW_TRUE);
    GLFWmonitor* monitor = glfw_get_window_monitor(main_window);
    
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
    
    GLFWwindow* main_window = NULL;
    if (window->main_window)
        main_window = window->main_window->platform_window->window;

    glfwWindowHint(GLFW_RESIZABLE, window->properties.is_resizable);
    glfwWindowHint(GLFW_MAXIMIZED, window->properties.is_maximized);
    glfwWindowHint(GLFW_VISIBLE, window->properties.is_shown);
    GLFWmonitor* monitor = NULL;
    if (window->properties.is_maximized) {
        int monitor_count = 0;
        monitor = glfwGetMonitors(&monitor_count)[0];
        const GLFWvidmode* mode = glfwGetVideoMode(monitor);
        window->data.size.x = mode->width;
        window->data.size.y = mode->height;
    }
    window->platform_window->window = glfwCreateWindow(window->data.size.x, window->data.size.y, window->data.title, monitor, main_window);
    glfwMakeContextCurrent(window->platform_window->window);

    if (!window->platform_window->window)
        printf("Window failed to open\n");

    window_update_data(window);
    window_update_properties(window);
}

void platform_window_open(window* window) {
    #if RAPI == RAPI_OPENGL

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        printf("GLAD initilization failed\n");
    
    #endif
}

void platform_window_update(window* window) {
    glfwSwapBuffers(window->platform_window->window);
    glfwPollEvents();
    
    double xpos, ypos;
    glfwGetCursorPos(window->platform_window->window, &xpos, &ypos);
    xpos = -(window->data.size.x / 2) + xpos;
    ypos = -(window->data.size.y / 2) + ypos;

    input_manager_set_mouse_pos(window->input, (ivec2){ xpos, ypos });

    if (glfwWindowShouldClose(window->platform_window->window)) window->is_open = false;
}

void platform_window_prep_for_draw(window* window) {
    glfwMakeContextCurrent(window->platform_window->window);
}

void platform_window_close(window* window) {
    glfwDestroyWindow(window->platform_window->window);
}

void platform_window_set_size(window* window, int width, int height) {
    if (window->properties.is_maximized)
        return;

    glfwSetWindowSize(window->platform_window->window, width, height);
    window->data.size.x = width;
    window->data.size.y = width;
}
void platform_window_set_title(window* window, char* title) { glfwSetWindowTitle(window->platform_window->window, title); }

void platform_window_set_resizable(window* window, bool resizable) {
    if (resizable || window->properties.is_maximized)
        return;

    glfwSetWindowAttrib(window->platform_window->window, GLFW_RESIZABLE, window->properties.is_resizable);

    glfwSetWindowSizeLimits(window->platform_window->window, window->data.size.x, window->data.size.y, window->data.size.x, window->data.size.y);
    
}
void platform_window_set_maximized(window* window, bool maximized) { 
    glfwSetWindowAttrib(window->platform_window->window, GLFW_MAXIMIZED, maximized); 
    

    const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    window->data.size.x = mode->width;
    window->data.size.y = mode->height;

    glfwSetWindowMonitor(window->platform_window->window, glfwGetPrimaryMonitor(), 0, 0, mode->width, mode->height, mode->refreshRate);

    glfwSetWindowSize(window->platform_window->window, window->data.size.x, window->data.size.y);
    // if (maximized)
    //     glfw_maximize_window(window);
    // else {
    //     glfw_unmaximize_window(window);
    // }
}
void platform_window_set_decorated(window* window, bool decorated) {
    if (window->properties.is_maximized)
        return;
    
    glfwSetWindowAttrib(window->platform_window->window, GLFW_DECORATED, decorated); 
}

void platform_window_hide(window* window) {
    glfwHideWindow(window->platform_window->window);
}
void platform_window_show(window* window) {
    glfwShowWindow(window->platform_window->window);
}

#endif
