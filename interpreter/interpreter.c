#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "interpreter.h"
#include "../ast/ast.h"

typedef enum {
    TYPE_INT,
    TYPE_FLOAT,
    TYPE_ARRAY
} SymbolType;

// Estrutura para os dados de um array
typedef struct {
    int size;
    int *elements;
} ArrayData;

// O símbolo pode ser um inteiro, float OU um array
typedef struct Symbol {
    char *name;
    SymbolType type;

    union {
        int intValue;
        float floatValue;
        ArrayData arrayData;
    } data;

    struct Symbol *next;
} Symbol;

Symbol *symbolTable = NULL; 

typedef struct Function {
    char *name;
    Value returnValue;  // Mudado para Value
    struct ASTNode *body;
    struct Function *next;
} Function;

Function *functionTable = NULL;
Function *currentFunction = NULL;

Symbol* findSymbol(char *name) {
    Symbol *s = symbolTable;
    while(s) {
        if(strcmp(s->name, name) == 0) {
            return s;
        }
        s = s->next;
    }
    return NULL;
}

void addSymbolForInt(char *name) {
    if(findSymbol(name) != NULL) {
        fprintf(stderr, "Erro: Variavel '%s' ja declarada.\n", name);
        exit(1);
    }
    Symbol *s = (Symbol*)malloc(sizeof(Symbol));
    s->name = strdup(name);
    s->type = TYPE_INT;     
    s->data.intValue = 0;
    s->next = symbolTable;
    symbolTable = s;
}

void addSymbolForFloat(char *name) {
    if(findSymbol(name) != NULL) {
        fprintf(stderr, "Erro: Variavel '%s' ja declarada.\n", name);
        exit(1);
    }
    Symbol *s = (Symbol*)malloc(sizeof(Symbol));
    s->name = strdup(name);
    s->type = TYPE_FLOAT;     
    s->data.floatValue = 0.0f;
    s->next = symbolTable;
    symbolTable = s;
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
    newFunc->returnValue.type = DATA_TYPE_INT;
    newFunc->returnValue.value.intValue = 0;
    newFunc->body = body;
    newFunc->next = functionTable;
    functionTable = newFunc;
}

Value evaluateNodeValue(ASTNode* node) {
    Value result;
    result.type = DATA_TYPE_INT;
    result.value.intValue = 0;

    if (!node) {
        return result;
    }

    switch (node->type) {
        case NODE_NUMBER:
            result.type = DATA_TYPE_INT;
            result.value.intValue = node->data.number;
            return result;
        
        case NODE_FLOAT:
            result.type = DATA_TYPE_FLOAT;
            result.value.floatValue = node->data.floatNum;
            return result;
        
        case NODE_ID: {
            Symbol* sym = findSymbol(node->data.name);
            if (!sym) {
                printf("Erro de semantica: Variavel '%s' nao declarada \n", node->data.name);
                exit(1);
            }
            
            if (sym->type == TYPE_INT) {
                result.type = DATA_TYPE_INT;
                result.value.intValue = sym->data.intValue;
            } else if (sym->type == TYPE_FLOAT) {
                result.type = DATA_TYPE_FLOAT;
                result.value.floatValue = sym->data.floatValue;
            } else {
                printf("Erro: Variavel '%s' nao e um inteiro ou float.\n", node->data.name);
                exit(1);
            }
            return result;
        }

        case NODE_ARRAY_ACCESS: {
            Symbol* sym = findSymbol(node->data.arrayAccessNode.arrayName->data.name);
            if (!sym) {
                printf("Erro: Array '%s' nao foi declarado.\n", node->data.arrayAccessNode.arrayName->data.name);
                exit(1);
            }
            if (sym->type != TYPE_ARRAY) {
                printf("Erro: Variavel '%s' nao e um array.\n", node->data.arrayAccessNode.arrayName->data.name);
                exit(1);
            }

            Value indexVal = evaluateNodeValue(node->data.arrayAccessNode.index);
            int index = (indexVal.type == DATA_TYPE_INT) ? indexVal.value.intValue : (int)indexVal.value.floatValue;

            if (index < 0 || index >= sym->data.arrayData.size) {
                printf("Erro: Acesso fora dos limites ao array '%s' no indice %d.\n", sym->name, index);
                exit(1);
            }

            result.type = DATA_TYPE_INT;
            result.value.intValue = sym->data.arrayData.elements[index];
            return result;
        }

        case NODE_BIN_OP: {
            Value leftValue = evaluateNodeValue(node->data.binaryOp.left);
            Value rightValue = evaluateNodeValue(node->data.binaryOp.right);
            
            // Promoção de tipo: se qualquer operando é float, resultado é float
            if (leftValue.type == DATA_TYPE_FLOAT || rightValue.type == DATA_TYPE_FLOAT) {
                result.type = DATA_TYPE_FLOAT;
                float left = (leftValue.type == DATA_TYPE_FLOAT) ? leftValue.value.floatValue : (float)leftValue.value.intValue;
                float right = (rightValue.type == DATA_TYPE_FLOAT) ? rightValue.value.floatValue : (float)rightValue.value.intValue;
                
                switch (node->data.binaryOp.op) {
                    case '+': result.value.floatValue = left + right; break;
                    case '-': result.value.floatValue = left - right; break;
                    case '*': result.value.floatValue = left * right; break;
                    case '/': 
                        if (right == 0.0f) {
                            printf("Erro de execucao: Divisao por zero \n");
                            exit(1);
                        }
                        result.value.floatValue = left / right;
                        break;
                }
            } else {
                result.type = DATA_TYPE_INT;
                switch (node->data.binaryOp.op) {
                    case '+': result.value.intValue = leftValue.value.intValue + rightValue.value.intValue; break;
                    case '-': result.value.intValue = leftValue.value.intValue - rightValue.value.intValue; break;
                    case '*': result.value.intValue = leftValue.value.intValue * rightValue.value.intValue; break;
                    case '/': 
                        if (rightValue.value.intValue == 0) {
                            printf("Erro de execucao: Divisao por zero \n");
                            exit(1);
                        }
                        result.value.intValue = leftValue.value.intValue / rightValue.value.intValue;
                        break;
                }
            }
            return result;
        }

        case NODE_FUNC_CALL: {
            Function* func = findFunction(node->data.funcCall.name);
            if (!func) {
                fprintf(stderr, "Erro Semantico: Funcao '%s' nao foi declarada. \n", node->data.funcCall.name);
                exit(1);
            }
            Function* previousFunction = currentFunction;
            currentFunction = func;
            currentFunction->returnValue.type = DATA_TYPE_INT;
            currentFunction->returnValue.value.intValue = 0;
            evaluateNode(currentFunction->body);
            Value retVal = currentFunction->returnValue;
            currentFunction = previousFunction;
            return retVal;
        }

        default:
            return result;
    }
}

int evaluateNode(ASTNode* node) {
    if (!node) {
        return 0;
    }

    switch (node->type) {
        case NODE_VAR: {
            DataType varType = node->data.varDecl.varType;
            if (varType == DATA_TYPE_INT) {
                addSymbolForInt(node->data.varDecl.name);
            } else if (varType == DATA_TYPE_FLOAT) {
                addSymbolForFloat(node->data.varDecl.name);
            }
            break;
        }

        case NODE_ARRAY_DECL: {
            if (findSymbol(node->data.arrayDeclNode.name) != NULL) {
                printf("Erro: Variavel '%s' ja foi declarada.\n", node->data.arrayDeclNode.name);
                exit(1);
            }
            Value sizeVal = evaluateNodeValue(node->data.arrayDeclNode.size);
            int size = (sizeVal.type == DATA_TYPE_INT) ? sizeVal.value.intValue : (int)sizeVal.value.floatValue;
            
            if (size <= 0) {
                printf("Erro: Tamanho do array deve ser positivo.\n");
                exit(1);
            }

            Symbol *s = (Symbol*)malloc(sizeof(Symbol));
            s->name = strdup(node->data.arrayDeclNode.name);
            s->type = TYPE_ARRAY;
            s->data.arrayData.size = size;
            s->data.arrayData.elements = (int*)calloc(size, sizeof(int));
            
            s->next = symbolTable;
            symbolTable = s;
            break;
        }

        case NODE_ASSIGN: {
            ASTNode* lvalue = node->data.assign.lvalue;
            Value rvalue = evaluateNodeValue(node->data.assign.rvalue);

            if (lvalue->type == NODE_ID) {
                Symbol* sym = findSymbol(lvalue->data.name);
                if (!sym) {
                    printf("Erro de semantica: Variavel '%s' nao foi declarada. \n", lvalue->data.name);
                    exit(1);
                }
                
                if (sym->type == TYPE_INT) {
                    sym->data.intValue = (rvalue.type == DATA_TYPE_INT) ? 
                        rvalue.value.intValue : (int)rvalue.value.floatValue;
                } else if (sym->type == TYPE_FLOAT) {
                    sym->data.floatValue = (rvalue.type == DATA_TYPE_FLOAT) ? 
                        rvalue.value.floatValue : (float)rvalue.value.intValue;
                } else {
                    printf("Erro: Variavel '%s' nao e um inteiro ou float.\n", lvalue->data.name);
                    exit(1);
                }

            } else if (lvalue->type == NODE_ARRAY_ACCESS) {
                Symbol* sym = findSymbol(lvalue->data.arrayAccessNode.arrayName->data.name);
                if (!sym) {
                    printf("Erro: Array '%s' nao foi declarado.\n", lvalue->data.arrayAccessNode.arrayName->data.name);
                    exit(1);
                }
                if (sym->type != TYPE_ARRAY) {
                    printf("Erro: Variavel '%s' nao e um array.\n", lvalue->data.arrayAccessNode.arrayName->data.name);
                    exit(1);
                }
                Value indexVal = evaluateNodeValue(lvalue->data.arrayAccessNode.index);
                int index = (indexVal.type == DATA_TYPE_INT) ? indexVal.value.intValue : (int)indexVal.value.floatValue;
                
                if (index < 0 || index >= sym->data.arrayData.size) {
                    printf("Erro: Acesso fora dos limites ao array '%s' no indice %d.\n", sym->name, index);
                    exit(1);
                }
                sym->data.arrayData.elements[index] = (rvalue.type == DATA_TYPE_INT) ? 
                    rvalue.value.intValue : (int)rvalue.value.floatValue;
            }
            break;
        }

        case NODE_PRINT: {
            Value valueToPrint = evaluateNodeValue(node->data.statement.expression);
            if (valueToPrint.type == DATA_TYPE_INT) {
                printf("%d\n", valueToPrint.value.intValue);
            } else {
                printf("%f\n", valueToPrint.value.floatValue);
            }
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
            Value result = evaluateNodeValue(node);
            return (result.type == DATA_TYPE_INT) ? result.value.intValue : (int)result.value.floatValue;
        }

        case NODE_RETURN: {
            if(!currentFunction) {
                fprintf(stderr, "Erro Semantico: Comando 'return' fora de uma funcao. \n");
                exit(1);
            }
            currentFunction->returnValue = evaluateNodeValue(node->data.statement.expression);
            break;
        }

        default:
            fprintf(stderr, "Erro: No da AST do tipo %d (%s) nao pode ser avaliado. \n", node->type, nodeTypeToString(node->type));
            break;
    }

    return 0;
}