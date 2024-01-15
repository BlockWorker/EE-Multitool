#ifndef _TUPLESTACK_H
#define _TUPLESTACK_H

#include "expr_tokens.h"

typedef struct tuplenode {
    expr_token_list data;
    uint16_t count;
    struct tuplenode* next;
} tuple_node;

typedef struct {
    tuple_node* head;
} tuple_stack;

void tuplestack_init(tuple_stack* stack);
int tuplestack_push_one(tuple_stack* stack, expr_token val);
int tuplestack_push_two(tuple_stack* stack, expr_token val1, expr_token val2);
int tuplestack_push_list(tuple_stack* stack, expr_token_list* list, uint16_t count);
int tuplestack_appendtop(tuple_stack* stack, expr_token val);
int tuplestack_pop(tuple_stack* stack, expr_token_list** list, uint16_t* count);
int tuplestack_top(tuple_stack* stack, expr_token_list** list, uint16_t* count);
int tuplestack_is_empty(tuple_stack* stack);
void tuplestack_clear(tuple_stack* stack);

#endif