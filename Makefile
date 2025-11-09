# --------------------------------------------------
# Interpretador - Makefile
# --------------------------------------------------

# Executável a ser gerado
EXEC = src/interp

# --- ARQUIVOS FONTE ---
PARSER = parser/parser.y
MAIN = src/main.c
AST_C = ast/ast.c
INTERPRETER_C = interpreter/interpreter.c
FLEX_FILE = lexer/lexer.l

# Arquivos gerados por Bison e Flex
BISON_C = src/parser.tab.c
BISON_H = src/parser.tab.h
FLEX_C  = src/lex.yy.c

# --- FERRAMENTAS ---
BISON ?= bison
FLEX  ?= flex
CC    ?= gcc

# --- FLAGS ---
CFLAGS = -Isrc -Iast
ifdef PRINT_AST
CFLAGS += -DPRINT_AST
endif
BISON_FLAGS = -d -o $(BISON_C)
FLEX_FLAGS  = -o $(FLEX_C)

# Linkagem condicional por SO
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
  LDFLAGS = -ll
else
  LDFLAGS = -lfl
endif

# --- REGRAS DO MAKE ---
.PHONY: all clean run test

# Alvo padrão
all: $(EXEC)

# --------------------------------------------------
# CONSTRUÇÃO
# --------------------------------------------------
$(EXEC): $(PARSER) $(FLEX_FILE) $(MAIN) $(AST_C) $(INTERPRETER_C)
	@echo "--- Compilando o Interpretador ---"
	$(BISON) $(BISON_FLAGS) $(PARSER)
	$(FLEX) $(FLEX_FLAGS) $(FLEX_FILE)
	$(CC) $(CFLAGS) -o $@ $(BISON_C) $(FLEX_C) $(MAIN) $(AST_C) $(INTERPRETER_C) $(LDFLAGS)
	@echo ">>> Executável '$(EXEC)' criado com sucesso."

# --------------------------------------------------
# EXECUÇÃO
# --------------------------------------------------
run: all
	./$(EXEC)

# --------------------------------------------------
# TESTES AUTOMATIZADOS
# --------------------------------------------------
test:
	@echo ">>> Compilando interpretador antes dos testes..."
	@$(MAKE) all PRINT_AST=$(PRINT_AST)
	@echo ">>> Rodando testes automáticos..."
	@OUTPUT_DIR=testeCases; \
	CASES_DIR=$$OUTPUT_DIR; \
	OUTPUT_FILE=$$OUTPUT_DIR/results.txt; \
	mkdir -p $$OUTPUT_DIR; \
	if [ ! -d "$$CASES_DIR" ]; then \
		echo "ERRO: Diretório '$$CASES_DIR' não encontrado!"; \
		exit 1; \
	fi; \
	echo "" > $$OUTPUT_FILE; \
	TEST_COUNT=0; \
	for file in $$(find $$CASES_DIR -maxdepth 1 -type f -name 'teste*.c' | sort -V); do \
		echo "Rodando $$file..."; \
		echo "--------------------------------------------------" >> $$OUTPUT_FILE; \
		echo ">>> START >>> $$(basename $$file)" >> $$OUTPUT_FILE; \
		if timeout 5s ./$(EXEC) < $$file >> $$OUTPUT_FILE 2>&1; then \
			echo "[OK]" >> $$OUTPUT_FILE; \
		else \
			echo "[ERRO ou TIMEOUT]" >> $$OUTPUT_FILE; \
		fi; \
		echo ">>> END >>> $$(basename $$file)\n" >> $$OUTPUT_FILE; \
		TEST_COUNT=$$((TEST_COUNT+1)); \
	done; \
	echo ">>> $${TEST_COUNT} testes executados."; \
	echo ">>> Resultados salvos em $$OUTPUT_FILE"

# --------------------------------------------------
# LIMPEZA
# --------------------------------------------------
clean:
	@echo ">>> Limpando arquivos gerados..."
	@rm -f $(EXEC) $(BISON_C) $(BISON_H) $(FLEX_C) testeCases/results.txt 2>/dev/null || true
	@echo ">>> Limpeza concluída."
