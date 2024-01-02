#include "stdio.h"
#include "window/window.h"


int main(int argc, char** argv) {
    init_window();

    GLFWwindow* window = glfwCreateWindow(1280, 720, "Solitare AI", NULL, NULL);
    if (!window) {
        printf("GLFW window creation failed\n");
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    while (!glfwWindowShouldClose(window)) {
        glClearColor(38 / 255.0f, 162 / 255.0f, 105 / 255.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    close_window();
    return 0;
}