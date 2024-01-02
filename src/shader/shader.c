#include "shader.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include <unistd.h>

char* load_data_from_file(char* path) {
    FILE *fptr = fopen(path,"r");
    char ch;
    if (fptr == NULL) {
        printf("File failed to load\n");
        return "Null\0";
    }

    char * line = NULL;
    char* file_content = NULL; 
    size_t len = 0;
    ssize_t read;

    while ((read = getline(&line, &len, fptr)) != -1) {
        //printf("Retrieved line of length %zu:\n", read);

        if (file_content == NULL) {
            file_content = malloc((strlen(line) * sizeof(char)));
            strcpy(file_content, line);
            file_content[strlen(line)] = '\0';
        } else {
            int strlength = strlen(file_content) + read;
            char* new_file_content = malloc((strlength * sizeof(char)) + 1);
            strcpy(new_file_content, file_content);
            strcat(new_file_content, line);
            new_file_content[strlength] = '\0';
            file_content = new_file_content;
        }

        printf("{%s}", line);
    }

    fclose(fptr);
    if (line)
        free(line);


    return file_content;
}

shader_data load_shader_data_from_file(char* path_to_vertex, char* path_to_fragment) {
    printf("Loading Vertex File\n");
    char* vert_data = load_data_from_file(path_to_vertex);
    printf("\nLoading Fragment File\n");
    char* frag_data = load_data_from_file(path_to_fragment);

    shader_data data = {};
    data.vertex_data = vert_data;
    data.fragment_data = path_to_fragment;
    return data;   
}

shader create_shader(shader_data data) {

    printf("Loading Shader\n"); 
    printf("Vertex Shader: {%s}\n", data.vertex_data);
    printf("Fragment Shader: {%s}\n", data.fragment_data);

    shader new_shader = {};
    return new_shader;
}