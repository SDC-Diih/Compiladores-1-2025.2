%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Var {
    char *name;
    int value;
    struct Var *next;
} Var;

Var *symbolTable = NULL;

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
%}

%union {
    int ival;
    char *sval;
}

%token INT PRINT
%token <ival> NUMBER
%token <sval> ID

%type <ival> expr   /* expr vai carregar inteiros */

%left '+' '-'
%left '*' '/'

%%

program:
      program stmt
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
    | PRINT ID ';'          {
                                Var *v = findVar($2);
                                if (v) {
                                    printf("%d\n", v->value);
                                } else {
                                    printf("Erro: variavel %s nao declarada\n", $2);
                                    exit(1);
                                }
                            }
    ;

expr:
      expr '+' expr         { $$ = $1 + $3; }
    | expr '-' expr         { $$ = $1 - $3; }
    | expr '*' expr         { $$ = $1 * $3; }
    | expr '/' expr         { $$ = $1 / $3; }
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
    ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Erro: %s\n", s);
}
