#include "board.h"

void create_background(board* board, char* path) {
    image new_image = load_image_from_file(path);
    set_bind_slot(&new_image, 1);

    board->board_image = new_image;
}