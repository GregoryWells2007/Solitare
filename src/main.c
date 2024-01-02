#include "stdio.h"
#include "mesh/mesh.h"
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

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        printf("GLAD initilization failed\n");
        return -1;
    }

    float card_mesh_positions[6] = {
        -0.5f, -0.5f,
         0.0f,  0.5f,
         0.5f, -0.5f 
    };

    mesh_data card_mesh_data = { card_mesh_positions, 6 };
    mesh card_mesh = create_mesh(card_mesh_data);

    while (!glfwWindowShouldClose(window)) {
        glClearColor(38 / 255.0f, 162 / 255.0f, 105 / 255.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        draw_mesh(&card_mesh);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    close_window();
    return 0;
}