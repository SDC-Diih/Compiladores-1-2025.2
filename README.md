# Compiladores-1-2025.2 -- Grupo 15

- Repositório do Grupo 15 da matéria de Compiladores 1 com o Sergio do semestre 2025.2 da FCTE

## Objetivo: Fazer um Interpretador da Linguagem C

## Funcionalidades

Nosso interpretador oferece suporte para um subconjunto essencial da linguagem C, incluindo:

- **Análise Léxica e Sintática:**
  - Tokenização do código-fonte.
  - Análise sintática com tratamento e exibição de erros.

- **Tipos de Dados e Variáveis:**
  - Declaração de variáveis dos tipos `int`, `float` e `char`.
  - Suporte a strings através de `char*`.

- **Controle de Fluxo:**
  - Estruturas condicionais: `if` e `else`.
  - Laços de repetição: `for` e `while`.

- **Expressões:**
  - Operadores aritméticos: `+`, `-`, `*`, `/`.

- **Funções:**
  - Execução  de funções e execução a partir de uma função principal `main()`.


## Pré-requisitos

Necessário utilizar Linux, WSL ou macOS
Necessário instalar as seguintes ferramentas do C: Bison e flex

## Referências

Documentação oficial e guias de referência para as principais tecnologias utilizadas no projeto:

- **[Linguagem C](https://en.cppreference.com/w/c/language):** Referência completa da linguagem C e sua biblioteca padrão.
- **[Flex](https://westes.github.io/flex/manual/):** Manual oficial do Flex (Fast Lexical Analyzer Generator), a ferramenta utilizada para a análise léxica.
- **[Bison](https://www.gnu.org/software/bison/manual/):** Manual oficial do Bison, o gerador de analisadores sintáticos da GNU utilizado para a análise sintática.
