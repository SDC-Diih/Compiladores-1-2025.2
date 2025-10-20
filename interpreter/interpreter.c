
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "interpreter.h"
#include "../ast/ast.h"

typedef enum {
    TYPE_INT,
    TYPE_ARRAY
} SymbolType;

// Estrutura para os dados de um array
typedef struct {
    int size;
    int *elements; // Ponteiro para os elementos alocados
} ArrayData;

// O simbolo pode ser um inteiro OU um array.
typedef struct Symbol {
    char *name;
    SymbolType type; // O tipo nos diz qual parte da union usar

    union {
        int intValue;
        ArrayData arrayData;
    } data;

    struct Symbol *next;
} Symbol;

Symbol *symbolTable = NULL; 

typedef struct Function {
    char *name;
    int returnValue;
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
    s->data.intValue = 0;   // Inicializamos o valor como 0
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
            Symbol* sym = findSymbol(node->data.name);
            if (!sym) {
                printf("Erro de semantica: Variavel '%s' nao declarada \n", node->data.name);
                exit(1);
            }
            // Um ID sozinho deve se referir a um inteiro. Acessar um array
            // sem um índice é um erro no nosso interpretador simples.
            if (sym->type != TYPE_INT) {
                printf("Erro: Variavel '%s' nao e um inteiro.\n", node->data.name);
                exit(1);
            }
            return sym->data.intValue;
        }

        case NODE_ARRAY_ACCESS: {
            // 1. Encontra o array na tabela de símbolos
            Symbol* sym = findSymbol(node->data.arrayAccessNode.arrayName->data.name);
            if (!sym) {
                printf("Erro: Array '%s' nao foi declarado.\n", node->data.arrayAccessNode.arrayName->data.name);
                exit(1);
            }
            if (sym->type != TYPE_ARRAY) {
                printf("Erro: Variavel '%s' nao e um array.\n", node->data.arrayAccessNode.arrayName->data.name);
                exit(1);
            }

            // 2. Calcula o índice
            int index = evaluateNode(node->data.arrayAccessNode.index);

            // 3. Verifica os limites (Bounds Checking)
            if (index < 0 || index >= sym->data.arrayData.size) {
                printf("Erro: Acesso fora dos limites ao array '%s' no indice %d.\n", sym->name, index);
                exit(1);
            }

            // 4. Retorna o valor
            return sym->data.arrayData.elements[index];
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
            addSymbolForInt(node->data.name); // Chama a nova função
            break;

        case NODE_ARRAY_DECL: {
            if (findSymbol(node->data.arrayDeclNode.name) != NULL) {
                printf("Erro: Variavel '%s' ja foi declarada.\n", node->data.arrayDeclNode.name);
                exit(1);
            }
            // 1. Calcula o tamanho do array
            int size = evaluateNode(node->data.arrayDeclNode.size);
            if (size <= 0) {
                printf("Erro: Tamanho do array deve ser positivo.\n");
                exit(1);
            }

            // 2. Cria o novo símbolo
            Symbol *s = (Symbol*)malloc(sizeof(Symbol));
            s->name = strdup(node->data.arrayDeclNode.name);
            s->type = TYPE_ARRAY;
            s->data.arrayData.size = size;
            // calloc aloca e inicializa com zeros
            s->data.arrayData.elements = (int*)calloc(size, sizeof(int));
            
            // 3. Adiciona na tabela
            s->next = symbolTable;
            symbolTable = s;
            break;
        }

        case NODE_ASSIGN: {
            ASTNode* lvalue = node->data.assign.lvalue;
            int rvalue = evaluateNode(node->data.assign.rvalue);

            // Verificamos se a atribuição é para uma variável simples ou um array
            if (lvalue->type == NODE_ID) {
                Symbol* sym = findSymbol(lvalue->data.name);
                if (!sym) {
                    printf("Erro de semantica: Variavel '%s' nao foi declarada. \n", lvalue->data.name);
                    exit(1);
                }
                if (sym->type != TYPE_INT) {
                     printf("Erro: Variavel '%s' nao e um inteiro.\n", lvalue->data.name);
                    exit(1);
                }
                sym->data.intValue = rvalue;

            } else if (lvalue->type == NODE_ARRAY_ACCESS) {
                // Lógica de atribuição para array
                Symbol* sym = findSymbol(lvalue->data.arrayAccessNode.arrayName->data.name);
                 if (!sym) {
                    printf("Erro: Array '%s' nao foi declarado.\n", lvalue->data.arrayAccessNode.arrayName->data.name);
                    exit(1);
                }
                if (sym->type != TYPE_ARRAY) {
                    printf("Erro: Variavel '%s' nao e um array.\n", lvalue->data.arrayAccessNode.arrayName->data.name);
                    exit(1);
                }
                int index = evaluateNode(lvalue->data.arrayAccessNode.index);
                if (index < 0 || index >= sym->data.arrayData.size) {
                    printf("Erro: Acesso fora dos limites ao array '%s' no indice %d.\n", sym->name, index);
                    exit(1);
                }
                sym->data.arrayData.elements[index] = rvalue;
            }
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
            fprintf(stderr, "Erro: No da AST do tipo %d (%s) nao pode ser avaliado. \n", node->type, nodeTypeToString(node->type)); // Adicionei uma função para converter enum para string para facilitar o debug
            break;
    }

    return 0;
}