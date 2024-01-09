#pragma once
#include "engine.h"
#include "src/card/card.h"

typedef struct card_renderer {
    mesh card_mesh;
    shader card_shader;
    camera card_camera;
    image card_image;
} card_renderer;

void init_card_renderer(card_renderer* renderer);
void start_card_renderer_frame(card_renderer* renderer);
void draw_card(card_renderer* renderer, card* value);