%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../ast/ast.h"

int yylex();
void yyerror(const char *s);

ASTNode *ast_root = NULL; 
%}

%union {
    int ival;
    char *sval;
    struct ASTNode* node;
}

%token INT PRINT RETURN
%token <ival> NUMBER
%token <sval> ID

%type <node> expr stmt stmt_list function_def program

%left '+' '-'
%left '*' '/'

%%

program:
      stmt_list { ast_root = $1; }
    | /* vazio */ { ast_root = NULL;}
    ;

stmt_list:
    /* vazio */ { $$ = NULL; }
    | stmt_list stmt { $$ = create_stmt_list_node($1, $2); }
    | stmt_list function_def { $$ = create_stmt_list_node($1, $2); }
    ;

function_def:
    INT ID '(' ')' '{' stmt_list '}' {
        $$ = create_func_def_node($2, $6);
    }
    ;

stmt:
      INT ID ';'            { $$ = create_var_node($2); }
    | ID '=' expr ';'       { $$ = create_assign_node(create_id_node($1), $3); }
    | INT ID '=' expr ';'   {
                                ASTNode* decl = create_var_node($2);
                                ASTNode* assign = create_assign_node(create_id_node(strdup($2)), $4);
                                $$ = create_stmt_list_node(decl, assign);
                            }
    | PRINT ID ';'          { $$ = create_print_node(create_id_node($2)); }
    | RETURN expr ';'       { $$ = create_return_node($2); }
    | expr ';'              { $$ = $1; }
    ;

expr:
      expr '+' expr         { $$ = create_bin_op_node('+', $1, $3); }
    | expr '-' expr         { $$ = create_bin_op_node('-', $1, $3); }
    | expr '*' expr         { $$ = create_bin_op_node('*', $1, $3); }
    | expr '/' expr         { $$ = create_bin_op_node('/', $1, $3); }
    | NUMBER                { $$ = create_number_node($1); }
    | ID                    { $$ = create_id_node($1); }
    | ID '(' ')'            { $$ = create_func_call_node($1); }
    | '(' expr ')'          { $$ = $2; }
    ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Erro de Sintaxe: %s\n", s);
}
