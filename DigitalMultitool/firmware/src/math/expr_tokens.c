#include "expr_tokens.h"
#include <stdlib.h>

void init_tokenlist(expr_token_list* list) {
    list->head = NULL;
    list->tail = NULL;
}

int push_token(expr_token_list* list, expr_token data) {
    expr_token_node* node = (expr_token_node*) malloc(sizeof(expr_token_node));
    if (node == NULL) return 0;
    node->data = data;
    node->next = list->head;
    list->head = node;
    if (list->tail == NULL) list->tail = node;
    return 1;
}

int queue_token(expr_token_list* list, expr_token data) {
    expr_token_node* node = (expr_token_node*) malloc(sizeof(expr_token_node));
    if (node == NULL) return 0;
    node->data = data;
    node->next = NULL;
    if (list->tail == NULL) {
        list->head = node;
    } else {
        list->tail->next = node;
    }
    list->tail = node;
    return 1;
}

int pop_token(expr_token_list* list, expr_token* element) {
    expr_token_node* node = list->head;
    if (node == NULL) return 0;
    if (element != NULL) *element = node->data;
    if (node->next == NULL) {
        list->tail = NULL; //empty list then
    }
    list->head = node->next;
    free(node);
    return 1;
}

int get_first_token(expr_token_list* list, expr_token* element) {
    if (list->head == NULL) return 0;
    *element = list->head->data;
    return 1;
}

int get_last_token(expr_token_list* list, expr_token* element) {
    if (list->tail == NULL) return 0;
    *element = list->tail->data;
    return 1;
}

void join_tokenlists(expr_token_list* first, expr_token_list* second) {
    if (first->head == NULL) {
        *first = *second;
        return;
    }
    if (second->head == NULL) return;
    first->tail->next = second->head;
    first->tail = second->tail;
}

int is_tokenlist_empty(expr_token_list* list) {
    return list->head == NULL;
}

void clear_tokenlist(expr_token_list* list) {
    if (list->head != NULL) {
        expr_token_node* node;
        expr_token_node* next = list->head;
        do {
            node = next;
            next = node->next;
            free(node);
        } while (next != NULL);
    }
    init_tokenlist(list);
}