# Compiladores-1-2025.2 -- Grupo 15

- Repositório do Grupo 15 da matéria de Compiladores 1 com o Sergio do semestre 2025.2 da FCTE

## Objetivo: Fazer um Interpretador da Linguagem C

## Equipe:

| Alexandre Beck | Arthur Matos | Diogo (Líder) | Pedro Miguel | Pedro Torreão |
|:----:|:----:|:----:|:----:|:----:|
| [@zzzBECK](https://github.com/zzzBECK) | [@Arthur-Matos](https://github.com/Arthur-Matos) | [@SDC-Diih](https://github.com/SDC-Diih) | [@pedroMADBR](https://github.com/pedroMADBR) | ? |

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

Este projeto pode ser compilado usando o `Makefile`:


### Compilando e Executando


**1. Para Compilar:**
Execute o seguinte comando no terminal:

```bash
make
```

**2. Para Executar:**
Após a compilação, use o comando:

```bash
./src/interp
```

O programa irá aguardar a entrada do código. Após digitar as linhas de código, pressione Ctrl+D (em Linux/macOS) ou Ctrl+Z + Enter (em Windows) para finalizar a entrada. A AST correspondente ao código será impressa no console e também seu resultado.

**3. Para Executar Testes:**
use o comando:

```bash
./src/interp < testeCases/teste[número do teste].c
```

### Compilar e executar ao mesmo tempo

Mais fácil pois necessita de somente um comando

```bash
make run
```

### Limpando os Arquivos Gerados

Para remover todos os arquivos compilados e gerados pelo Bison/Flex (incluindo o executável src/interp), use o comando de limpeza.

```bash
make clean
```

_É uma boa prática rodar este comando antes de compilar uma nova versão ou simplesmente para limpar o diretório do projeto._

## Referências

Documentação oficial e guias de referência para as principais tecnologias utilizadas no projeto:

- **[Linguagem C](https://en.cppreference.com/w/c/language):** Referência completa da linguagem C e sua biblioteca padrão.
- **[Flex](https://westes.github.io/flex/manual/):** Manual oficial do Flex (Fast Lexical Analyzer Generator), a ferramenta utilizada para a análise léxica.
- **[Bison](https://www.gnu.org/software/bison/manual/):** Manual oficial do Bison, o gerador de analisadores sintáticos da GNU utilizado para a análise sintática.
