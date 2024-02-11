#pragma once
#include "engine.h"

struct board_rendering_data {
    texture_2d board_background_image;
};

typedef struct board {
    char* background_image;
    struct board_rendering_data board_rendering_data;
} board;