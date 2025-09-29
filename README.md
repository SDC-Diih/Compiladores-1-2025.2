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

- Necessário utilizar Linux, WSL ou macOS
- Necessário instalar as seguintes ferramentas do C: Bison e flex

## Como Compilar e Executar

Este projeto pode ser compilado em dois modos diferentes usando o `Makefile`:

1. **Modo AST**: Gera um executável que constrói e visualiza a Árvore de Sintaxe Abstrata do código de entrada.
2. **Modo Direto**: Gera um executável que interpreta e executa o código de entrada em tempo real.

### Compilando e Executando a Versão AST (Modo Padrão)

Esta versão do interpretador não executa o código diretamente. Em vez disso, ela analisa a sintaxe e gera uma representação visual da Árvore de Sintaxe Abstrata (AST).

**1. Para Compilar:**
Execute o seguinte comando no terminal:

```bash
make ast
```

**2. Para Executar:**
Após a compilação, use o comando:

```bash
./src/interp_ast
```

O programa irá aguardar a entrada do código. Após digitar as linhas de código, pressione Ctrl+D (em Linux/macOS) ou Ctrl+Z + Enter (em Windows) para finalizar a entrada. A AST correspondente ao código será impressa no console.

### Compilando e Executando a Versão de Execução Direta

Esta é a versão original do interpretador, que executa os comandos (como print) e realiza cálculos em tempo real, sem gerar uma AST visível.

**1. Para Compilar:**
Use o alvo direct no comando make:

```bash
make direct
```

**2. Para Executar:**
Após a compilação, use o comando:

```bash
./src/interp_direct
```

O programa irá executar os comandos à medida que os lê. Por exemplo, um comando print irá exibir o valor da variável no console imediatamente.


### Compilar e executar ao mesmo tempo

Mais fácil pois necessita de somente um comando

**Modo Direto**

```bash
make run-direct
```

**Modo AST**

```bash
make run-ast
```

### Limpando os Arquivos Gerados

Para remover todos os arquivos compilados e gerados pelo Bison/Flex (incluindo ambos os executáveis interp_ast e interp_direct), use o comando de limpeza.

```bash
make clean
```

É uma boa prática rodar este comando antes de compilar uma nova versão ou simplesmente para limpar o diretório do projeto.

## Referências

Documentação oficial e guias de referência para as principais tecnologias utilizadas no projeto:

- **[Linguagem C](https://en.cppreference.com/w/c/language):** Referência completa da linguagem C e sua biblioteca padrão.
- **[Flex](https://westes.github.io/flex/manual/):** Manual oficial do Flex (Fast Lexical Analyzer Generator), a ferramenta utilizada para a análise léxica.
- **[Bison](https://www.gnu.org/software/bison/manual/):** Manual oficial do Bison, o gerador de analisadores sintáticos da GNU utilizado para a análise sintática.
