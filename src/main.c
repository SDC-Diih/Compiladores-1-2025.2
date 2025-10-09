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

    evaluateNode(astRoot);

    if (astRoot) {
        printf(" -------------------------------------------------- \n");
        printf("Árvore Sintática Abstrata (AST): \n");
        printAst(astRoot, 0);
        freeAst(astRoot);
    } else {
        printf(" Falha ao gerar AST! \n");
    }
    return 0;
}
