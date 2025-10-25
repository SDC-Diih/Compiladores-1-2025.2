#ifndef AST_H
#define AST_H

typedef enum {
    // Expressões
    NODE_NUMBER,
    NODE_FLOAT,      // Novo tipo para literais float
    NODE_ID,

    // Comandos (Statements)
    NODE_BIN_OP,
    NODE_VAR,
    NODE_ASSIGN,
    NODE_PRINT,
    NODE_RETURN,

    // Estruturas
    NODE_STMT_LIST,
    NODE_FUNC_CALL,
    NODE_FUNC_DEF,

    // Array
    NODE_ARRAY_DECL,
    NODE_ARRAY_ACCESS,
} NodeType;

// Enum para tipos de dados
typedef enum {
    DATA_TYPE_INT,
    DATA_TYPE_FLOAT
} DataType;

// Estrutura para representar valores (int ou float)
typedef struct {
    DataType type;
    union {
        int intValue;
        float floatValue;
    } value;
} Value;

// Estrutura da Árvore Sintática Abstrata (AST)
typedef struct ASTNode {
    NodeType type;

    union {
        int number;      // Para NODE_NUMBER (mantido por compatibilidade)
        float floatNum;  // Para NODE_FLOAT
        char* name;      // PARA NODE_ID e NODE_VAR

        struct {
            DataType varType;  // Tipo da variável (int ou float)
            char* name;
        } varDecl;  // Para NODE_VAR com tipo

        struct {
            char op; // operador: '+', '-', '*', '/'
            struct ASTNode* left;
            struct ASTNode* right;
        } binaryOp; // Para NODE_BIN_OP
        
        struct {
            struct ASTNode* lvalue; // variável
            struct ASTNode* rvalue; // expressão
        } assign; // Para NODE_ASSIGN

        struct {
            struct ASTNode* expression; 
        } statement; // Para NODE_PRINT e NODE_RETURN

        struct {
            struct ASTNode* statement;
            struct ASTNode* next;
        } stmtList; // Para NODE_STMT_LIST
        
        struct {
            char* name;
            struct ASTNode* body;   // corpo da função
        } funcDef; // Para NODE_FUNC_DEF

        struct {
            char* name;
        } funcCall; // Para NODE_FUNC_CALL

        // Novo nó para declaração de array
        struct{
            char *name;
            struct ASTNode *size; // O tamanho pode ser uma expressão, ex: arr[x+1]
        }arrayDeclNode;

        // Novo nó para acesso a um elemento do array
        struct  {
            struct ASTNode *arrayName; // Nó do tipo ID
            struct ASTNode *index;    // A expressão do índice
        }arrayAccessNode;

    } data;

} ASTNode;

// Funções para criar nós da AST
ASTNode* createNumberNode(int value);
ASTNode* createFloatNode(float value);  
ASTNode* createIdNode(char* name);
ASTNode* createVarNode(char* name);
ASTNode* createVarNodeWithType(DataType type, char* name);  

ASTNode* createBinOpNode(char op, ASTNode* left, ASTNode* right);
ASTNode* createAssignNode(ASTNode* lvalue, ASTNode* rvalue);
ASTNode* createPrintNode(ASTNode* expression);
ASTNode* createReturnNode(ASTNode* expression);

ASTNode* createStmtListNode(ASTNode* statement, ASTNode* next);
ASTNode* createFuncDefNode(char* name, ASTNode* body);
ASTNode* createFuncCallNode(char* name);

void printAst(ASTNode* node, int level);
void freeAst(ASTNode* node);

// Funções para Array
ASTNode* createArrayDeclNode(char* name, ASTNode* size);
ASTNode* createArrayAccessNode(ASTNode* arrayName, ASTNode* index);

const char* nodeTypeToString(NodeType type);

#endif