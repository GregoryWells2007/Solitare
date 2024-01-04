#pragma once
#include "engine.h"

typedef struct card_renderer {
    mesh card_mesh;
    shader card_shader;
    camera card_camera;
} card_renderer;

void init_card_renderer(card_renderer* renderer);