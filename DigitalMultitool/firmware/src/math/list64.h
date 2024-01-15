#ifndef LIST64_H
#define LIST64_H

#include <stdint.h>

typedef struct l64node {
    union {
        int64_t s64;
        uint64_t u64;
        double f64;
    } data;
    struct l64node* next;
} list64_node;

typedef struct {
    list64_node* head;
    list64_node* tail;
} list64;

void list64_init(list64* list);
int list64_push_s(list64* list, int64_t data);
int list64_push_u(list64* list, uint64_t data);
int list64_push_f(list64* list, double data);
int list64_queue_s(list64* list, int64_t data);
int list64_queue_u(list64* list, uint64_t data);
int list64_queue_f(list64* list, double data);
int list64_pop_s(list64* list, int64_t* element);
int list64_pop_u(list64* list, uint64_t* element);
int list64_pop_f(list64* list, double* element);
int list64_get_first_s(list64* list, int64_t* element);
int list64_get_first_u(list64* list, uint64_t* element);
int list64_get_first_f(list64* list, double* element);
int list64_get_last_s(list64* list, int64_t* element);
int list64_get_last_u(list64* list, uint64_t* element);
int list64_get_last_f(list64* list, double* element);
void list64_join(list64* first, list64* second);
int list64_is_empty(list64* list);
void list64_clear(list64* list);

#endif