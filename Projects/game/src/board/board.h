#pragma once
#include "engine.h"

struct board_rendering_data {
    texture_2d board_background_image;
    texture_2d board_areas_image;
};

typedef struct board_area {
    ivec2 position;
    int card_index;
} board_area;

typedef struct board {
    char* background_image;
    char* areas_image;

    array_list areas;

    struct board_rendering_data board_rendering_data;
} board;