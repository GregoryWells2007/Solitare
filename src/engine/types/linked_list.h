#pragma once

typedef struct linked_list {
    void* data;
    struct linked_list* next;
} linked_list;

linked_list linked_list_create();

void linked_list_add(linked_list* list, void* data);
void* linked_list_get(linked_list* list, int index);
void linked_list_set(linked_list* list, int index, void* data);
int linked_list_size(linked_list* list);