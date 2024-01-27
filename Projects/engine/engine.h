#pragma once

#include "src/platform/platform.h"
#include "src/types/vector2.h"
#include "src/types/vector3.h"

// window includes
#include "src/core/windowing/window_manager.h"
#include "src/core/windowing/window.h"

// rendering includes
#include "src/core/rendering/output_buffer/output_buffer.h"

#include "engine_api.h"
HEADER_DEF void engine_init() {
    platform_init();
}