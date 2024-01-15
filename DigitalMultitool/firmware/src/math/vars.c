#include "vars.h"
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define VAR_pi 0x6970ul
#define VAR_e 0x65ul
#define VAR__MTV 0x56544d5ful
#define VAR_X 0x78ul

typedef struct varnode {
    uint64_t key;
    expr_token_list values;
    uint16_t count;
    struct varnode* left;
    struct varnode* right;
} var_node;

var_node* root = NULL;

expr_token_list e, pi, _mtv, x;
expr_token t_e, t_pi, t__mtv, t_x;

void initVars() {
    init_tokenlist(&e);
    init_tokenlist(&pi);
    init_tokenlist(&_mtv);
    init_tokenlist(&x);
    t_e._type = 0;
    t_e.info.doubleVal = M_E;
    t_pi._type = 0;
    t_pi.info.doubleVal = M_PI;
    t__mtv._type = 0;
    t__mtv.info.doubleVal = 1.0;
    t_x._type = 0;
    t_x.info.doubleVal = 0.0;
    queue_token(&e, t_e);
    queue_token(&pi, t_pi);
    queue_token(&_mtv, t__mtv);
    queue_token(&x, t_x);
}

var_node* findNode(uint64_t key) {
    var_node* curr = root;
    while (curr != NULL) {
        if (key == curr->key) return curr;
        else if (key > curr->key) curr = curr->right;
        else curr = curr->left;
    }
    return NULL;
}

var_node* findOrCreateNode(uint64_t key) {
    var_node* newn;
    if (root == NULL) {
        newn = malloc(sizeof(var_node));
        if (newn == NULL) return NULL;
        newn->key = key;
        newn->count = 0;
        newn->left = NULL;
        newn->right = NULL;
        root = newn;
        return newn;
    }
    var_node* curr = root, *last;
    while (curr != NULL) {
        last = curr;
        if (key == curr->key) return curr;
        else if (key > curr->key) curr = curr->right;
        else curr = curr->left;
    }
    newn = malloc(sizeof(var_node));
    if (newn == NULL) return NULL;
    newn->key = key;
    newn->count = 0;
    newn->left = NULL;
    newn->right = NULL;
    if (key > last->key) last->right = newn;
    else last->left = newn;
    return newn;
}

int setVar(uint64_t key, expr_token_list* val, uint16_t count) {
    if (varReserved(key)) return 0;
    if (key == VAR_X) {
        if (count != 1) return 0;
        if (val->head->data._type != TOKEN_NUM) return 0;
        x = *val;
        t_x = x.head->data;
        return 1;
    }
    var_node* node = findOrCreateNode(key);
    if (node == NULL) return 0;
    node->values = *val;
    node->count = count;
    return 1;
}

int setVarSingle(uint64_t key, expr_token val) {
    if (varReserved(key)) return 0;
    if (key == VAR_X) {
        if (val._type != TOKEN_NUM) return 0;
        clear_tokenlist(&x);
        t_x = val;
        return queue_token(&x, t_x);
    }
    var_node* node = findOrCreateNode(key);
    if (node == NULL) return 0;
    if (node->count > 0) {
        clear_tokenlist(&node->values);
        if (!queue_token(&node->values, val)) return 0;
    } else {
        expr_token_list list;
        init_tokenlist(&list);
        if (!queue_token(&list, val)) return 0;
        node->values = list;
    }
    node->count = 1;
    return 1;
}

int setX(double value) {
    clear_tokenlist(&x);
    t_x.info.doubleVal = value;
    return queue_token(&x, t_x);
}

int removeVar(uint64_t key) {
    if (varReserved(key) || key == VAR_X) return 0;
    var_node* curr = root, *last;
    while (curr != NULL) {
        last = curr;
        if (key == curr->key) break;
        else if (key > curr->key) curr = curr->right;
        else curr = curr->left;
    }
    if (curr == NULL) return 0;
    if (curr->left == NULL && curr->right == NULL) { //no children: just remove
        if (curr == last->right) last->right = NULL;
        else last->left = NULL;
    } else if (curr->left == NULL) { //only right child: move up
        if (curr == last->right) last->right = curr->right;
        else last->left = curr->right;
    } else if (curr->right == NULL) { //only left child: move up
        if (curr == last->right) last->right = curr->left;
        else last->left = curr->left;
    } else { //two children: replace with next node in order
        var_node* fcurr = curr->right, *flast = curr;
        while (fcurr->left != NULL) {
            flast = fcurr;
            fcurr = fcurr->left;
        }
        fcurr->left = curr->left;
        if (flast != curr) {
            flast->left = fcurr->right;
            fcurr->right = curr->right;
        }
        if (curr == last->right) last->right = fcurr;
        else last->left = fcurr;
    }
    clear_tokenlist(&curr->values);
    free(curr);
    return 1;
}

int getVar(uint64_t key, expr_token_list** val, uint16_t* count) {
    switch (key) {
        case VAR_e:
            *val = &e;
            *count = 1;
            return 1;
        case VAR_pi:
            *val = &pi;
            *count = 1;
            return 1;
        case VAR__MTV:
            *val = &_mtv;
            *count = 1;
            return 1;
        case VAR_X:
            *val = &x;
            *count = 1;
            return 1;
    }
    var_node* node = findNode(key);
    if (node == NULL) return 0;
    *val = &node->values;
    *count = node->count;
    return 1;
}

int getVarSingle(uint64_t key, expr_token* val) {
    switch (key) {
        case VAR_e:
            *val = t_e;
            return 1;
        case VAR_pi:
            *val = t_pi;
            return 1;
        case VAR__MTV:
            *val = t__mtv;
            return 1;
        case VAR_X:
            *val = t_x;
            return 1;
    }
    var_node* node = findNode(key);
    if (node == NULL) return 0;
    *val = node->values.head->data;
    return 1;
}

int varExists(uint64_t key) {
    if (varReserved(key) || key == VAR_X) return 1;
    return findNode(key) != NULL;
}

int varReserved(uint64_t key) {
    switch (key) {
        case VAR_e:
        case VAR_pi:
        case VAR__MTV:
            return 1;
        default:
            return 0;
    }
}

int getKeyFromName(char* name, uint64_t* key) {
    int len = strlen(name);
    if (len == 0 || len > 8) return 0;
    *key = 0;
    int i;
    for (i = 0; i < len; i++) {
        *key |= (uint64_t)*(name + i) << (8 * i);
    }
    return 1;
}