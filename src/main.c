#include <stdio.h>
#include "../ast/ast.h"

extern ASTNode *ast_root;

int yyparse();

int main() {
    printf("  \n");
    printf(" Interpretador em C (Modo AST) \n");
    printf(" Insira o código abaixo e pressione Ctrl+D (Linux/Mac) ou Ctrl+Z (Windows) para finalizar a entrada: \n");
    printf(" -------------------------------------------------- \n");

    yyparse();

    if (ast_root) {
        printf(" -------------------------------------------------- \n");
        printf("Árvore Sintática Abstrata (AST): \n");
        print_ast(ast_root, 0);
        free_ast(ast_root);
    } else {
        printf(" Falha ao gerar AST! \n");
    }
    return 0;
}
