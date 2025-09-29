# Nome do executável final (vai ficar em src/)
EXEC = src/interp

# Caminhos dos arquivos fonte
BISON_FILE = parser/parser.y
FLEX_FILE  = lexer/lexer.l
MAIN_FILE  = src/main.c
AST_FILE = ast/ast.c

# Arquivos que o Bison vai gerar em src/
BISON_C   = src/parser.tab.c
BISON_H   = src/parser.tab.h

# Arquivo gerado pelo Flex em src/
FLEX_C    = src/lex.yy.c

# Ferramentas (permitem override via ambiente, ex: BISON=/opt/local/bin/bison make)
BISON ?= bison
FLEX  ?= flex
CC    ?= gcc

# Flags
CFLAGS  += -Isrc -Iast
BISON_FLAGS = -d -o $(BISON_C)   # -d gera .h, -o muda saída .c
FLEX_FLAGS  = -o $(FLEX_C)       # gera lex.yy.c em src/

# Linkagem condicional por SO
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)          # macOS
  LDFLAGS = -ll                   # libl no macOS (em vez de -lfl)
else                               # Linux e outros
  LDFLAGS = -lfl                  # libfl (Flex)
endif

.PHONY: all clean run

# Alvo padrão
all: $(EXEC)

# Regra para gerar o executável
$(EXEC): $(BISON_C) $(FLEX_C) $(MAIN_FILE) $(AST_FILE)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# Regra para rodar o Bison
$(BISON_C) $(BISON_H): $(BISON_FILE)
	$(BISON) $(BISON_FLAGS) $(BISON_FILE)

# Regra para rodar o Flex (depende do header do Bison)
$(FLEX_C): $(FLEX_FILE) $(BISON_H)
	$(FLEX) $(FLEX_FLAGS) $(FLEX_FILE)

# Executar o programa (se quiser)
run: $(EXEC)
	./$(EXEC)

# Limpeza
clean:
	rm -f $(EXEC) $(BISON_C) $(BISON_H) $(FLEX_C)