#include "ast.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

ASTNode* createNode(NodeType type) {
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));

    if(!node) {
        fprintf(stderr, "Falha ao alocar memoria para o no \n");
        exit(EXIT_FAILURE);
    }
    
    node->type = type;
    return node;
};

ASTNode* createNumberNode(int value) {
    ASTNode* node = createNode(NODE_NUMBER);
    node->data.number = value;
    return node;
};

ASTNode* createIdNode(char* name) {
    ASTNode* node = createNode(NODE_ID);
    node->data.name = strdup(name);
    return node;
};

ASTNode* createVarNode(char* name) {
    ASTNode* node = createNode(NODE_VAR);
    node->data.name = strdup(name);
    return node;
};

ASTNode* createBinOpNode(char op, ASTNode* left, ASTNode* right) {
    ASTNode* node = createNode(NODE_BIN_OP);
    node->data.binaryOp.op = op;
    node->data.binaryOp.left = left;
    node->data.binaryOp.right = right;
    return node;
};

ASTNode* createAssignNode(ASTNode* lvalue, ASTNode* rvalue) {
    ASTNode* node = createNode(NODE_ASSIGN);
    node->data.assign.lvalue = lvalue;
    node->data.assign.rvalue = rvalue;
    return node;
};

ASTNode* createPrintNode(ASTNode* expression) {
    ASTNode* node = createNode(NODE_PRINT);
    node->data.statement.expression = expression;
    return node;
};

ASTNode* createReturnNode(ASTNode* expression) {
    ASTNode* node = createNode(NODE_RETURN);
    node->data.statement.expression = expression;
    return node;
};

ASTNode* createStmtListNode(ASTNode* statement, ASTNode* next) {
    ASTNode* node = createNode(NODE_STMT_LIST);
    node->data.stmtList.statement = statement;
    node->data.stmtList.next = next;
    return node;
};

ASTNode* createFuncDefNode(char* name, ASTNode* body) {
    ASTNode* node = createNode(NODE_FUNC_DEF);
    node->data.funcDef.name = strdup(name);
    node->data.funcDef.body = body;
    return node;
};

ASTNode* createFuncCallNode(char* name) {
    ASTNode* node = createNode(NODE_FUNC_CALL);
    node->data.funcCall.name = strdup(name);
    return node;
};

ASTNode* createArrayDeclNode(char* name, ASTNode* size) {
    // 1. Aloca memória para a struct específica do nó de declaração de array.
    ASTNode* node = createNode(NODE_ARRAY_DECL);

    // 2. Verifica se a alocação de memória foi bem-sucedida.
    if (!node) {
        fprintf(stderr, "Erro: Falha ao alocar memória para o nó de declaração de array.\n");
        exit(1); // Encerra o programa em caso de falha crítica.
    }

    // 3. Preenche os campos da struct.
    node->type = NODE_ARRAY_DECL; // Define o tipo do nó.
    node->data.arrayDeclNode.name = name;           // Armazena o nome do array.
    node->data.arrayDeclNode.size = size;           // Armazena a sub-árvore que representa o tamanho.

    // 4. Retorna o ponteiro para o nó, convertido para o tipo base ASTNode*.
    return (ASTNode*) node;
}

ASTNode* createArrayAccessNode(ASTNode* arrayName, ASTNode* index) {
    // 1. Aloca memória para a struct específica do nó de acesso a array.
    ASTNode* node = createNode(NODE_ARRAY_ACCESS);

    // 2. Verifica se a alocação de memória foi bem-sucedida.
    if (!node) {
        fprintf(stderr, "Erro: Falha ao alocar memória para o nó de acesso a array.\n");
        exit(1);
    }

    // 3. Preenche os campos da struct.
    node->type = NODE_ARRAY_ACCESS; // Define o tipo do nó.
    node->data.arrayAccessNode.arrayName = arrayName;    // Armazena o nó do nome do array.
    node->data.arrayAccessNode.index = index;            // Armazena a sub-árvore que representa o índice.

    // 4. Retorna o ponteiro para o nó, convertido para o tipo base ASTNode*.
    return (ASTNode*) node;
}

void printAst(ASTNode* node, int level) {
    if (!node) return;

    if (node->type == NODE_STMT_LIST) {
        printAst(node->data.stmtList.statement, level);
        printAst(node->data.stmtList.next, level);
        return;

    }
            
    for (int i = 0; i < level; i++) printf("  ");

    switch (node->type) {
        case NODE_NUMBER:
            printf( "Numero: %d\n", node->data.number);
            break;
        case NODE_ID:
            printf( "Variavel: %s\n", node->data.name);
            break;
        case NODE_VAR:
            printf( "Declaracao: %s\n", node->data.name);
            break;
        case NODE_BIN_OP:
            printf( "Operador: %c\n", node->data.binaryOp.op);
            printAst(node->data.binaryOp.left, level + 1);
            printAst(node->data.binaryOp.right, level + 1);
            break;
        case NODE_ASSIGN:
            printf( "Atribuicao: \n");
            printAst(node->data.assign.lvalue, level + 1);
            printAst(node->data.assign.rvalue, level + 1);
            break;
        case NODE_PRINT:
            printf( "Print: \n");
            printAst(node->data.statement.expression, level + 1);
            break;
        case NODE_RETURN:
            printf( "Return: \n");
            printAst(node->data.statement.expression, level + 1);
            break;
        case NODE_FUNC_DEF:
            printf( "Funcao: %s\n", node->data.funcDef.name);
            printf( "Corpo da Funcao: \n");
            printAst(node->data.funcDef.body, level + 1);
            break;
        case NODE_FUNC_CALL:
            printf( "Chamada da Funcao: %s\n", node->data.funcCall.name);
            break;
        case NODE_ARRAY_DECL:
            printf( "Declaração de Array: %s\n", node->data.arrayDeclNode.name);
            printAst(node->data.arrayDeclNode.size, level + 1);
            break;
        case NODE_ARRAY_ACCESS:
            printf( "Acesso do array: \n");
            printAst(node->data.arrayAccessNode.arrayName, level + 1);
            printAst(node->data.arrayAccessNode.index, level + 1);
            break;
        default:
            printf( "Tipo de no desconhecido \n");
            break;
    }
}

void freeAst(ASTNode* node) {
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
            freeAst(node->data.binaryOp.left);
            freeAst(node->data.binaryOp.right);
            break;
        case NODE_ASSIGN:
            freeAst(node->data.assign.lvalue);
            freeAst(node->data.assign.rvalue);
            break;
        case NODE_PRINT:
        case NODE_RETURN:
            freeAst(node->data.statement.expression); // <-- MUDANÇA: freeAst() para a expressão filha
            break;
        case NODE_STMT_LIST:
            freeAst(node->data.stmtList.statement);
            freeAst(node->data.stmtList.next);
            break;
        case NODE_FUNC_DEF:
            free(node->data.funcDef.name);
            freeAst(node->data.funcDef.body);
            break;
        case NODE_ARRAY_DECL:
            free(node->data.arrayDeclNode.name);
            freeAst(node->data.arrayDeclNode.size);
            break;

        case NODE_ARRAY_ACCESS:
            freeAst(node->data.arrayAccessNode.arrayName);
            freeAst(node->data.arrayAccessNode.index);
            break;

        default:
            break;
    }

    free(node);
}

const char* nodeTypeToString(NodeType type) {
    switch (type) {
        case NODE_NUMBER: return "NODE_NUMBER";
        case NODE_ID: return "NODE_ID";
        case NODE_BIN_OP: return "NODE_BIN_OP";
        case NODE_VAR: return "NODE_VAR";
        case NODE_ASSIGN: return "NODE_ASSIGN";
        case NODE_PRINT: return "NODE_PRINT";
        case NODE_RETURN: return "NODE_RETURN";
        case NODE_STMT_LIST: return "NODE_STMT_LIST";
        case NODE_FUNC_CALL: return "NODE_FUNC_CALL";
        case NODE_FUNC_DEF: return "NODE_FUNC_DEF";
        case NODE_ARRAY_DECL: return "NODE_ARRAY_DECL";
        case NODE_ARRAY_ACCESS: return "NODE_ARRAY_ACCESS";
        default: return "UNKNOWN_NODE";
    }
}