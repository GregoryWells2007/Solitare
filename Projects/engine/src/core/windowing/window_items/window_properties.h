#pragma once
#include "engine_api.h"

typedef struct window_properties {
    bool is_resizable;
    bool is_maximized;

    bool is_shown;

    bool is_decorated;
} window_properties;

HEADER_DEF void window_properties_set_resizable(window_properties* data, bool value) { data->is_resizable = value; }
HEADER_DEF void window_properties_set_maximized(window_properties* data, bool value) { data->is_maximized = value; }
HEADER_DEF void window_properties_set_shown(window_properties* data, bool value) { data->is_shown = value; }
HEADER_DEF void window_properties_set_decorated(window_properties* data, bool value) { data->is_decorated = value; }