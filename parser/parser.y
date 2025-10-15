%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../ast/ast.h"

int yylex();
void yyerror(const char *s);

ASTNode *astRoot = NULL; 
%}

%union {
    int ival;
    char *sval;
    struct ASTNode* node;
}

%token INT PRINT RETURN
%token <ival> NUMBER
%token <sval> ID

%type <node> expr stmt stmtList functionDef program

%left '+' '-'
%left '*' '/'

%%

program:
      stmtList { astRoot = $1; }
    | /* vazio */ { astRoot = NULL;}
    ;

stmtList:
    /* vazio */ { $$ = NULL; }
    | stmtList stmt { $$ = createStmtListNode($1, $2); }
    | stmtList functionDef { $$ = createStmtListNode($1, $2); }
    ;

functionDef:
    INT ID '(' ')' '{' stmtList '}' {
        $$ = createFuncDefNode($2, $6);
    }
    ;

stmt:
      INT ID ';'            { $$ = createVarNode($2); }
    | INT ID '['expr']' ';' { $$ = createArrayDeclNode($2, $4); } 
    | ID '=' expr ';'       { $$ = createAssignNode(createIdNode($1), $3); }

    | ID '['expr']' '=' expr ';' {
                                ASTNode* target = createArrayAccessNode(createIdNode($1), $3);
                                $$ = createAssignNode(target, $6);
                            }
    | INT ID '=' expr ';'   {
                                ASTNode* decl = createVarNode($2);
                                ASTNode* assign = createAssignNode(createIdNode(strdup($2)), $4);
                                $$ = createStmtListNode(decl, assign);
                            }
    | PRINT expr ';'        { $$ = createPrintNode($2); }
    | RETURN expr ';'       { $$ = createReturnNode($2); }
    | expr ';'              { $$ = $1; }
    ;

expr:
      expr '+' expr         { $$ = createBinOpNode('+', $1, $3); }
    | expr '-' expr         { $$ = createBinOpNode('-', $1, $3); }
    | expr '*' expr         { $$ = createBinOpNode('*', $1, $3); }
    | expr '/' expr         { $$ = createBinOpNode('/', $1, $3); }
    | NUMBER                { $$ = createNumberNode($1); }
    | ID                    { $$ = createIdNode($1); }
    | ID '[' expr ']'       { $$ = createArrayAccessNode(createIdNode($1), $3); }
    | ID '(' ')'            { $$ = createFuncCallNode($1); }
    | '(' expr ')'          { $$ = $2; }
    ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Erro de Sintaxe: %s\n", s);
}
