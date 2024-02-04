#pragma once
#include "engine_api.h"
#include "stdlib.h"

#define GROWTH_FACTOR 2

typedef struct array_list {
    void** data;
    int max_item_count;
    int size;
} array_list;

HEADER_DEF array_list array_list_create() {
    array_list new_array_list = (array_list){ };
    new_array_list.data = malloc(sizeof(void*) * GROWTH_FACTOR);
    new_array_list.max_item_count = GROWTH_FACTOR;
    new_array_list.size = 0;
    return new_array_list;
}

HEADER_DEF void array_list_resize(array_list* list) {
    list->max_item_count *= GROWTH_FACTOR;
    list->data = realloc(list->data, sizeof(void*) * list->max_item_count);
}

HEADER_DEF void array_list_add(array_list* list, void* data) {
    list->data[list->size] = data;
    list->size++;
    
    if (list->size == list->max_item_count)
        array_list_resize(list); 
}
HEADER_DEF void array_list_insert(array_list* list, int index, void* data) {

    for (int i = list->size; i > index; i--) {
        list->data[i] = list->data[i - 1];
    }

    list->data[index] = data;
    list->size++;

    if (list->size == list->max_item_count)
        array_list_resize(list);
}
HEADER_DEF void array_list_remove(array_list* list, int index) { 
    list->data[index] = NULL; 

    for (int i = index; i < list->size; i++) {
        list->data[i] = list->data[i + 1];
    }
    list->size--;
}
HEADER_DEF void array_list_clear(array_list* list) { list->size = 0; } 
HEADER_DEF void* array_list_get(array_list* list, int index) { return list->data[index]; };
HEADER_DEF int array_list_size(array_list* list) { return list->size; }