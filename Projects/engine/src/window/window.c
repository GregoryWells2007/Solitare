#include "glad/glad.h"
#include "window.h"
#include "stdio.h"
#include "stdlib.h"

void init_windows() {
    if (!glfwInit())
        printf("GLFW initilization failed\n");
}
void close_windows() {
    glfwTerminate();
}
void update_windows() {
    glfwPollEvents();
}

void init_opengl() {
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        printf("GLAD initilization failed\n");
}

static void cursor_position_callback(GLFWwindow* win, double xpos, double ypos) {
    input_manager* input = glfwGetWindowUserPointer(win);
    set_mouse_pos(input, (vector2){xpos, ypos});
}

static void mouse_clicked_callback(GLFWwindow* win, int button, int action, int mods) {
    input_manager* input = glfwGetWindowUserPointer(win);
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
        input->mouse_down = true;
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
        input->mouse_down = false;


    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
        input->right_mouse_down = true;
    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE)
        input->right_mouse_down = false;
}


window create_window(window_data data) {
    GLFWwindow* glfw_window = glfwCreateWindow(data.sizeX, data.sizeY, data.name, NULL, NULL);
    if (!glfw_window) {
        printf("GLFW window creation failed\n");
        glfwTerminate();
    }

    glfwMakeContextCurrent(glfw_window);

    glfwSetCursorPosCallback(glfw_window, cursor_position_callback);
    glfwSetMouseButtonCallback(glfw_window, mouse_clicked_callback);

    // int max_width  = GetSystemMetrics(SM_CXSCREEN);
    // int max_hieght = GetSystemMetrics(SM_CYSCREEN);

    // glfwSetWindowMonitor(window, NULL, (max_width/2)-(width/2), (max_hieght/2) - (height/2), width, height, GLFW_DONT_CARE);

    window new_window = {};
    new_window.window = glfw_window;
    new_window.input = malloc(sizeof(input_manager));
    new_window.input->mouse_position.x = 10;
    new_window.input->mouse_position.y = 100;

    glfwSetWindowUserPointer(glfw_window, (void*)new_window.input);

    return new_window;
}

void clear_window(window* window, color window_color) {
    glfwMakeContextCurrent(window->window);
    glClearColor(window_color.r / 255.0f, window_color.g / 255.0f, window_color.b / 255.0f, window_color.a);
    glClear(GL_COLOR_BUFFER_BIT);
}
void draw_window(window* window) {
    glfwMakeContextCurrent(window->window);
    glfwSwapBuffers(window->window);
}
int isOpen(window* window) {
    return !glfwWindowShouldClose(window->window);
}

input_manager* get_input_manager(window* window) {
    return window->input;
}

float get_time() {
    return glfwGetTime();
}