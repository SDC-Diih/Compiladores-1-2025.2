
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "interpreter.h"
#include "../ast/ast.h"

typedef struct Var {
    char *name;
    int value;
    struct Var *next;
} Var;

Var *symbolTable = NULL;

