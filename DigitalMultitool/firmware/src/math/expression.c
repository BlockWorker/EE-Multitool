#include "expression.h"
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "vars.h"
#include "tuplestack.h"
#include "mathext.h"

//int min(int a, int b) {
//    return a < b ? a : b;
//}

int parse_operator(char cur, expr_token* t, expr_token last_token, int start_of_expr) {
    switch (cur) {
        case '+':
            t->_type = TOKEN_OP;
            t->info.longVal = OP_ADD;
            return 1;
        case '-':
            if (start_of_expr != 0 ||                                                       //unary (negation) minus if at start of expr
                last_token._type == TOKEN_OP || last_token._type == TOKEN_FUNC ||           //or last token was operator or function
                (last_token._type == TOKEN_BR && last_token.info.longVal == BR_OPEN)) {      //or last token was opening bracket
                t->_type = TOKEN_FUNC;
                t->info.longVal = FUNC_NEG;
            } else { //operator (subtraction) minus
                t->_type = TOKEN_OP;
                t->info.longVal = OP_SUB;
            }
            return 1;
        case '*':
            t->_type = TOKEN_OP;
            t->info.longVal = OP_MUL;
            return 1;
        case '/':
            t->_type = TOKEN_OP;
            t->info.longVal = OP_DIV;
            return 1;
        case '%':
            t->_type = TOKEN_OP;
            t->info.longVal = OP_MOD;
            return 1;
        case '^':
            t->_type = TOKEN_OP;
            t->info.longVal = OP_POW;
            return 1;
        case ',':
            t->_type = TOKEN_OP;
            t->info.longVal = OP_COMMA;
            return 1;
        case '#': //TODO: temporary symbol
            t->_type = TOKEN_OP;
            t->info.longVal = OP_STORE;
            return 1;
        default:
            return 0;
    }
}

int add_operator(expr_token_list* expr, expr_token_list* opstack, expr_token op) {
    expr_token tos;
    while (get_first_token(opstack, &tos) != 0 && (tos._type == TOKEN_OP || tos._type == TOKEN_FUNC) &&      //top of stack exists and is function or operator...
      (op_func_prec(tos) > op_func_prec(op) || (op_func_prec(tos) == op_func_prec(op) && op_rass(tos) == 0))) {   //with higher prec, or equal prec and left associativity
        pop_token(opstack, &tos);
        if (queue_token(expr, tos) == 0) return 0;
    }
    if (push_token(opstack, op) == 0) return 0;
    return 1;
}

//for easy implied multiplication
int add_mul(expr_token_list* expr, expr_token_list* opstack) {
    expr_token mul;
    mul._type = TOKEN_OP;
    mul.info.longVal = OP_MUL;
    return add_operator(expr, opstack, mul);
}

int parse_func(char** str, expr_token* t) {
    switch (**str) {
        case 'a':
            if (strncmp(*str + 1, "bs", 2) == 0) {
                t->info.longVal = FUNC_ABS;
                *str += 3;
            } else if (strncmp(*str + 1, "cosh", 4) == 0) {
                t->info.longVal = FUNC_ACOSH;
                *str += 5;
            } else if (strncmp(*str + 1, "cos", 3) == 0) {
                t->info.longVal = FUNC_ACOS;
                *str += 4;
            } else if (strncmp(*str + 1, "sinh", 4) == 0) {
                t->info.longVal = FUNC_ASINH;
                *str += 5;
            } else if (strncmp(*str + 1, "sin", 3) == 0) {
                t->info.longVal = FUNC_ASIN;
                *str += 4;
            } else if (strncmp(*str + 1, "tanh", 4) == 0) {
                t->info.longVal = FUNC_ATANH;
                *str += 5;
            } else if (strncmp(*str + 1, "tan", 3) == 0) {
                t->info.longVal = FUNC_ATAN;
                *str += 4;
            } else return 0;
            break;
        case 'c':
            if (strncmp(*str + 1, "brt", 3) == 0) {
                t->info.longVal = FUNC_CBRT;
                *str += 4;
            } else if (strncmp(*str + 1, "osh", 3) == 0) {
                t->info.longVal = FUNC_COSH;
                *str += 4;
            } else if (strncmp(*str + 1, "os", 2) == 0) {
                t->info.longVal = FUNC_COS;
                *str += 3;
            } else if (strncmp(*str + 1, "eil", 3) == 0) {
                t->info.longVal = FUNC_CEIL;
                *str += 4;
            } else return 0;
            break;
        case 's':
            if (strncmp(*str + 1, "inh", 3) == 0) {
                t->info.longVal = FUNC_SINH;
                *str += 4;
            } else if (strncmp(*str + 1, "in", 2) == 0) {
                t->info.longVal = FUNC_SIN;
                *str += 3;
            } else if (strncmp(*str + 1, "qrt", 3) == 0) {
                t->info.longVal = FUNC_SQRT;
                *str += 4;
            } else return 0;
            break;
        case 't':
            if (strncmp(*str + 1, "anh", 3) == 0) {
                t->info.longVal = FUNC_TANH;
                *str += 4;
            } else if (strncmp(*str + 1, "an", 2) == 0) {
                t->info.longVal = FUNC_TAN;
                *str += 3;
            } else return 0;
            break;
        case 'e':
            if (*(*str + 1) == '^') {
                t->info.longVal = FUNC_EXP;
                *str += 2;
            } else return 0;
            break;
        case 'l':
            if (*(*str + 1) == 'n') {
                t->info.longVal = FUNC_LN;
                *str += 2;
            } else if (strncmp(*str + 1, "og", 2) == 0) {
                t->info.longVal = FUNC_LOG;
                *str += 3;
            } else return 0;
            break;
        case 'f':
            if (strncmp(*str + 1, "rac", 3) == 0) {
                t->info.longVal = FUNC_FRAC;
                *str += 4;
            } else if (strncmp(*str + 1, "loor", 4) == 0) {
                t->info.longVal = FUNC_FLOOR;
                *str += 5;
            } else return 0;
            break;
        default: return 0;
    }
    t->_type = TOKEN_FUNC;
    return 1;
}

int parse_postfix_func(char** str, expr_token* t) {
    switch (**str) {
        case '!':
            t->info.longVal = POSTFIX_FACT;
            *str += 1;
            break;
        default: return 0;
    }
    t->_type = TOKEN_POSTFIX;
    return 1;
}

int parse_var(char** str, expr_token* t) {
    char name[9];
    uint64_t key;
    int i;
    for (i = min(strlen(*str), 8); i > 0; i--) {
        memset(name, 0, 9);
        strncpy(name, *str, i);
        if (getKeyFromName(name, &key) && varExists(key)) {
            t->_type = TOKEN_VAR;
            t->info.longVal = key;
            *str += i;
            return 1;
        }
    }
    return 0;
}

int parse_expr(char* str, expr_token_list* expr) {
    if (expr == NULL) return 0;
    clear_tokenlist(expr);
    expr_token_list opstack;
    init_tokenlist(&opstack);
    
    char* cur = str;
    char* tmp;
    expr_token last_token;
    last_token._type = 0xff;
    last_token.info.longVal = 0;
    while (strlen(cur) > 0) {
        expr_token t;
        expr_token tos;
        
        if (last_token._type == TOKEN_VARPTR) {
            return 0; //var pointer only allowed at end of expression (store)
        } else if (last_token._type == TOKEN_OP && last_token.info.longVal == OP_STORE) {
            if ((*cur < 'A' || *cur > 'Z') && (*cur < 'a' || *cur > 'z') && *cur != '_') return 0; //invalid variable name start
            uint64_t key;
            if (!getKeyFromName(cur, &key)) return 0;
            if (varReserved(key)) return 0;
            t._type = TOKEN_VARPTR;
            t.info.longVal = key;
            if (!queue_token(expr, t)) return 0;
            cur += strlen(cur);
        } else if ((*cur >= '0' && *cur <= '9') || (*cur == '.' && *(cur + 1) >= '0' && *(cur + 1) <= '9')) {
            double num = strtod(cur, &tmp);
            if (last_token._type == TOKEN_VAR || (last_token._type == TOKEN_BR && last_token.info.longVal == BR_CLOSE) ||
              last_token._type == TOKEN_POSTFIX) {
                if (!add_mul(expr, &opstack)) return 0; //implied multiplication if number directly follows variable, closing bracket or postfix function
            }
            t._type = TOKEN_NUM;
            t.info.doubleVal = num;
            if (!queue_token(expr, t)) return 0;
            cur = tmp;
        } else if (parse_operator(*cur, &t, last_token, cur == str)) {
            if (!add_operator(expr, &opstack, t)) return 0;
            cur++;
        } else if (*cur == '(') {
            if (last_token._type == TOKEN_NUM || last_token._type == TOKEN_VAR ||
              (last_token._type == TOKEN_BR && last_token.info.longVal == BR_CLOSE) ||
              last_token._type == TOKEN_POSTFIX) {
                if(!add_mul(expr, &opstack)) return 0; //implied multiplication if opening bracket directly follows number, variable, closing bracket or postfix function
            }
            t._type = TOKEN_BR;
            t.info.longVal = BR_OPEN;
            if (!push_token(&opstack, t)) return 0;
            cur++;
        } else if (*cur == ')') {
            t._type = TOKEN_BR;
            t.info.longVal = BR_CLOSE;
            do {
                if (!pop_token(&opstack, &tos)) return 0; //missing left bracket
                if (tos._type != TOKEN_BR && !queue_token(expr, tos)) return 0;
            } while (tos._type != TOKEN_BR);
            cur++;
        } else if (parse_func(&cur, &t)) {
            if (last_token._type == TOKEN_NUM || last_token._type == TOKEN_VAR ||
              (last_token._type == TOKEN_BR && last_token.info.longVal == BR_CLOSE) ||
              last_token._type == TOKEN_POSTFIX) {
                if(!add_mul(expr, &opstack)) return 0; //implied multiplication if function directly follows number, variable, closing bracket or postfix function
            }
            if(!push_token(&opstack, t)) return 0;
        } else if (parse_postfix_func(&cur, &t)) {
            if(!queue_token(expr, t)) return 0;
        } else if (parse_var(&cur, &t)) {
            if (last_token._type == TOKEN_NUM || last_token._type == TOKEN_VAR ||
              (last_token._type == TOKEN_BR && last_token.info.longVal == BR_CLOSE) ||
              last_token._type == TOKEN_POSTFIX) {
                if(!add_mul(expr, &opstack)) return 0; //implied multiplication if variable directly follows number, variable, closing bracket or postfix function
            }
            if(!queue_token(expr, t)) return 0;
        } else {
            //invalid expr_token
            return 0;
        }
        
        last_token = t;
    }
    
    expr_token op;
    while (pop_token(&opstack, &op)) if (!queue_token(expr, op)) return 0;
    
    return 1;
}

int eval_operator(tuple_stack* stack, uint64_t op) {
    expr_token_list* val1, *val2;
    uint16_t cnt1, cnt2;
    if (!tuplestack_pop(stack, &val2, &cnt2)) return 0;
    if (!tuplestack_top(stack, &val1, &cnt1)) return 0;
    expr_token_node* cur1 = val1->head;
    expr_token_node* cur2 = val2->head;
    if (cur1 == NULL || cur2 == NULL) return 0;
    if (op != OP_COMMA) tuplestack_pop(stack, &val1, &cnt1);
    expr_token t1;
    int swapped = 0;
    switch (op) {
        case OP_ADD:
            //do first addition, push to stack
            if (cur1->data._type != TOKEN_NUM || cur2->data._type != TOKEN_NUM) return 0;
            t1._type = TOKEN_NUM;
            t1.info.doubleVal = cur1->data.info.doubleVal + cur2->data.info.doubleVal;
            if (!tuplestack_push_one(stack, t1)) return 0;
            cur1 = cur1->next;
            cur2 = cur2->next;
            //swap operands if required
            if (cnt1 < cnt2) {
                expr_token_node* n = cur2;
                cur2 = cur1;
                cur1 = n;
            }
            //add remaining operands, append
            while (cur2 != NULL) {
                if (cur1->data._type != TOKEN_NUM || cur2->data._type != TOKEN_NUM) return 0;
                expr_token t;
                t._type = TOKEN_NUM;
                t.info.doubleVal = cur1->data.info.doubleVal + cur2->data.info.doubleVal;
                if (!tuplestack_appendtop(stack, t)) return 0;
                cur1 = cur1->next;
                cur2 = cur2->next;
            }
            //append partnerless operands to result
            while (cur1 != NULL) {
                if (cur1->data._type != TOKEN_NUM) return 0;
                expr_token t;
                t._type = TOKEN_NUM;
                t.info.doubleVal = cur1->data.info.doubleVal;
                if (!tuplestack_appendtop(stack, t)) return 0;
                cur1 = cur1->next;
            }
            return 1;
        case OP_SUB:
            //do first subtraction, push to stack
            if (cur1->data._type != TOKEN_NUM || cur2->data._type != TOKEN_NUM) return 0;
            t1._type = TOKEN_NUM;
            t1.info.doubleVal = cur1->data.info.doubleVal - cur2->data.info.doubleVal;
            if (!tuplestack_push_one(stack, t1)) return 0;
            cur1 = cur1->next;
            cur2 = cur2->next;
            //swap operands if required
            if (cnt1 < cnt2) {
                expr_token_node* n = cur2;
                cur2 = cur1;
                cur1 = n;
                swapped = 1;
            }
            //subtract remaining operands, append
            while (cur2 != NULL) {
                if (cur1->data._type != TOKEN_NUM || cur2->data._type != TOKEN_NUM) return 0;
                expr_token t;
                t._type = TOKEN_NUM;
                if (swapped) t.info.doubleVal = cur2->data.info.doubleVal - cur1->data.info.doubleVal;
                else t.info.doubleVal = cur1->data.info.doubleVal - cur2->data.info.doubleVal;
                if (!tuplestack_appendtop(stack, t)) return 0;
                cur1 = cur1->next;
                cur2 = cur2->next;
            }
            //append partnerless operands to result
            while (cur1 != NULL) {
                if (cur1->data._type != TOKEN_NUM) return 0;
                expr_token t;
                t._type = TOKEN_NUM;
                if (swapped) t.info.doubleVal = -cur1->data.info.doubleVal;
                else t.info.doubleVal = cur1->data.info.doubleVal;
                if (!tuplestack_appendtop(stack, t)) return 0;
                cur1 = cur1->next;
            }
            return 1;
        case OP_MUL:
            //do first multiplication
            if (cur1->data._type != TOKEN_NUM || cur2->data._type != TOKEN_NUM) return 0;
            t1._type = TOKEN_NUM;
            t1.info.doubleVal = cur1->data.info.doubleVal * cur2->data.info.doubleVal;
            //swap operands if required
            if (cnt1 < cnt2) {
                expr_token_node* n = cur2;
                cur2 = cur1;
                cur1 = n;
            }
            cur1 = cur1->next;
            if (cnt1 == 1 || cnt2 == 1) { //one operand is a number --> just scale the other
                //push first result
                if (!tuplestack_push_one(stack, t1)) return 0;
                //multiply remaining operands, append
                //add remaining operands, append
                while (cur1 != NULL) {
                    if (cur1->data._type != TOKEN_NUM) return 0;
                    expr_token t;
                    t._type = TOKEN_NUM;
                    t.info.doubleVal = cur1->data.info.doubleVal * cur2->data.info.doubleVal;
                    if (!tuplestack_appendtop(stack, t)) return 0;
                    cur1 = cur1->next;
                }
            } else {
                cur2 = cur2->next;
                //add products of remaining operands (equivalent to vector dot product)
                while (cur2 != NULL) {
                    if (cur1->data._type != TOKEN_NUM || cur2->data._type != TOKEN_NUM) return 0;
                    t1.info.doubleVal += cur1->data.info.doubleVal * cur2->data.info.doubleVal;
                    cur1 = cur1->next;
                    cur2 = cur2->next;
                }
                //push result
                if (!tuplestack_push_one(stack, t1)) return 0;
            }
            return 1;
        case OP_DIV:
            if (cnt2 > 1) return 0; //division by vector is not defined
            //divide first value
            if (cur1->data._type != TOKEN_NUM || cur2->data._type != TOKEN_NUM) return 0;
            t1._type = TOKEN_NUM;
            t1.info.doubleVal = cur1->data.info.doubleVal / cur2->data.info.doubleVal;
            if (!tuplestack_push_one(stack, t1)) return 0;
            cur1 = cur1->next;
            //divide remaining operands, append
            while (cur1 != NULL) {
                if (cur1->data._type != TOKEN_NUM) return 0;
                expr_token t;
                t._type = TOKEN_NUM;
                t.info.doubleVal = cur1->data.info.doubleVal / cur2->data.info.doubleVal;
                if (!tuplestack_appendtop(stack, t)) return 0;
                cur1 = cur1->next;
            }
            return 1;
        case OP_MOD:
            if (cnt2 > 1) return 0; //modulo by vector is not defined
            //modulo first value
            if (cur1->data._type != TOKEN_NUM || cur2->data._type != TOKEN_NUM) return 0;
            t1._type = TOKEN_NUM;
            t1.info.doubleVal = fmod(cur1->data.info.doubleVal, cur2->data.info.doubleVal);
            if (!tuplestack_push_one(stack, t1)) return 0;
            cur1 = cur1->next;
            //modulo remaining operands, append
            while (cur1 != NULL) {
                if (cur1->data._type != TOKEN_NUM) return 0;
                expr_token t;
                t._type = TOKEN_NUM;
                t.info.doubleVal = fmod(cur1->data.info.doubleVal, cur2->data.info.doubleVal);
                if (!tuplestack_appendtop(stack, t)) return 0;
                cur1 = cur1->next;
            }
            return 1;
        case OP_POW:
            if (cnt1 > 1 || cnt2 > 1) return 0; //no vectors in exponentiation
            if (cur1->data._type != TOKEN_NUM || cur2->data._type != TOKEN_NUM) return 0;
            t1._type = TOKEN_NUM;
            if (cur1->data.info.doubleVal == M_E) t1.info.doubleVal = exp(cur2->data.info.doubleVal);
            else t1.info.doubleVal = pow(cur1->data.info.doubleVal,  cur2->data.info.doubleVal);
            if (!tuplestack_push_one(stack, t1)) return 0;
            return 1;
        case OP_COMMA:
            while (cur2 != NULL) {
                if (!tuplestack_appendtop(stack, cur2->data)) return 0;
                cur2 = cur2->next;
            }
            return 1;
        case OP_STORE:
            if (cnt2 > 1) return 0;
            if (cur2->data._type != TOKEN_VARPTR) return 0;
            if (!setVar(cur2->data.info.longVal, val1, cnt1)) return 0;
            return tuplestack_push_list(stack, val1, cnt1);
        default:
            return 0;
    }
}

int eval_var(tuple_stack* stack, uint64_t key) {
    expr_token_list* list;
    uint16_t count;
    if (!getVar(key, &list, &count)) return 0;
    return tuplestack_push_list(stack, list, count);
}

int eval_componentwise_func(expr_token* res, expr_token* arg, uint64_t fn) {
    double trash;
    switch (fn) {
        case FUNC_NEG:
            res->info.doubleVal = -arg->info.doubleVal;
            return 1;
        case FUNC_ABS:
            res->info.doubleVal = fabs(arg->info.doubleVal);
            return 1;
        case FUNC_ACOS:
            res->info.doubleVal = acos(arg->info.doubleVal);
            return 1;
        case FUNC_ACOSH:
            res->info.doubleVal = acosh(arg->info.doubleVal);
            return 1;
        case FUNC_ASIN:
            res->info.doubleVal = asin(arg->info.doubleVal);
            return 1;
        case FUNC_ASINH:
            res->info.doubleVal = asinh(arg->info.doubleVal);
            return 1;
        case FUNC_ATAN:
            res->info.doubleVal = atan(arg->info.doubleVal);
            return 1;
        case FUNC_ATANH:
            res->info.doubleVal = atanh(arg->info.doubleVal);
            return 1;
        case FUNC_COS:
            res->info.doubleVal = cos(arg->info.doubleVal);
            return 1;
        case FUNC_COSH:
            res->info.doubleVal = cosh(arg->info.doubleVal);
            return 1;
        case FUNC_SIN:
            res->info.doubleVal = sin(arg->info.doubleVal);
            return 1;
        case FUNC_SINH:
            res->info.doubleVal = sinh(arg->info.doubleVal);
            return 1;
        case FUNC_TAN:
            res->info.doubleVal = tan(arg->info.doubleVal);
            return 1;
        case FUNC_TANH:
            res->info.doubleVal = tanh(arg->info.doubleVal);
            return 1;
        case FUNC_EXP:
            res->info.doubleVal = exp(arg->info.doubleVal);
            return 1;
        case FUNC_LN:
            res->info.doubleVal = log(arg->info.doubleVal);
            return 1;
        case FUNC_LOG:
            res->info.doubleVal = log10(arg->info.doubleVal);
            return 1;
        case FUNC_FRAC:
            res->info.doubleVal = modf(arg->info.doubleVal, &trash);
            return 1;
        case FUNC_SQRT:
            res->info.doubleVal = sqrt(arg->info.doubleVal);
            return 1;
        case FUNC_CBRT:
            res->info.doubleVal = cbrt(arg->info.doubleVal);
            return 1;
        case FUNC_CEIL:
            res->info.doubleVal = ceil(arg->info.doubleVal);
            return 1;
        case FUNC_FLOOR:
            res->info.doubleVal = floor(arg->info.doubleVal);
            return 1;
        case POSTFIX_FACT:
            res->info.doubleVal = gammap1(arg->info.doubleVal);
            return 1;
        default:
            return 0;
    }
}

int eval_func(tuple_stack* stack, uint64_t fn) {
    expr_token_list* v1, *v2;
    expr_token_node* cur1, *cur2;
    uint16_t cnt1, cnt2;
    expr_token t1;
    switch (fn) {
        case FUNC_NEG:
        case FUNC_ABS:
        case FUNC_ACOS:
        case FUNC_ACOSH:
        case FUNC_ASIN:
        case FUNC_ASINH:
        case FUNC_ATAN:
        case FUNC_ATANH:
        case FUNC_COS:
        case FUNC_COSH:
        case FUNC_SIN:
        case FUNC_SINH:
        case FUNC_TAN:
        case FUNC_TANH:
        case FUNC_EXP:
        case FUNC_LN:
        case FUNC_LOG:
        case FUNC_FRAC:
        case FUNC_SQRT:
        case FUNC_CBRT:
        case FUNC_CEIL:
        case FUNC_FLOOR:
        case POSTFIX_FACT:
            if (!tuplestack_pop(stack, &v1, &cnt1)) return 0;
            cur1 = v1->head;
            if (cur1->data._type != TOKEN_NUM) return 0;
            t1._type = TOKEN_NUM;
            if (!eval_componentwise_func(&t1, &cur1->data, fn)) return 0;
            if (!tuplestack_push_one(stack, t1)) return 0;
            cur1 = cur1->next;
            while (cur1 != NULL) {
                if (cur1->data._type != TOKEN_NUM) return 0;
                expr_token t;
                t._type = TOKEN_NUM;
                if (!eval_componentwise_func(&t, &cur1->data, fn)) return 0;
                if (!tuplestack_appendtop(stack, t)) return 0;
                cur1 = cur1->next;
            }
            return 1;
        default:
            return 0;
    }
}

int eval_expr(expr_token_list* expr, list64* result) {
    tuple_stack evalstack;
    tuplestack_init(&evalstack);
    
    expr_token_node* curr = expr->head;
    while (curr != NULL) {
        switch(curr->data._type) {
            case TOKEN_VARPTR:
            case TOKEN_NUM:
                if (!tuplestack_push_one(&evalstack, curr->data)) return 0;
                break;
            case TOKEN_OP:
                if (!eval_operator(&evalstack, curr->data.info.longVal)) return 0;
                break;
            case TOKEN_BR:
                return 0; //no brackets in finished expression!
            case TOKEN_VAR:
                if (!eval_var(&evalstack, curr->data.info.longVal)) return 0;
                break;
            case TOKEN_POSTFIX:
            case TOKEN_FUNC:
                if (!eval_func(&evalstack, curr->data.info.longVal)) return 0;
                break;                
            default:
                return 0;
        }
        curr = curr->next;
    }
    
    expr_token_list* res;
    uint16_t resCount;
    if (!tuplestack_pop(&evalstack, &res, &resCount)) return 0;
    if (!tuplestack_is_empty(&evalstack)) return 0; //can only output one tuple!
    list64_clear(result);
    while(!is_tokenlist_empty(res)) {
        expr_token t;
        if (!pop_token(res, &t)) return 0;
        if (!list64_queue_f(result, t.info.doubleVal)) return 0;
    }
    return 1;
}


void free_expr(expr_token_list* expr) {
    if (expr == NULL) return;
    clear_tokenlist(expr);
    free(expr);
}