#ifndef EXPRESSION_H
#define EXPRESSION_H

#include "expr_tokens.h"
#include "list64.h"

int parse_expr(char* string, expr_token_list* expr);

int eval_expr(expr_token_list* expr, list64* result);

void free_expr(expr_token_list* expr);

#endif