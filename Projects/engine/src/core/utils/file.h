#pragma once
#include "engine_api.h"
#include "stdlib.h"
#include "string.h"

typedef struct file {
    char* data;
    int line_count;
} file;

HEADER_DEF file file_load_from_path(char* path) {
    FILE *fptr = fopen(path,"r");
    if (fptr == NULL) {
        printf("File failed to load\n");
        return (file){ };
    }

    char * line = NULL;
    char* file_content = NULL; 
    size_t len = 0;
    ssize_t read;

    file new_file = (file){ };
    new_file.data = NULL;
    new_file.line_count = 0;

    while ((read = getline(&line, &len, fptr)) != -1) {
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

        new_file.line_count++;
    }

    new_file.data = file_content;

    fclose(fptr);
    if (line)
        free(line);

    return new_file;
}

HEADER_DEF char* file_get_data(file* file) { return file->data; }