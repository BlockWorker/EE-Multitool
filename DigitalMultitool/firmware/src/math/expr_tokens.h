#ifndef EXPR_TOKENS_H
#define EXPR_TOKENS_H

#include <stdint.h>

//****** TOKEN KEY ******//
// types:  0 = number, 1 = operator, 2 = bracket, 3 = variable, 4 = function, 5 = postfix function
// operator format:  bits 63-4 = index, bit 3 = right associative?, bits 2-0 = precedence
// brackets:  0 = opening, 1 = closing
// function:  bits 63-4 = index, bit 3 = right associative? (1 for most funcs), bits 2-0 = precedence (7 for most funcs)

#define op_func_id(t) (((t).info.longVal & 0xfffffffffffffff0ul) >> 4)
#define op_rass(t) (((t).info.longVal & 0x8ul) >> 3)
#define op_func_prec(t) ((t).info.longVal & 0x7ul)

#define TOKEN_NUM 0
#define TOKEN_OP 1
#define TOKEN_BR 2
#define TOKEN_VAR 3
#define TOKEN_FUNC 4
#define TOKEN_POSTFIX 5
#define TOKEN_VARPTR 6

#define OP_ADD 0x02
#define OP_SUB 0x12
#define OP_MUL 0x23
#define OP_DIV 0x33
#define OP_MOD 0x43
#define OP_POW 0x5d
#define OP_COMMA 0x61
#define OP_STORE 0x70

#define BR_OPEN 0
#define BR_CLOSE 1

#define FUNC_NEG 0x0c
#define FUNC_ABS 0x1f
#define FUNC_ACOS 0x2f
#define FUNC_ACOSH 0x3f
#define FUNC_ASIN 0x4f
#define FUNC_ASINH 0x5f
#define FUNC_ATAN 0x6f
#define FUNC_ATANH 0x7f
#define FUNC_COS 0x8f
#define FUNC_COSH 0x9f
#define FUNC_SIN 0xaf
#define FUNC_SINH 0xbf
#define FUNC_TAN 0xcf
#define FUNC_TANH 0xdf
#define FUNC_EXP 0xef
#define FUNC_LN 0xff
#define FUNC_LOG 0x10f
#define FUNC_FRAC 0x11f
#define FUNC_SQRT 0x12f
#define FUNC_CBRT 0x13f
#define FUNC_CEIL 0x14f
#define FUNC_FLOOR 0x15f

#define POSTFIX_FACT 0x1000

typedef struct {
    int8_t _type;
    union {
        double doubleVal;
        uint64_t longVal;
    } info;
} expr_token;

typedef struct tnode {
    expr_token data;
    struct tnode* next;
} expr_token_node;

typedef struct {
    expr_token_node* head;
    expr_token_node* tail;
} expr_token_list;

void init_tokenlist(expr_token_list* list);
int push_token(expr_token_list* list, expr_token data);
int queue_token(expr_token_list* list, expr_token data);
int pop_token(expr_token_list* list, expr_token* element);
int get_first_token(expr_token_list* list, expr_token* element);
int get_last_token(expr_token_list* list, expr_token* element);
void join_tokenlists(expr_token_list* first, expr_token_list* second);
int is_tokenlist_empty(expr_token_list* list);
void clear_tokenlist(expr_token_list* list);

#endif