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
}

ASTNode* createNumberNode(int value) {
    ASTNode* node = createNode(NODE_NUMBER);
    node->data.number = value;
    return node;
}

ASTNode* createFloatNode(float value) {
    ASTNode* node = createNode(NODE_FLOAT);
    node->data.floatNum = value;
    return node;
}

ASTNode* createIdNode(char* name) {
    ASTNode* node = createNode(NODE_ID);
    node->data.name = strdup(name);
    return node;
}

ASTNode* createVarNode(char* name) {
    ASTNode* node = createNode(NODE_VAR);
    node->data.name = strdup(name);
    return node;
}

ASTNode* createVarNodeWithType(DataType type, char* name) {
    ASTNode* node = createNode(NODE_VAR);
    node->data.varDecl.varType = type;
    node->data.varDecl.name = strdup(name);
    return node;
}

ASTNode* createBinOpNode(char op, ASTNode* left, ASTNode* right) {
    ASTNode* node = createNode(NODE_BIN_OP);
    node->data.binaryOp.op = op;
    node->data.binaryOp.left = left;
    node->data.binaryOp.right = right;
    return node;
}

ASTNode* createAssignNode(ASTNode* lvalue, ASTNode* rvalue) {
    ASTNode* node = createNode(NODE_ASSIGN);
    node->data.assign.lvalue = lvalue;
    node->data.assign.rvalue = rvalue;
    return node;
}

ASTNode* createPrintNode(ASTNode* expression) {
    ASTNode* node = createNode(NODE_PRINT);
    node->data.statement.expression = expression;
    return node;
}

ASTNode* createReturnNode(ASTNode* expression) {
    ASTNode* node = createNode(NODE_RETURN);
    node->data.statement.expression = expression;
    return node;
}

ASTNode* createStmtListNode(ASTNode* statement, ASTNode* next) {
    ASTNode* node = createNode(NODE_STMT_LIST);
    node->data.stmtList.statement = statement;
    node->data.stmtList.next = next;
    return node;
}

ASTNode* createFuncDefNode(char* name, ASTNode* body) {
    ASTNode* node = createNode(NODE_FUNC_DEF);
    node->data.funcDef.name = strdup(name);
    node->data.funcDef.body = body;
    return node;
}

ASTNode* createFuncCallNode(char* name) {
    ASTNode* node = createNode(NODE_FUNC_CALL);
    node->data.funcCall.name = strdup(name);
    return node;
}

ASTNode* createArrayDeclNode(char* name, ASTNode* size) {
    ASTNode* node = createNode(NODE_ARRAY_DECL);
    if (!node) {
        fprintf(stderr, "Erro: Falha ao alocar memória para o nó de declaração de array.\n");
        exit(1);
    }
    node->type = NODE_ARRAY_DECL;
    node->data.arrayDeclNode.name = name;
    node->data.arrayDeclNode.size = size;
    return (ASTNode*) node;
}

ASTNode* createArrayAccessNode(ASTNode* arrayName, ASTNode* index) {
    ASTNode* node = createNode(NODE_ARRAY_ACCESS);
    if (!node) {
        fprintf(stderr, "Erro: Falha ao alocar memória para o nó de acesso a array.\n");
        exit(1);
    }
    node->type = NODE_ARRAY_ACCESS;
    node->data.arrayAccessNode.arrayName = arrayName;
    node->data.arrayAccessNode.index = index;
    return (ASTNode*) node;
}

ASTNode* createIfNode(ASTNode* condition, ASTNode* thenBranch, ASTNode* elseBranch) {
    ASTNode* node = createNode(NODE_IF);
    node->data.ifNode.condition = condition;
    node->data.ifNode.thenBranch = thenBranch;
    node->data.ifNode.elseBranch = elseBranch;
    return node;
}

ASTNode* createRelationalOpNode(char* op, ASTNode* left, ASTNode* right) {
    ASTNode* node = createNode(NODE_RELATIONAL_OP);
    node->data.relationalOp.op = strdup(op);
    node->data.relationalOp.left = left;
    node->data.relationalOp.right = right;
    return node;
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
            printf("Numero (int): %d\n", node->data.number);
            break;
        case NODE_FLOAT:
            printf("Numero (float): %f\n", node->data.floatNum);
            break;
        case NODE_ID:
            printf("Variavel: %s\n", node->data.name);
            break;
        case NODE_VAR:
            printf("Declaracao: %s\n", node->data.varDecl.name);
            break;
        case NODE_BIN_OP:
            printf("Operador: %c\n", node->data.binaryOp.op);
            printAst(node->data.binaryOp.left, level + 1);
            printAst(node->data.binaryOp.right, level + 1);
            break;
        case NODE_ASSIGN:
            printf("Atribuicao: \n");
            printAst(node->data.assign.lvalue, level + 1);
            printAst(node->data.assign.rvalue, level + 1);
            break;
        case NODE_PRINT:
            printf("Print: \n");
            printAst(node->data.statement.expression, level + 1);
            break;
        case NODE_RETURN:
            printf("Return: \n");
            printAst(node->data.statement.expression, level + 1);
            break;
        case NODE_FUNC_DEF:
            printf("Funcao: %s\n", node->data.funcDef.name);
            printf("Corpo da Funcao: \n");
            printAst(node->data.funcDef.body, level + 1);
            break;
        case NODE_FUNC_CALL:
            printf("Chamada da Funcao: %s\n", node->data.funcCall.name);
            break;
        case NODE_ARRAY_DECL:
            printf("Declaração de Array: %s\n", node->data.arrayDeclNode.name);
            printAst(node->data.arrayDeclNode.size, level + 1);
            break;
        case NODE_ARRAY_ACCESS:
            printf("Acesso do array: \n");
            printAst(node->data.arrayAccessNode.arrayName, level + 1);
            printAst(node->data.arrayAccessNode.index, level + 1);
            break;
        case NODE_IF:
            printf("If: \n");
            for (int i = 0; i < level + 1; i++) printf("  ");
            printf("Condicao: \n");
            printAst(node->data.ifNode.condition, level + 2);
            for (int i = 0; i < level + 1; i++) printf("  ");
            printf("Then: \n");
            printAst(node->data.ifNode.thenBranch, level + 2);
            if (node->data.ifNode.elseBranch) {
                for (int i = 0; i < level + 1; i++) printf("  ");
                printf("Else: \n");
                printAst(node->data.ifNode.elseBranch, level + 2);
            }
            break;
        case NODE_RELATIONAL_OP:
            printf("Operador Relacional: %s\n", node->data.relationalOp.op);
            printAst(node->data.relationalOp.left, level + 1);
            printAst(node->data.relationalOp.right, level + 1);
            break;
        default:
            printf("Tipo de no desconhecido \n");
            break;
    }
}

void freeAst(ASTNode* node) {
    if (!node) return;

    switch (node->type) {
        case NODE_NUMBER:
        case NODE_FLOAT:
            break;

        case NODE_ID:
        case NODE_FUNC_CALL:
            free(node->data.name); 
            break;

        case NODE_VAR:
            free(node->data.varDecl.name);
            break;

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
            freeAst(node->data.statement.expression);
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
        case NODE_IF:
            freeAst(node->data.ifNode.condition);
            freeAst(node->data.ifNode.thenBranch);
            freeAst(node->data.ifNode.elseBranch);
            break;
        case NODE_RELATIONAL_OP:
            free(node->data.relationalOp.op);
            freeAst(node->data.relationalOp.left);
            freeAst(node->data.relationalOp.right);
            break;
        default:
            break;
    }

    free(node);
}

const char* nodeTypeToString(NodeType type) {
    switch (type) {
        case NODE_NUMBER: return "NODE_NUMBER";
        case NODE_FLOAT: return "NODE_FLOAT";
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
        case NODE_IF: return "NODE_IF";
        case NODE_RELATIONAL_OP: return "NODE_RELATIONAL_OP";
        default: return "UNKNOWN_NODE";
    }
}