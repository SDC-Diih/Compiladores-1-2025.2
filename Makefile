# Executáveis a serem gerados
EXEC_AST = src/interp_ast
EXEC_DIRECT = src/interp_direct

# --- ARQUIVOS FONTE ---

# Fontes da versão AST
AST_PARSER = parser/parser.y
AST_MAIN = src/main.c
AST_C = ast/ast.c

# Fontes da versão de Execução Direta
DIRECT_PARSER = parser/parser_direct.y
DIRECT_MAIN = src/main_direct.c

# Fonte do Lexer 
FLEX_FILE = lexer/lexer.l

# Arquivo gerado pelo bison e Flex em src/

BISON_C = src/parser.tab.c
BISON_H = src/parser.tab.h

FLEX_C = src/lex.yy.c

# Ferramentas (permitem override via ambiente, ex: BISON=/opt/local/bin/bison make)
BISON ?= bison
FLEX  ?= flex
CC    ?= gcc

# Flags

CFLAGS_AST = -Isrc -Iast
CFLAGS_DIRECT = -Isrc
BISON_FLAGS = -d -o $(BISON_C)
FLEX_FLAGS  = -o $(FLEX_C)

# Linkagem condicional por SO
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)          # macOS
  LDFLAGS = -ll                   # libl no macOS (em vez de -lfl)
else                               # Linux e outros
  LDFLAGS = -lfl                  # libfl (Flex)
endif

# --- REGRAS DO MAKE ---
.PHONY: all ast direct clean run-ast run-direct


# Alvo padrão: se o usuário digitar apenas "make", ele fará a versão direta.
all: $(EXEC_DIRECT)

# Alvo para construir a versão AST
ast: $(EXEC_AST)

# Alvo para construir a versão de Execução Direta
direct: $(EXEC_DIRECT)

# --- REGRAS DE CONSTRUÇÃO ---

# Regra para construir o executável da AST
$(EXEC_AST): $(AST_PARSER) $(FLEX_FILE) $(AST_MAIN) $(AST_C)
	@echo "--- Compilando a versão AST ---"
	$(BISON) $(BISON_FLAGS) $(AST_PARSER)
	$(FLEX) $(FLEX_FLAGS) $(FLEX_FILE)
	$(CC) $(CFLAGS_AST) -o $@ $(BISON_C) $(FLEX_C) $(AST_MAIN) $(AST_C) $(LDFLAGS)
	@echo ">>> Executável '$(EXEC_AST)' criado com sucesso."

# Regra para construir o executável de Execução Direta
$(EXEC_DIRECT): $(DIRECT_PARSER) $(FLEX_FILE) $(DIRECT_MAIN)
	@echo "--- Compilando a versão de Execução Direta ---"
	$(BISON) $(BISON_FLAGS) $(DIRECT_PARSER)
	$(FLEX) $(FLEX_FLAGS) $(FLEX_FILE)
	$(CC) $(CFLAGS_DIRECT) -o $@ $(BISON_C) $(FLEX_C) $(DIRECT_MAIN) $(LDFLAGS)
	@echo ">>> Executável '$(EXEC_DIRECT)' criado com sucesso."

# --- REGRAS AUXILIARES ---

# Regra para rodar a versão AST
run-ast: ast
	./$(EXEC_AST)

# Regra para rodar a versão de Execução Direta
run-direct: direct
	./$(EXEC_DIRECT)

# Limpeza para todos os arquivos
clean:
	rm -f $(EXEC_AST) $(EXEC_DIRECT) $(BISON_C) $(BISON_H) $(FLEX_C)