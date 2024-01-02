#pragma once

typedef struct shader_data {
    char* fragment_data;
    char* vertex_data;
} shader_data;

typedef struct shader {
    unsigned int programID;
} shader;

shader_data load_shader_data_from_file(char* path_to_vertex, char* path_to_fragment);
shader create_shader(shader_data data);