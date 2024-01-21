#include "stdio.h"
#include "engine.h"

int main(int argc, char** argv) {
    window main_window = window_create();

    window_data* main_window_data = window_get_data(&main_window); 
    window_data_set_name(main_window_data, "Main Window\0");
    window_data_set_size(main_window_data, (vector2){ 1920, 1080 });

    window_properties* main_window_properties = window_get_properties(&main_window); // imma add some properties later

    window_open(&main_window);

    while (window_is_open(&main_window)) {
        printf("updating window");
        window_update(&main_window);
    }
     
    window_close(&main_window);
}