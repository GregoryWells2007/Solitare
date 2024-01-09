#pragma once
#include "engine.h"
#include "game/board/board.h"

typedef struct board_renderer {
    mesh board_mesh;
    shader board_shader;
} board_renderer;

void init_board_renderer(board_renderer* renderer);
void draw_board(board_renderer* renderer, board* board);