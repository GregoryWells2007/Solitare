#include "engine_api.h"

#if RAPI == RAPI_OPENGL
#include "src/core/rendering/utils/screen_clearing.h"
#include "glad/glad.h"

void platform_set_screen_color(color col) {
    glClearColor(col.r / 255.0f, col.g / 255.0f, col.b / 255.0f, col.a);
}

void platform_clear_screen(screen_layer* layers, int count) {
    GLbitfield mask = GL_COLOR_BUFFER_BIT;

    // im fucking lazy so this shit needs to be made faster later

    glClear(mask);
}

#endif