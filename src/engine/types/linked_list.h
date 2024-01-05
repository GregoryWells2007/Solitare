#pragma once

typedef struct linked_list {
    void* data;
    linked_list* next;
} linked_list;

linked_list linked_list_create() {
    linked_list list = {};
    list->data = NULL;
    list->next = NULL;
    return list;
}

void linked_list_add(linked_list* list, void* data) {
    while (list->data != NULL)
        list = list->next;

    list->data = data;
    list->next = &linked_list_create();
}

void* linked_list_get(linked_list* list, int index) {
    while (index > 0) {
        list = list->next;
        index--;
    }
    return list->data;
}

void linked_list_set(linked_list* list, int index, void* data) {
    while (index > 0) {
        index--;
        list = list->next;
    }
    list->data = data;
}

int linked_list_size(linked_list* list) {
    int count = 0;
    if (list->data != NULL)
        count++;

    while (list->next != NULL) {
        count++;
        list = list->next;
    }

    return count;
}