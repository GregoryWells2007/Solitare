#pragma once

typedef enum texture_2d_parameter {
    texture_2d_magnification_filter, texture_2d_minification_filter,
    texture_2d_wrap_x, texture_2d_wrap_y,

    texture_2d_parameter_none
} texture_2d_parameter;

typedef enum texture_2d_parameter_value {
    texture_2d_filter_nearest, texture_2d_filter_linear,
    texture_2d_wrap_repeat, texture_2d_wrap_clamp,
    
    texture_2d_parameter_value_none
} texture_2d_parameter_value;

typedef enum texture_2d_color_mode {
    RGBA, texture_2d_color_mode_none
} texture_2d_color_mode;