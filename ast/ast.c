#include "ast.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

ASTNode* create_node(NodeType type) {
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));

    if(!node) {
        fprintf(stderr, "Falha ao alocar memoria para o no \n");
        exit(EXIT_FAILURE);
    }
    
    node->type = type;
    return node;
};

ASTNode* create_number_node(int value) {
    ASTNode* node = create_node(NODE_NUMBER);
    node->data.number = value;
    return node;
};

ASTNode* create_id_node(char* name) {
    ASTNode* node = create_node(NODE_ID);
    node->data.name = strdup(name);
    return node;
};

ASTNode* create_var_node(char* name) {
    ASTNode* node = create_node(NODE_VAR);
    node->data.name = strdup(name);
    return node;
};

ASTNode* create_bin_op_node(char op, ASTNode* left, ASTNode* right) {
    ASTNode* node = create_node(NODE_BIN_OP);
    node->data.binary_op.op = op;
    node->data.binary_op.left = left;
    node->data.binary_op.right = right;
    return node;
};

ASTNode* create_assign_node(ASTNode* lvalue, ASTNode* rvalue) {
    ASTNode* node = create_node(NODE_ASSIGN);
    node->data.assign.lvalue = lvalue;
    node->data.assign.rvalue = rvalue;
    return node;
};

ASTNode* create_print_node(ASTNode* expression) {
    ASTNode* node = create_node(NODE_PRINT);
    node->data.statement.expression = expression;
    return node;
};

ASTNode* create_return_node(ASTNode* expression) {
    ASTNode* node = create_node(NODE_RETURN);
    node->data.statement.expression = expression;
    return node;
};

ASTNode* create_stmt_list_node(ASTNode* statement, ASTNode* next) {
    ASTNode* node = create_node(NODE_STMT_LIST);
    node->data.stmt_list.statement = statement;
    node->data.stmt_list.next = next;
    return node;
};

ASTNode* create_func_def_node(char* name, ASTNode* body) {
    ASTNode* node = create_node(NODE_FUNC_DEF);
    node->data.func_def.name = strdup(name);
    node->data.func_def.body = body;
    return node;
};

ASTNode* create_func_call_node(char* name) {
    ASTNode* node = create_node(NODE_FUNC_CALL);
    node->data.func_call.name = strdup(name);
    return node;
};

void print_ast(ASTNode* node, int level) {
    if (!node) return;

    for (int i = 0; i < level; i++) printf("  ");

    switch (node->type) {
        case NODE_NUMBER:
            printf( "Numero: %d\n", node->data.number);
            break;
        case NODE_ID:
            printf( "ID: %s\n", node->data.name);
            break;
        case NODE_VAR:
            printf( "Var: %s\n", node->data.name);
            break;
        case NODE_BIN_OP:
            printf( "Operador: %c\n", node->data.binary_op.op);
            print_ast(node->data.binary_op.left, level + 1);
            print_ast(node->data.binary_op.right, level + 1);
            break;
        case NODE_ASSIGN:
            printf( "Assignment: \n");
            print_ast(node->data.assign.lvalue, level + 1);
            print_ast(node->data.assign.rvalue, level + 1);
            break;
        case NODE_PRINT:
            printf( "Print: \n");
            print_ast(node->data.statement.expression, level + 1);
            break;
        case NODE_RETURN:
            printf( "Return: \n");
            print_ast(node->data.statement.expression, level + 1);
            break;
        case NODE_STMT_LIST:
            printf("Lista: \n");
            print_ast(node->data.stmt_list.statement, level +1);
            if (node->data.stmt_list.next) {
                print_ast(node->data.stmt_list.next, level);
            }
            break;
        case NODE_FUNC_DEF:
            printf( "Funcao: %s\n", node->data.func_def.name);
            printf( "Corpo da Funcao: \n");
            print_ast(node->data.func_def.body, level + 1);
            break;
        case NODE_FUNC_CALL:
            printf( "Chamada da Funcao: %s\n", node->data.func_call.name);
            break;
        default:
            printf( "Tipo de no desconhecido \n");
            break;
    }
}

void free_ast(ASTNode* node) {
    if (!node) return;

    switch (node->type) {

        // Nó sem memória alocada
        case NODE_NUMBER:
            break;

        // Nós com strdup
        case NODE_ID:
        case NODE_VAR:
        case NODE_FUNC_CALL:
            free(node->data.name); 
            break;

        // Nós com filhos
        case NODE_BIN_OP:
            free_ast(node->data.binary_op.left);
            free_ast(node->data.binary_op.right);
            break;
        case NODE_ASSIGN:
            free_ast(node->data.assign.lvalue);
            free_ast(node->data.assign.rvalue);
            break;
        case NODE_PRINT:
        case NODE_RETURN:
            free_ast(node->data.statement.expression); // <-- MUDANÇA: free_ast() para a expressão filha
            break;
        case NODE_STMT_LIST:
            free_ast(node->data.stmt_list.statement);
            free_ast(node->data.stmt_list.next);
            break;
        case NODE_FUNC_DEF:
            free(node->data.func_def.name);
            free_ast(node->data.func_def.body);
            break;

        default:
            break;
    }

    free(node);
}
