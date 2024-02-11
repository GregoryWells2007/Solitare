#pragma once
#include "engine.h"

typedef struct card_renderer {
    shader_program card_shader;
} card_renderer;

void card_renderer_init(card_renderer* renderer);
void card_renderer_draw_card(card_renderer* renderer, transform2d position);
void card_renderer_cleanup(card_renderer* renderer);