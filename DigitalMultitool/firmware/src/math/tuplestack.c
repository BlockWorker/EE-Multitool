#include "tuplestack.h"
#include <stdlib.h>

void tuplestack_init(tuple_stack* stack) {
    stack->head = NULL;
}

int tuplestack_push_one(tuple_stack* stack, expr_token val) {
    tuple_node* node = (tuple_node*)malloc(sizeof(tuple_node));
    if (node == NULL) return 0;
    init_tokenlist(&node->data);
    if (!queue_token(&node->data, val)) return 0;
    node->count = 1;
    node->next = stack->head;
    stack->head = node;
    return 1;
}

int tuplestack_push_two(tuple_stack* stack, expr_token val1, expr_token val2) {
    tuple_node* node = (tuple_node*)malloc(sizeof(tuple_node));
    if (node == NULL) return 0;
    init_tokenlist(&node->data);
    if (!queue_token(&node->data, val1)) return 0;
    if (!queue_token(&node->data, val2)) return 0;
    node->count = 2;
    node->next = stack->head;
    stack->head = node;
    return 1;
}

int tuplestack_push_list(tuple_stack* stack, expr_token_list* list, uint16_t count) {
    tuple_node* node = (tuple_node*)malloc(sizeof(tuple_node));
    if (node == NULL) return 0;
    init_tokenlist(&node->data);
    expr_token_node* tn = list->head;
    while (tn != NULL) {
        if (!queue_token(&node->data, tn->data)) return 0;
        tn = tn->next;
    }
    node->count = count;
    node->next = stack->head;
    stack->head = node;
    return 1;
}

int tuplestack_appendtop(tuple_stack* stack, expr_token val) {
    tuple_node* node = stack->head;
    if (node == NULL) return tuplestack_push_one(stack, val);
    if (!queue_token(&node->data, val)) return 0;
    node->count++;
    return 1;
}

int tuplestack_pop(tuple_stack* stack, expr_token_list** list, uint16_t* count) {
    tuple_node* node = stack->head;
    if (node == NULL) return 0;
    *list = malloc(sizeof(expr_token_list));
    if (*list == NULL) return 0;
    **list = node->data;
    *count = node->count;
    stack->head = node->next;
    free(node);
    return 1;
}

int tuplestack_top(tuple_stack* stack, expr_token_list** list, uint16_t* count) {
    tuple_node* node = stack->head;
    if (node == NULL) return 0;
    *list = &node->data;
    *count = node->count;
    return 1;
}

int tuplestack_is_empty(tuple_stack* stack) {
    return stack->head == NULL;
}

void tuplestack_clear(tuple_stack* stack) {
    if (stack->head != NULL) {
        tuple_node* node;
        tuple_node* next = stack->head;
        do {
            node = next;
            next = node->next;
            clear_tokenlist(&node->data);
            free(node);
        } while (next != NULL);
    }
    tuplestack_init(stack);
}