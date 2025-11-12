# Planejamento de Sprints – Interpretador C

## Sprint 1 – Definição do Projeto
**Objetivos**
- Decidir o escopo inicial do interpretador (Decidido pelo C).
- Configurar ambiente (Flex, Bison, repositório).
- Especificar a primeira versão da gramática básica.

**Entregas**
- Documento descrevendo a linguagem inicial (variáveis inteiras, operações básicas, função `print`).
- Documento de descrição das sprints.
- Ambiente configurado e funcionando com exemplo simples.

**Tarefas**
- [x] Definir tokens: identificadores, números, operadores, `print`.
- [x] Criar repositório e configurar ferramentas.
- [x] Escrever gramática inicial no Bison (.y).
- [x] Escrever regras léxicas no Flex (.l).
- [x] Descrever documento de sprints
- [x] Descrever documento de escopo do interpretador.

## Sprint 2 – Implementação Básica
**Objetivos**
- Construir um interpretador inicial que suporte variáveis inteiras.
- Implementar operações aritméticas (+, -, *, /).
- Adicionar comando `print` simplificado para exibir resultados.

**Entregas**
- Arquivo `.l` com tokens completos para inteiros e operadores.
- Arquivo `.y` com regras para atribuições, expressões e `print`.
- Parser funcionando em exemplos simples de soma, multiplicação e impressão.

**Tarefas**
- [x] Implementar análise léxica para números inteiros, identificadores e operadores.
- [x] Criar regras no Bison para expressões aritméticas e atribuições.
- [x] Criar tabela de símbolos simples.
- [x] Adicionar suporte ao comando `print`.

## Sprint 3 – AST e Análise Semântica Inicial
**Objetivos**
- Criar a árvore sintática abstrata (AST) para representar expressões e comandos.
- Implementar análise semântica básica (variáveis declaradas antes do uso).
- Implementar execução percorrendo a AST.

**Entregas**
- Estrutura da AST funcionando.
- Interpretador recursivo executando a AST.
- Tabela de símbolos inicial para variáveis inteiras.
- Parser gerando AST para expressões, atribuições e `print`.

**Tarefas**
- [x] Implementar nós da AST para operações, atribuições e `print`.
- [x] Implementar execução percorrendo a AST.
- [x] Validar erros básicos (variável não declarada, divisão por zero).
- [x] Testar com exemplos pequenos.

## Sprint 4 – Interpretação da AST e Controle de Fluxo
**Objetivos**

- Adicionar suporte a estruturas de controle (`if`, `while`).

**Entregas**
- Suporte a condicionais e laços.
- Exemplos de teste com laços e decisões.

**Tarefas**
- [X] Implementar suporte a `if` e `while`/`for` (for não incluso)
- [X] Ampliar análise semântica para condições.
- [X] Validar com programas simples.

## Sprint 5 – Funções e Extensões
**Objetivos**
- Incluir suporte básico a funções (Void main).
- Implementar pilha de execução para variáveis locais.
- Adicionar otimizações simples (tentativa).

**Entregas**
- Funções declaradas e chamadas na linguagem.
- Pilha de contexto para escopo local.

**Tarefas**
- [X] Implementar declaração e chamada de funções. 
- [SKIPPED] Criar pilha de variáveis locais. (não incluso)
- [X] Tentar adicionar otimização. 
- [X] Testar funções simples.


## Sprint 6 – Refinamento e Entrega Final
**Objetivos**
- Consolidar todas as funcionalidades do interpretador.
- Corrigir erros e finalizar documentação.
- Preparar apresentação final.

**Entregas**
- Interpretador completo e testado.
- Documentação clara (gramática, exemplos, limitações).
- Apresentação pronta.

**Tarefas**
- [X] Revisar e corrigir bugs.
- [X] Criar testes finais
- [ ] Documentar funcionamento e exemplos.
- [ ] Preparar demo para apresentação final.
