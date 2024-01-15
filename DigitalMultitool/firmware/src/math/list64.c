#include "list64.h"
#include <stdlib.h>

void list64_init(list64* list) {
    list->head = NULL;
    list->tail = NULL;
}

int list64_push_s(list64* list, int64_t data) {
    list64_node* node = (list64_node*) malloc(sizeof(list64_node));
    if (node == NULL) return 0;
    node->data.s64 = data;
    node->next = list->head;
    list->head = node;
    if (list->tail == NULL) list->tail = node;
    return 1;
}

int list64_push_u(list64* list, uint64_t data) {
    list64_node* node = (list64_node*) malloc(sizeof(list64_node));
    if (node == NULL) return 0;
    node->data.u64 = data;
    node->next = list->head;
    list->head = node;
    if (list->tail == NULL) list->tail = node;
    return 1;
}

int list64_push_f(list64* list, double data) {
    list64_node* node = (list64_node*) malloc(sizeof(list64_node));
    if (node == NULL) return 0;
    node->data.f64 = data;
    node->next = list->head;
    list->head = node;
    if (list->tail == NULL) list->tail = node;
    return 1;
}

int list64_queue_s(list64* list, int64_t data) {
    list64_node* node = (list64_node*) malloc(sizeof(list64_node));
    if (node == NULL) return 0;
    node->data.s64 = data;
    node->next = NULL;
    if (list->tail == NULL) {
        list->head = node;
    } else {
        list->tail->next = node;
    }
    list->tail = node;
    return 1;
}

int list64_queue_u(list64* list, uint64_t data) {
    list64_node* node = (list64_node*) malloc(sizeof(list64_node));
    if (node == NULL) return 0;
    node->data.u64 = data;
    node->next = NULL;
    if (list->tail == NULL) {
        list->head = node;
    } else {
        list->tail->next = node;
    }
    list->tail = node;
    return 1;
}

int list64_queue_f(list64* list, double data) {
    list64_node* node = (list64_node*) malloc(sizeof(list64_node));
    if (node == NULL) return 0;
    node->data.f64 = data;
    node->next = NULL;
    if (list->tail == NULL) {
        list->head = node;
    } else {
        list->tail->next = node;
    }
    list->tail = node;
    return 1;
}

int list64_pop_s(list64* list, int64_t* element) {
    list64_node* node = list->head;
    if (node == NULL) return 0;
    if (element != NULL) *element = node->data.s64;
    if (node->next == NULL) {
        list->tail = NULL; //empty list then
    }
    list->head = node->next;
    free(node);
    return 1;
}

int list64_pop_u(list64* list, uint64_t* element) {
    list64_node* node = list->head;
    if (node == NULL) return 0;
    if (element != NULL) *element = node->data.u64;
    if (node->next == NULL) {
        list->tail = NULL; //empty list then
    }
    list->head = node->next;
    free(node);
    return 1;
}

int list64_pop_f(list64* list, double* element) {
    list64_node* node = list->head;
    if (node == NULL) return 0;
    if (element != NULL) *element = node->data.f64;
    if (node->next == NULL) {
        list->tail = NULL; //empty list then
    }
    list->head = node->next;
    free(node);
    return 1;
}

int list64_get_first_s(list64* list, int64_t* element) {
    if (list->head == NULL) return 0;
    *element = list->head->data.s64;
    return 1;
}

int list64_get_first_u(list64* list, uint64_t* element) {
    if (list->head == NULL) return 0;
    *element = list->head->data.u64;
    return 1;
}

int list64_get_first_f(list64* list, double* element) {
    if (list->head == NULL) return 0;
    *element = list->head->data.f64;
    return 1;
}

int list64_get_last_s(list64* list, int64_t* element) {
    if (list->tail == NULL) return 0;
    *element = list->tail->data.s64;
    return 1;
}

int list64_get_last_u(list64* list, uint64_t* element) {
    if (list->tail == NULL) return 0;
    *element = list->tail->data.u64;
    return 1;
}

int list64_get_last_f(list64* list, double* element) {
    if (list->tail == NULL) return 0;
    *element = list->tail->data.f64;
    return 1;
}

void list64_join(list64* first, list64* second) {
    if (first->head == NULL) {
        *first = *second;
        return;
    }
    if (second->head == NULL) return;
    first->tail->next = second->head;
    first->tail = second->tail;
}

int list64_is_empty(list64* list) {
    return list->head == NULL ? 1 : 0;
}

void list64_clear(list64* list) {
    if (list->head != NULL) {
        list64_node* node;
        list64_node* next = list->head;
        do {
            node = next;
            next = node->next;
            free(node);
        } while (next != NULL);
    }
    list64_init(list);
}