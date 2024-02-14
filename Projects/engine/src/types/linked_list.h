#pragma once
#include "engine_api.h"

typedef struct linked_list {
    void* data;
    struct linked_list* next_node;
} linked_list;

HEADER_DEF linked_list linked_list_create() {
    linked_list new_linked_list = (linked_list) { };
    new_linked_list.data = NULL;
    new_linked_list.next_node = NULL;
    return new_linked_list;
}

HEADER_DEF void linked_list_add(linked_list* list, void* data) {
    list->next_node = malloc(sizeof(linked_list));
    list->next_node->next_node = NULL;
    list->next_node->data = NULL;
}
HEADER_DEF void linked_list_insert(linked_list* list, int index, void* data) {
    if (index == 0) {
        linked_list* new_linked_list = malloc(sizeof(linked_list));
        new_linked_list->data = list->data;
        new_linked_list->next_node = list->next_node;

        list->data = data;
        list->next_node = new_linked_list;
    }

    while (index > 1) {
        list = list->next_node;
        index--;
    }

    linked_list* new_linked_list = malloc(sizeof(linked_list));
    new_linked_list->data = data;
    new_linked_list->next_node = list->next_node;

    list->next_node = new_linked_list;
}
HEADER_DEF void linked_list_remove(linked_list* list, int index) { 
    if (index == 0) {
        list->data = list->next_node->data;
        list->next_node = list->next_node->next_node;
    }

    while (index > 1) {
        list = list->next_node;
        index--;
    }

    list->next_node = list->next_node->next_node;
}
HEADER_DEF void linked_list_clear(linked_list* list) { 
    list->next_node = NULL; 
    list->data = NULL;
} 
HEADER_DEF void* linked_list_get(linked_list* list, int index) { 
    while (index > 0) {
        list = list->next_node;
        index--;
    } 
    return list->data;
}
HEADER_DEF int linked_list_size(linked_list* list) { 
    int size = (list->data != NULL);
    list = list->next_node;
    while (list != NULL) {
        list = list->next_node;
        size++;
    }
    return size;
}