%code requires {
    #include "../ast/ast.h"
}

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
    float fval;
    char *sval;
    struct ASTNode* node;
    int dataType;
}

%token INT FLOAT PRINT RETURN IF ELSE WHILE FOR
%token EQ NEQ LT GT LEQ GEQ
%token <ival> NUMBER
%token <fval> FLOAT_NUM
%token <sval> ID

%type <node> expr stmt stmtList functionDef program condition assignment
%type <dataType> type

%left EQ NEQ LT GT LEQ GEQ
%left '+' '-'
%left '*' '/'

%%

program:
      stmtList { astRoot = $1; }
    | /* vazio */ { astRoot = NULL;}
    ;

type:
      INT   { $$ = DATA_TYPE_INT; }
    | FLOAT { $$ = DATA_TYPE_FLOAT; }
    ;

stmtList:
      /* vazio */ { $$ = NULL; }
    | stmtList stmt { 
        if ($1 == NULL) {
            $$ = $2;
        } else {
            $$ = createStmtListNode($1, $2); 
        }
      }
    | stmtList functionDef { 
        if ($1 == NULL) {
            $$ = $2;
        } else {
            $$ = createStmtListNode($1, $2); 
        }
      }
    ;

functionDef:
    type ID '(' ')' '{' stmtList '}' {
        $$ = createFuncDefNode($2, $6);
    }
    ;

stmt:
      type ID ';'            { $$ = createVarNodeWithType((DataType)$1, $2); }
    | type ID '['expr']' ';' { $$ = createArrayDeclNode($2, $4); } 
    | ID '=' expr ';'       { $$ = createAssignNode(createIdNode($1), $3); }
    | ID '['expr']' '=' expr ';' {
                                ASTNode* target = createArrayAccessNode(createIdNode($1), $3);
                                $$ = createAssignNode(target, $6);
                            }
    | type ID '=' expr ';'   {
                                ASTNode* decl = createVarNodeWithType((DataType)$1, $2);
                                ASTNode* assign = createAssignNode(createIdNode(strdup($2)), $4);
                                $$ = createStmtListNode(decl, assign);
                            }
    | PRINT expr ';'        { $$ = createPrintNode($2); }
    | RETURN expr ';'       { $$ = createReturnNode($2); }
    | IF '(' condition ')' '{' stmtList '}' { 
                                $$ = createIfNode($3, $6, NULL); 
                            }
    | IF '(' condition ')' '{' stmtList '}' ELSE '{' stmtList '}' { 
                                $$ = createIfNode($3, $6, $10); 
                            }
    | WHILE '(' condition ')' '{' stmtList '}' {
                                $$ = createWhileNode($3, $6);
                            }
    | FOR '(' assignment ';' condition ';' assignment ')' '{' stmtList '}' {
                                $$ = createForNode($3, $5, $7, $10);
                            }
    | expr ';'              { $$ = $1; }
    ;

assignment:
      ID '=' expr           { $$ = createAssignNode(createIdNode($1), $3); }
    ;

condition:
      expr EQ expr          { $$ = createRelationalOpNode("==", $1, $3); }
    | expr NEQ expr         { $$ = createRelationalOpNode("!=", $1, $3); }
    | expr LT expr          { $$ = createRelationalOpNode("<", $1, $3); }
    | expr GT expr          { $$ = createRelationalOpNode(">", $1, $3); }
    | expr LEQ expr         { $$ = createRelationalOpNode("<=", $1, $3); }
    | expr GEQ expr         { $$ = createRelationalOpNode(">=", $1, $3); }
    ;

expr:
      expr '+' expr         { $$ = createBinOpNode('+', $1, $3); }
    | expr '-' expr         { $$ = createBinOpNode('-', $1, $3); }
    | expr '*' expr         { $$ = createBinOpNode('*', $1, $3); }
    | expr '/' expr         { $$ = createBinOpNode('/', $1, $3); }
    | NUMBER                { $$ = createNumberNode($1); }
    | FLOAT_NUM             { $$ = createFloatNode($1); }
    | ID                    { $$ = createIdNode($1); }
    | ID '[' expr ']'       { $$ = createArrayAccessNode(createIdNode($1), $3); }
    | ID '(' ')'            { $$ = createFuncCallNode($1); }
    | '(' expr ')'          { $$ = $2; }
    ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Erro de Sintaxe: %s\n", s);
}
