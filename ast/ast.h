#ifndef AST_H
#define AST_H

typedef enum {
    // Expressões
    NODE_NUMBER,
    NODE_FLOAT,
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

    // Condicionais
    NODE_IF,
    NODE_WHILE,
    NODE_FOR,
    NODE_RELATIONAL_OP,
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
        int number;
        float floatNum;
        char* name;

        struct {
            DataType varType;
            char* name;
        } varDecl;

        struct {
            char op;
            struct ASTNode* left;
            struct ASTNode* right;
        } binaryOp;
        
        struct {
            struct ASTNode* lvalue;
            struct ASTNode* rvalue;
        } assign;

        struct {
            struct ASTNode* expression; 
        } statement;

        struct {
            struct ASTNode* statement;
            struct ASTNode* next;
        } stmtList;
        
        struct {
            char* name;
            struct ASTNode* body;
        } funcDef;

        struct {
            char* name;
        } funcCall;

        struct{
            char *name;
            struct ASTNode *size;
        }arrayDeclNode;

        struct  {
            struct ASTNode *arrayName;
            struct ASTNode *index;
        }arrayAccessNode;

        // Novo nó para estruturas condicionais
        struct {
            struct ASTNode* condition;
            struct ASTNode* thenBranch;
            struct ASTNode* elseBranch;
        } ifNode;

        // Novo nó para estrutura while
        struct {
            struct ASTNode* condition;
            struct ASTNode* body;
        } whileNode;

        // Novo nó para estrutura for
        struct {
            struct ASTNode* init;
            struct ASTNode* condition;
            struct ASTNode* increment;
            struct ASTNode* body;
        } forNode;

        // Novo nó para operadores relacionais
        struct {
            char* op; // "==", "!=", "<", ">", "<=", ">="
            struct ASTNode* left;
            struct ASTNode* right;
        } relationalOp;

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

// Funções para estruturas condicionais
ASTNode* createIfNode(ASTNode* condition, ASTNode* thenBranch, ASTNode* elseBranch);
ASTNode* createWhileNode(ASTNode* condition, ASTNode* body);
ASTNode* createForNode(ASTNode* init, ASTNode* condition, ASTNode* increment, ASTNode* body);
ASTNode* createRelationalOpNode(char* op, ASTNode* left, ASTNode* right);

const char* nodeTypeToString(NodeType type);

#endif