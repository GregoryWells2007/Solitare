#include "engine_api.h"

#if OS == OS_LINUX
#include "GLFW/glfw3.h"

void platform_init() {
    if (!glfwInit())
        printf("Failed to initlize GLFW\n");
}

#endif