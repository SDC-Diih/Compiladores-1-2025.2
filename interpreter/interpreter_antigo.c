
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "interpreter.h"
#include "../ast/ast.h"

typedef struct Var {
    char *name;
    int value;
    struct Var *next;
} Var;

typedef struct Function {
    char *name;
    int returnValue;
    struct ASTNode *body;
    struct Function *next;
} Function;

Var *symbolTable = NULL;
Function *functionTable = NULL;
Function *currentFunction = NULL;

Var* findVar(char *name) {
    Var *v = symbolTable;
    while(v) {
        if(strcmp(v->name, name) == 0) {
            return v;
        }
        v = v->next;
    }
    return NULL;
}

void addVar(char *name) {
    if(findVar(name) != NULL) {
        return; // já existe
    }
    Var *v = (Var*)malloc(sizeof(Var));
    v->name = strdup(name);
    v->value = 0;
    v->next = symbolTable;
    symbolTable = v;
}

Function* findFunction(char *name) {
    Function *current = functionTable;
    while(current) {
        if(strcmp(current->name, name) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

void addFunction(char* name, ASTNode* body) {
    if (findFunction(name) != NULL) {
        fprintf(stderr, "Erro Semantico: Funcao '%s' ja foi definida. \n", name);
        exit(1);
    }
    Function* newFunc = (Function*)malloc(sizeof(Function));
    newFunc->name = strdup(name);
    newFunc->returnValue = 0;
    newFunc->body = body;
    newFunc->next = functionTable;
    functionTable = newFunc;
}


int evaluateNode(ASTNode* node) {
    if (!node) {
        return 0;
    }

    switch (node->type) {
        case NODE_NUMBER:
            return node->data.number;
        
        case NODE_ID: {
            Var* var = findVar(node->data.name);
            if (!var) {
                printf("Erro de semantica: Variavel '%s' nao declarada \n", node->data.name);
                exit(1);
            }
            return var->value;
        }

        case NODE_BIN_OP: {
            int leftValue = evaluateNode(node->data.binaryOp.left);
            int rightValue = evaluateNode(node->data.binaryOp.right);

            switch (node->data.binaryOp.op) {
                case '+': return leftValue + rightValue;
                case '-': return leftValue - rightValue;
                case '*': return leftValue * rightValue;
                case '/': 
                    if (rightValue == 0) {
                        printf("Erro de execucao: Divisao por zero \n");
                        exit(1);
                    }
                    return leftValue / rightValue;
            }
            break;
        }

        case NODE_VAR: 
            addVar(node->data.name);
            break;

        case NODE_ASSIGN: {
            Var* var = findVar(node->data.assign.lvalue->data.name);
            if (!var) {
                printf("Erro de semantica: Variavel '%s' nao foi declarada. \n", node->data.assign.lvalue->data.name);
                exit(1);
            }
            var->value = evaluateNode(node->data.assign.rvalue);
            break;
        }

        case NODE_PRINT: {
            int valueToPrint = evaluateNode(node->data.statement.expression);
            printf("%d \n", valueToPrint);
            break;
        }

        case NODE_STMT_LIST: {
            evaluateNode(node->data.stmtList.statement);
            if (node->data.stmtList.next) {
                evaluateNode(node->data.stmtList.next);
            }
            break;
        }

        case NODE_FUNC_DEF: {
            addFunction(node->data.funcDef.name, node->data.funcDef.body);
            break;
        }

        case NODE_FUNC_CALL: {
            Function* func = findFunction(node->data.funcCall.name);
            if (!func) {
                fprintf(stderr, "Erro Semantico: Funcao '%s' nao foi declarada. \n", node->data.funcCall.name);
                exit(1);
            }

            Function* previousFunction = currentFunction;
            currentFunction = func;

            currentFunction->returnValue = 0;

            evaluateNode(currentFunction->body);

            currentFunction = previousFunction;

            return func->returnValue;
        }

        case NODE_RETURN: {
            if(!currentFunction) {
                fprintf(stderr, "Erro Semantico: Comando 'return' fora de uma funcao. \n");
                exit(1);

            }

            currentFunction->returnValue = evaluateNode(node->data.statement.expression);
            break;
        }

        default:
            fprintf(stderr, "Erro: No da AST do tipo %d nao pode ser avaliado. \n", node->type);
            break;
    }

    return 0;
}
