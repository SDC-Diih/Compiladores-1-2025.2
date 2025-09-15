# Nome do executável final (vai ficar em src/)
EXEC = src/interp

# Caminhos dos arquivos fonte
BISON_FILE = parser/parser.y
FLEX_FILE  = lexer/lexer.l
MAIN_FILE  = src/main.c

# Arquivos que o Bison vai gerar em src/
BISON_C   = src/parser.tab.c
BISON_H   = src/parser.tab.h

# Arquivo gerado pelo Flex em src/
FLEX_C    = src/lex.yy.c

# Parâmetros opcionais ao Bison e Flex
BISON_FLAGS = -d -o $(BISON_C)   # -d gera .h, -o muda saída .c
FLEX_FLAGS  = -o $(FLEX_C)       # gera lex.yy.c em src/

# Compilador e flags
CC = gcc
CFLAGS =
LDFLAGS = -lfl   # biblioteca do Flex

# Alvo padrão
all: $(EXEC)

# Regra para gerar o executável
$(EXEC): $(BISON_C) $(FLEX_C) $(MAIN_FILE)
	$(CC) $(CFLAGS) -o $@ $(BISON_C) $(FLEX_C) $(MAIN_FILE) $(LDFLAGS)

# Regra para rodar o Bison
$(BISON_C) $(BISON_H): $(BISON_FILE)
	bison $(BISON_FLAGS) $(BISON_FILE)

# Regra para rodar o Flex
$(FLEX_C): $(FLEX_FILE)
	flex $(FLEX_FLAGS) $(FLEX_FILE)

# Limpeza
clean:
	rm -f $(EXEC) $(BISON_C) $(BISON_H) $(FLEX_C)
