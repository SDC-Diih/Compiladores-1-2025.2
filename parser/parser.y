%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum { TYPE_INT, TYPE_FLOAT } VarType;

typedef struct Var {
    char *name;
    VarType type;
    union {
        int i_val;
        float f_val;
    } value;
    struct Var *next;
} Var;

typedef struct Function {
    char *name;
    VarType returnType;
    union {
        int i_val;
        float f_val;
    } returnValue;
    struct Function *next;
} Function;

Var *symbolTable = NULL;
Function *functionTable = NULL;
Function *currentFunction = NULL;

int yylex();
void yyerror(const char *s);

Var* findVar(char *name) {
    Var *v = symbolTable;
    while(v) {
        if(strcmp(v->name, name) == 0)
            return v;
        v = v->next;
    }
    return NULL;
}

void addVar(char *name, VarType type) {
    if(findVar(name) != NULL)
        return; // já existe

    Var *v = (Var*)malloc(sizeof(Var));
    v->name = strdup(name);
    v->type = type;
    v->value.i_val = 0;
    v->next = symbolTable;
    symbolTable = v;
}

Function* findFunction(char *name) {
    Function *f = functionTable;
    while(f) {
        if(strcmp(f->name, name) == 0)
            return f;
        f = f->next;
    }
    return NULL;
}

Function* createFunction(char *name, VarType type) {
    Function *f = (Function*)malloc(sizeof(Function));
    f->name = strdup(name);
    f->returnType = type;
    f->returnValue.i_val = 0;
    f->next = functionTable;
    functionTable = f;
    return f;
}
%}

%union {
    int ival;
    float fval;
    char *sval;
}

%token INT FLOAT PRINT RETURN
%token <ival> NUMBER
%token <fval> NUMBER_FLOAT
%token <sval> ID

%type <fval> expr

%left '+' '-'
%left '*' '/'

%%

program:
      program function_def
    | program stmt
    | /* vazio */
    ;

function_def:
      INT ID '(' ')' '{' { currentFunction = createFunction($2, TYPE_INT); }
      stmt_list '}'      { currentFunction = NULL; }
    | FLOAT ID '(' ')' '{' { currentFunction = createFunction($2, TYPE_FLOAT); }
      stmt_list '}'        { currentFunction = NULL; }
    ;

stmt_list:
      stmt_list stmt
    | /* vazio */
    ;

stmt:
      INT ID ';' {
            addVar($2, TYPE_INT);
        }
    | FLOAT ID ';' {
            addVar($2, TYPE_FLOAT);
        }
    | ID '=' expr ';' {
            Var *v = findVar($1);
            if (v) {
                if (v->type == TYPE_INT)
                    v->value.i_val = (int)$3;
                else
                    v->value.f_val = (float)$3;
            } else {
                printf("Erro: variavel %s nao declarada\n", $1);
                exit(1);
            }
        }
    | INT ID '=' expr ';' {
            addVar($2, TYPE_INT);
            Var *v = findVar($2);
            v->value.i_val = (int)$4;
        }
    | FLOAT ID '=' expr ';' {
            addVar($2, TYPE_FLOAT);
            Var *v = findVar($2);
            v->value.f_val = (float)$4;
        }
    | PRINT ID ';' {
            Var *v = findVar($2);
            if (v) {
                if (v->type == TYPE_INT)
                    printf("%d\n", v->value.i_val);
                else
                    printf("%f\n", v->value.f_val);
            } else {
                printf("Erro: variavel %s nao declarada\n", $2);
                exit(1);
            }
        }
    | RETURN expr ';' {
            if (currentFunction) {
                if (currentFunction->returnType == TYPE_INT)
                    currentFunction->returnValue.i_val = (int)$2;
                else
                    currentFunction->returnValue.f_val = $2;
            } else {
                printf("Erro: return fora de funcao\n");
                exit(1);
            }
        }
    | ID '(' ')' ';' {
            Function *f = findFunction($1);
            if (f) {
                if (f->returnType == TYPE_INT)
                    printf("%d\n", f->returnValue.i_val);
                else
                    printf("%f\n", f->returnValue.f_val);
            } else {
                printf("Erro: funcao %s nao declarada\n", $1);
                exit(1);
            }
        }
    ;

expr:
      expr '+' expr   { $$ = $1 + $3; }
    | expr '-' expr   { $$ = $1 - $3; }
    | expr '*' expr   { $$ = $1 * $3; }
    | expr '/' expr   {
            if ($3 == 0) {
                printf("Erro: divisao por zero!\n");
                exit(1);
            }
            $$ = $1 / $3;
        }
    | NUMBER          { $$ = $1; }
    | NUMBER_FLOAT    { $$ = $1; }
    | ID {
            Var *v = findVar($1);
            if (v) {
                $$ = (v->type == TYPE_INT) ? v->value.i_val : v->value.f_val;
            } else {
                printf("Erro: variavel %s nao declarada\n", $1);
                exit(1);
            }
        }
    | ID '(' ')' {
            Function *f = findFunction($1);
            if (f) {
                $$ = (f->returnType == TYPE_INT) ? f->returnValue.i_val : f->returnValue.f_val;
            } else {
                printf("Erro: funcao %s nao declarada\n", $1);
                exit(1);
            }
        }
    ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Erro: %s\n", s);
}