#include <stdio.h>
#include "../ast/ast.h"
#include "../interpreter/interpreter.h"

extern ASTNode *astRoot;

int yyparse();

int main() {
    printf("  \n");
    printf(" Interpretador em C \n");
    printf(" -------------------------------------------------- \n");

    yyparse();

    if (!astRoot) {
        printf(" Falha ao gerar AST! \n");
        
    } else {
        printf("Árvore Sintática Abstrata (AST): \n");
        printAst(astRoot, 0);
        printf(" -------------------------------------------------- \n");

        evaluateNode(astRoot);

        freeAst(astRoot);
    }
    return 0;
}
