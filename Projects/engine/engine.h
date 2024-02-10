#pragma once

// types
#include "src/platform/platform.h"
#include "src/types/vector2.h"
#include "src/types/vector3.h"
#include "src/types/vector4.h"
#include "src/types/color.h"
#include "src/types/array_list.h"

// window includes
#include "src/core/windowing/window_manager.h"
#include "src/core/windowing/window.h"

// rendering includes
#include "src/core/rendering/meshing/vertex_array.h"
#include "src/core/rendering/utils/screen_clearing.h"
#include "src/core/rendering/shaders/shader_program.h"
#include "src/core/rendering/textures/texture_2d/texture_2d.h"
#include "src/core/rendering/framebuffer/framebuffer.h"
#include "src/core/rendering/framebuffer/renderbuffer/renderbuffer.h"

// util includes
#include "src/core/utils/file.h"
#include "src/core/utils/texture_file.h"
#include "src/core/utils/camera.h"
#include "src/core/utils/transform.h"

#include "engine_api.h"
HEADER_DEF void engine_init() {
    platform_init();
}