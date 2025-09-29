%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Var {
    char *name;
    int value;
    struct Var *next;
} Var;

typedef struct Function {
    char *name;
    int returnValue;
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
        if(strcmp(v->name, name) == 0) {
            return v;
        }
        v = v->next;
    }
    return NULL;
}

void addVar(char *name) {
    if(findVar(name) != NULL) {
        return; // já existe
    }
    Var *v = (Var*)malloc(sizeof(Var));
    v->name = strdup(name);
    v->value = 0;
    v->next = symbolTable;
    symbolTable = v;
}

Function* findFunction(char *name) {
    Function *f = functionTable;
    while(f) {
        if(strcmp(f->name, name) == 0) {
            return f;
        }
        f = f->next;
    }
    return NULL;
}

Function* createFunction(char *name) {
    Function *f = (Function*)malloc(sizeof(Function));
    f->name = strdup(name);
    f->returnValue = 0;
    f->next = functionTable;
    functionTable = f;
    return f;
}
%}

%union {
    int ival;
    char *sval;
}

%token INT PRINT RETURN
%token <ival> NUMBER
%token <sval> ID

%type <ival> expr   /* expr vai carregar inteiros */

%left '+' '-'
%left '*' '/'

%%

program:
      program function_def
    | program stmt
    | /* vazio */
    ;

function_def:
      INT ID '(' ')' '{' { 
                                currentFunction = createFunction($2);
                            } stmt_list '}' {
                                currentFunction = NULL;
                            }
    ;

stmt_list:
      stmt_list stmt
    | /* vazio */
    ;

stmt:
      INT ID ';'            { addVar($2); }
    | ID '=' expr ';'       {
                                Var *v = findVar($1);
                                if (v) {
                                    v->value = $3; 
                                } else {
                                    printf("Erro: variavel %s nao declarada\n", $1);
                                    exit(1);
                                }
                            }
    | INT ID '=' expr ';'   {
                                addVar($2);
                                Var *v = findVar($2);
                                if (v) {
                                    v->value = $4; 
                                } else {
                                    printf("Erro: variavel %s nao declarada\n", $2);
                                    exit(1);
                                }
                            }
    | PRINT ID ';'          {
                                Var *v = findVar($2);
                                if (v) {
                                    printf("%d\n", v->value);
                                } else {
                                    printf("Erro: variavel %s nao declarada\n", $2);
                                    exit(1);
                                }
                            }
    | RETURN expr ';'       {
                                if (currentFunction) {
                                    currentFunction->returnValue = $2;
                                } else {
                                    printf("Erro: return fora de funcao\n");
                                    exit(1);
                                }
                            }
    | ID '(' ')' ';'        {
                                Function *f = findFunction($1);
                                if (f) {
                                    printf("%d\n", f->returnValue);
                                } else {
                                    printf("Erro: funcao %s nao declarada\n", $1);
                                    exit(1);
                                }
                            }
    ;

expr:
      expr '+' expr         { $$ = $1 + $3; }
    | expr '-' expr         { $$ = $1 - $3; }
    | expr '*' expr         { $$ = $1 * $3; }
    | expr '/' expr         {
                                if ($3 == 0) {
                                    printf("Erro: Divisão por Zero! \n");
                                    exit(1); 
                                } else {
                                    $$ = $1 / $3;
                                }
                            }
    | NUMBER                { $$ = $1; }
    | ID                    {
                                Var *v = findVar($1);
                                if (v) {
                                    $$ = v->value;
                                } else {
                                    printf("Erro: variavel %s nao declarada\n", $1);
                                    exit(1); 
                                }
                            }
    | ID '(' ')'            {
                                Function *f = findFunction($1);
                                if (f) {
                                    $$ = f->returnValue;
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