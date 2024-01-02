#include "glad/glad.h"
#include "window.h"
#include "stdio.h"

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

window create_window(window_data data) {
    GLFWwindow* glfw_window = glfwCreateWindow(1280, 720, "Solitare AI", NULL, NULL);
    if (!glfw_window) {
        printf("GLFW window creation failed\n");
        glfwTerminate();
    }

    glfwMakeContextCurrent(glfw_window);

    window new_window = {};
    new_window.window = glfw_window;
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