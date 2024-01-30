#include "engine_api.h"

#if RAPI == RAPI_OPENGL
#include "src/core/rendering/textures/texture_2d/texture_2d.h"

struct platform_texture_2d {
    unsigned int rendererID;
};
void platform_texture_2d_generate(texture_2d* texture) {

}
void platform_texture_2d_set_param(texture_2d_parameter param, texture_2d_parameter_value input) {

}
void platform_texture_2d_bind(texture_2d* texture, int slot) {

}
void platform_texture_2d_set_data(texture_2d* texture) {
    
}

#endif