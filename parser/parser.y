%{
#include <stdio.h>
#include <stdlib.h>

int yylex(void);
void yyerror(const char *s);
%}

/* Valor semântico dos tokens como int */
%define api.value.type {int}

/* Declara tokens */
%token NUM
%token PLUS MINUS TIMES DIVIDE LPAREN RPAREN

/* Precedência e associatividade (da menor p/ maior) */
%left PLUS MINUS
%left TIMES DIVIDE
%right UMINUS   /* para o - unário: -5, -(2+3) */

%%

/* Uma expressão aritmética com precedência correta */
expressao
    : expressao PLUS   expressao    { $$ = $1 + $3; }
    | expressao MINUS  expressao    { $$ = $1 - $3; }
    | expressao TIMES  expressao    { $$ = $1 * $3; }
    | expressao DIVIDE expressao    { $$ = $1 / $3; }
    | LPAREN expressao RPAREN       { $$ = $2; }
    | MINUS expressao %prec UMINUS  { $$ = -$2; }  /* -unário */
    | NUM                           { $$ = $1; }
    ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Erro sintático: %s\n", s);
}

int main(void) {
    int result;
    if (yyparse() == 0) {
        /* Se quiser imprimir o valor, mude a gramática para produzir em 'main' */
    }
    return 0;
}
