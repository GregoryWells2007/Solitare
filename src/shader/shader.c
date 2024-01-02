#include "shader.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include <unistd.h>
#include "glad/glad.h"

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

        // printf("{%s}", line);
    }

    fclose(fptr);
    if (line)
        free(line);


    return file_content;
}

shader_data load_shader_data_from_file(char* path_to_vertex, char* path_to_fragment) {
    char* vert_data = load_data_from_file(path_to_vertex);
    char* frag_data = load_data_from_file(path_to_fragment);

    shader_data data = {};
    data.vertex_data = vert_data;
    data.fragment_data = frag_data;
    return data;   
}

shader create_shader(shader_data data) {
    unsigned int program = glCreateProgram();
    long vertlen = strlen(data.vertex_data);
    long fraglen = strlen(data.fragment_data);

    // create vertex shader
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, (const GLchar *const *)&data.vertex_data, (const GLint *) &vertlen);
    glCompileShader(vertexShader);

    int result = 0;

    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE) {
        int length = 0;
        glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(length * sizeof(char));
        glGetShaderInfoLog(vertexShader, length, &length, message);
        printf("Failed to compile vertex shader\n");
        printf("Reason: {%s}", message);
    } else {
        printf("Vertex Shader compiled\n");
    }

    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, (const GLchar *const *)&data.fragment_data, (const GLint *) &fraglen);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE) {
        int length = 0;
        glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(length * sizeof(char));
        glGetShaderInfoLog(fragmentShader, length, &length, message);
        printf("Failed to compile fragment shader\n");
        printf("Reason: {%s}", message);
    } else {
        printf("Fragment Shader compiled\n");
    }

    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);

    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    printf("Vertex ID%i\n", program);

    shader new_shader = {};
    new_shader.programID = program;
    return new_shader;
}