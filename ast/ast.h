#ifndef AST_H
#define AST_H

typedef enum {

    // Expressões
    NODE_NUMBER,
    NODE_ID,
    NODE_BIN_OP,

    // Comandos (Statements)
    NODE_VAR,
    NODE_ASSIGN,
    NODE_PRINT,
    NODE_RETURN,

    // Estruturas
    NODE_STMT_LIST,
    NODE_FUNC_CALL,
    NODE_FUNC_DEF,
} NodeType;

// Estrutura da Árvore Sintática Abstrata (AST)
typedef struct ASTNode {
    NodeType type;

    union {
        int number; // Para NODE_NUMBER
        char* name; // PARA NODE_ID e NODE_VAR

        struct {
            char op; // operador: '+', '-', '*', '/'
            struct ASTNode* left;
            struct ASTNode* right;
        } binary_op; // Para NODE_BIN_OP
        
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
        } stmt_list; // Para NODE_STMT_LIST
        
        struct {
            char* name;
            struct ASTNode* body;   // corpo da função
        } func_def; // Para NODE_FUNC_DEF

        struct {
            char* name;
        } func_call; // Para NODE_FUNC_CALL

    } data;

} ASTNode;

// Funções para criar nós da AST

ASTNode* create_number_node(int value);
ASTNode* create_id_node(char* name);
ASTNode* create_var_node(char* name);

ASTNode* create_bin_op_node(char op, ASTNode* left, ASTNode* right);
ASTNode* create_assign_node(ASTNode* lvalue, ASTNode* rvalue);
ASTNode* create_print_node(ASTNode* expression);
ASTNode* create_return_node(ASTNode* expression);

ASTNode* create_stmt_list_node(ASTNode* statement, ASTNode* next);
ASTNode* create_func_def_node(char* name, ASTNode* body);
ASTNode* create_func_call_node(char* name);

void print_ast(ASTNode* node, int level);
void free_ast(ASTNode* node);

#endif 
