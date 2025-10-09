# Executáveis a serem gerados
EXEC = src/interp

# --- ARQUIVOS FONTE ---

# Fontes da versão AST
PARSER = parser/parser.y
MAIN = src/main.c
AST_C = ast/ast.c
INTERPRETER_C = interpreter/interpreter.c

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

CFLAGS = -Isrc -Iast
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
.PHONY: all clean run


# Alvo padrão: se o usuário digitar apenas "make"
all: $(EXEC)

# --- REGRAS DE CONSTRUÇÃO ---

# Regra para construir o executável da AST
$(EXEC): $(PARSER) $(FLEX_FILE) $(MAIN) $(AST_C) $(INTERPRETER_C)
	@echo "--- Compilando o Interpretador ---"
	$(BISON) $(BISON_FLAGS) $(PARSER)
	$(FLEX) $(FLEX_FLAGS) $(FLEX_FILE)
	$(CC) $(CFLAGS) -o $@ $(BISON_C) $(FLEX_C) $(MAIN) $(AST_C) $(INTERPRETER_C) $(LDFLAGS)
	@echo ">>> Executável '$(EXEC)' criado com sucesso."

# --- REGRAS AUXILIARES ---

# Regra para rodar a versão AST
run: all
	./$(EXEC)

# Limpeza para todos os arquivos
clean:
	rm -f $(EXEC) $(BISON_C) $(BISON_H) $(FLEX_C)