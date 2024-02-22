#include "input_manager.h"

void input_manager_set_mouse_pos(input_manager* manager, ivec2 mouse_pos) {
    manager->mouse_position = mouse_pos;
}   

ivec2 input_manager_get_mouse_pos(input_manager* manager) { return manager->mouse_position; }

void input_manager_click_mouse(input_manager* manager) {
    manager->mouse_clicked = true;
    manager->mouse_down = true;
}
void input_manager_release_mouse(input_manager* manager) {
    manager->mouse_up = true;
}