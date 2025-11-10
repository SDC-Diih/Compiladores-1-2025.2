# Compiladores-1-2025.2 -- Grupo 15

- Repositório do Grupo 15 da matéria de Compiladores 1 com o Sergio do semestre 2025.2 da FCTE

## Objetivo: Fazer um Interpretador da Linguagem C

## Equipe:

| Alexandre Beck | Arthur Matos | Diogo (Líder) | Pedro Miguel | Pedro Torreão |
|:----:|:----:|:----:|:----:|:----:|
| [@zzzBECK](https://github.com/zzzBECK) | [@Arthur-Matos](https://github.com/Arthur-Matos) | [@SDC-Diih](https://github.com/SDC-Diih) | [@pedroMADBR](https://github.com/pedroMADBR) | [@PedroTorreao21](https://github.com/PedroTorreao21) |

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

Este projeto pode ser compilado usando o Makefile. O Makefile foi configurado para permitir a compilação com ou sem a impressão da Árvore Sintática Abstrata (AST) para fins de depuração.

### 1. Compilando o Interpretador

#### Compilação Padrão (Sem AST)

Para compilar o interpretador sem a impressão da AST (modo de execução normal), execute:

```bash
make
```

Isso irá gerar o executável em src/interp.

#### Compilação com Impressão da AST

Para compilar o interpretador habilitando a visualização da AST antes da execução do código, passe a variável PRINT_AST=1 para o make:

```bash
make PRINT_AST=1
```

Isso define a flag PRINT_AST que é usada pelo src/main.c para imprimir a árvore.

### 2. Executando o Interpretador

Após a compilação, você pode executar o interpretador de duas formas:

#### Modo Interativo

Execute o programa e digite o código C diretamente no terminal:
```bash
./src/interp
```

O programa irá aguardar a entrada do código. Após digitar as linhas de código, pressione Ctrl+D (em Linux/macOS) ou Ctrl+Z + Enter (em Windows) para finalizar a entrada.

O interpretador irá executar o código. Se compilado com PRINT_AST=1, ele exibirá a AST antes de imprimir o resultado da execução.

#### Executando Arquivos de Teste

Você pode executar um arquivo .c diretamente passando-o como entrada (stdin):

```bash
./src/interp < testeCases/teste1.c
```

### 3. Comandos Adicionais do Makefile

O Makefile inclui outros alvos úteis:

#### make run 

Compila e executa o interpretador em modo interativo. Por padrão, compila sem AST.

```bash
make run
```

Para compilar com AST e executar:

```bash
make run PRINT_AST=1
```

#### make test 

Este comando compila o interpretador e executa automaticamente todos os arquivos teste*.c localizados no diretório testeCases. Os resultados de todos os testes (incluindo a saída da AST, se habilitada) são concatenados e salvos em testeCases/results.txt.

```bash
make test
```

Para rodar os testes e incluir a impressão da AST nos resultados:

```bash
make test PRINT_AST=1
```

#### make clean 

Remove todos os arquivos compilados e gerados pelo Bison/Flex (incluindo o executável src/interp e o arquivo testeCases/results.txt).

```bash
make clean
```


## Referências

Documentação oficial e guias de referência para as principais tecnologias utilizadas no projeto:

- **[Linguagem C](https://en.cppreference.com/w/c/language):** Referência completa da linguagem C e sua biblioteca padrão.
- **[Flex](https://westes.github.io/flex/manual/):** Manual oficial do Flex (Fast Lexical Analyzer Generator), a ferramenta utilizada para a análise léxica.
- **[Bison](https://www.gnu.org/software/bison/manual/):** Manual oficial do Bison, o gerador de analisadores sintáticos da GNU utilizado para a análise sintática.
