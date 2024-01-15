#ifndef VARS_H
#define VARS_H

#include "expr_tokens.h"

void initVars();
int setVar(uint64_t key, expr_token_list* val, uint16_t count);
int setVarSingle(uint64_t key, expr_token val);
int setX(double value);
int removeVar(uint64_t key);
int getVar(uint64_t key, expr_token_list** val, uint16_t* count);
int getVarSingle(uint64_t key, expr_token* val);
int varExists(uint64_t key);
int varReserved(uint64_t key);
int getKeyFromName(char* name, uint64_t* key);

#endif