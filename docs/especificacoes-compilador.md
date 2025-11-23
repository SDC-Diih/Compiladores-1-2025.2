# Especificações do Interpretador C Limitado

## Visão Geral

Este documento especifica as funcionalidades suportadas e não suportadas pelo nosso interpretador de C limitado, desenvolvido usando Flex e Bison.

## Funcionalidades Suportadas

### 1. Tipos de Dados

#### 1.1 Tipos Primitivos
- **`int`**: Números inteiros de 32 bits
  - Exemplo: `int x = 42;`
  - Suporta valores negativos e positivos
- **`float`**: Números de ponto flutuante
  - Exemplo: `float pi = 3.14159;`
  - Suporte a notação decimal

#### 1.2 Arrays
- **Arrays unidimensionais de inteiros**
  - Declaração: `int array[tamanho];`
  - Acesso: `array[indice]`
  - Atribuição: `array[indice] = valor;`
  - Verificação de limites em tempo de execução

### 2. Declaração e Atribuição de Variáveis

#### 2.1 Declaração Simples
```c
int variavel;
float numero;
```

#### 2.2 Declaração com Inicialização
```c
int x = 10;
float y = 3.14;
```

#### 2.3 Atribuição
```c
x = 20;
y = x + 5.5;
```

### 3. Operadores

#### 3.1 Operadores Aritméticos
- **Adição**: `+`
- **Subtração**: `-`
- **Multiplicação**: `*`
- **Divisão**: `/`
  - Divisão por zero é detectada e gera erro em tempo de execução

#### 3.2 Operadores Relacionais
- **Igualdade**: `==`
- **Desigualdade**: `!=`
- **Menor que**: `<`
- **Maior que**: `>`
- **Menor ou igual**: `<=`
- **Maior ou igual**: `>=`

#### 3.3 Conversão Automática de Tipos
- Conversão implícita entre `int` e `float` nas operações
- Resultado de operação mista (`int` + `float`) é `float`

### 4. Estruturas de Controle

#### 4.1 Estrutura Condicional - IF
```c
if (condicao) {
    // comandos
}

if (condicao) {
    // comandos if
} else {
    // comandos else
}
```

#### 4.2 Loop WHILE
```c
while (condicao) {
    // comandos
}
```

#### 4.3 Loop FOR
```c
for (inicializacao; condicao; incremento) {
    // comandos
}
```
- Exemplo: `for (i = 0; i < 10; i = i + 1) { ... }`

### 5. Funções

#### 5.1 Definição de Função
```c
int nomeFuncao() {
    // corpo da função
    return valor;
}

float outraFuncao() {
    // corpo da função
    return 3.14;
}
```

#### 5.2 Chamada de Função
```c
int resultado = nomeFuncao();
```

#### 5.3 Comando Return
- Obrigatório para funções que retornam valores
- Funções sem `return` explícito retornam 0 (para `int`) ou 0.0 (para `float`)

### 6. Comando de Saída

#### 6.1 Print
```c
print variavel;
print expressao;
print 42;
```
- Imprime o valor seguido de quebra de linha
- Suporta tanto `int` quanto `float`

### 7. Comentários

#### 7.1 Comentário de Linha
```c
// Este é um comentário de linha
```

#### 7.2 Comentário de Bloco
```c
/*
  Este é um
  comentário de bloco
*/
```

### 8. Análise de Erros

#### 8.1 Erros Léxicos
- Caracteres inválidos são detectados e reportados

#### 8.2 Erros Sintáticos
- Erros de sintaxe são reportados com mensagens descritivas

#### 8.3 Erros Semânticos
- Variável não declarada
- Função não declarada
- Comando `return` fora de função
- Redeclaração de variáveis
- Acesso fora dos limites de array

#### 8.4 Erros de Execução
- Divisão por zero
- Overflow de array

## Funcionalidades NÃO Suportadas

### 1. Tipos de Dados Não Suportados
- **`char`**: Caracteres individuais
- **`string`**: Strings/arrays de caracteres
- **`double`**: Precisão dupla
- **`long`**: Inteiros longos
- **`short`**: Inteiros curtos
- **Ponteiros**: `int*`, `float*`, etc.
- **Structs**: Estruturas de dados customizadas
- **Unions**: Uniões
- **Enums**: Enumerações

### 2. Arrays Limitados
- **Arrays multidimensionais**: `int matrix[5][5]`
- **Arrays de tipos diferentes de int**
- **Inicialização de arrays**: `int arr[3] = {1, 2, 3}`
- **Arrays dinâmicos**

### 3. Operadores Não Suportados
- **Operadores lógicos**: `&&`, `||`, `!`
- **Operadores bitwise**: `&`, `|`, `^`, `~`, `<<`, `>>`
- **Operadores de incremento/decremento**: `++`, `--`
- **Operadores compostos**: `+=`, `-=`, `*=`, `/=`
- **Operador ternário**: `? :`
- **Operador de endereço**: `&`
- **Operador de indireção**: `*`

### 4. Estruturas de Controle Avançadas
- **Switch/Case**: Estrutura de múltipla escolha
- **Do-While**: Loop com teste no final
- **Break/Continue**: Controle de loop
- **Goto**: Salto incondicional

### 5. Funções Avançadas
- **Parâmetros de função**: Funções só podem ser sem parâmetros
- **Sobrecarga de funções**: Múltiplas funções com mesmo nome
- **Recursão**: Embora tecnicamente possível, não foi testada extensivamente
- **Variáveis locais com escopo**: Todas as variáveis são globais
- **Função `main`**: Não há função principal obrigatória

### 6. Funcionalidades da Linguagem C
- **Preprocessor**: `#include`, `#define`, `#ifdef`, etc.
- **Headers**: Inclusão de arquivos de cabeçalho
- **Bibliotecas**: `stdio.h`, `stdlib.h`, `math.h`, etc.
- **Entrada de dados**: `scanf`, `getchar`, etc.
- **Manipulação de arquivos**: `fopen`, `fread`, `fwrite`, etc.

### 7. Gerenciamento de Memória
- **Alocação dinâmica**: `malloc`, `calloc`, `free`
- **Ponteiros**: Aritmética de ponteiros
- **Referências**: Passagem por referência

### 8. Funcionalidades Avançadas
- **Typedef**: Definição de novos tipos
- **Const**: Variáveis constantes
- **Static**: Variáveis estáticas
- **Register**: Sugestão de registro
- **Volatile**: Variáveis voláteis
- **Extern**: Variáveis externas

## Limitações Técnicas

### 1. Escopo de Variáveis
- Todas as variáveis são globais
- Não há suporte a variáveis locais em funções
- Não há controle de escopo de bloco

### 2. Gerenciamento de Memória
- Arrays têm tamanho fixo definido em tempo de compilação
- Não há garbage collection
- Memory leaks podem ocorrer em caso de erro

### 3. Tipos de Erro
- Alguns erros só são detectados em tempo de execução
- Mensagens de erro podem ser limitadas
- Não há recuperação de erros durante a execução

### 4. Performance
- Interpretador, não compilador (execução mais lenta)
- Não há otimizações de código
- AST é reconstruída a cada execução

## Exemplos de Código Válido

### Exemplo 1: Operações Básicas
```c
int x = 10;
int y = 20;
int soma = x + y;
print soma; // Imprime: 30
```

### Exemplo 2: Estruturas de Controle
```c
int i = 0;
while (i < 5) {
    print i;
    i = i + 1;
}
```

### Exemplo 3: Funções
```c
int calcular() {
    return 10 * 5;
}

int resultado = calcular();
print resultado; // Imprime: 50
```

### Exemplo 4: Arrays
```c
int arr[5];
arr[0] = 10;
arr[1] = 20;
print arr[0]; // Imprime: 10
```

## Casos de Teste

O interpretador foi testado com 36 casos de teste que cobrem:
- Testes 1-18: Funcionalidades básicas (variáveis, operações, funções, arrays, condicionais)
- Testes 19-27: Loops WHILE
- Testes 28-36: Loops FOR

Todos os testes incluem comentários explicando o comportamento esperado e são utilizados para validação da implementação.

## Como Compilar e Executar

### Pré-requisitos
- Sistema Linux, WSL ou macOS
- Ferramentas instaladas: `flex`, `bison`, `gcc`

### Compilação

#### Compilação Padrão
Para compilar o interpretador sem impressão da AST:
```bash
make
```

#### Compilação com Impressão da AST
Para compilar habilitando a visualização da AST (útil para depuração):
```bash
make PRINT_AST=1
```

### Execução

#### Modo Interativo
Execute o interpretador e digite código diretamente:
```bash
make run
```
ou após compilar:
```bash
./src/interp
```

Para finalizar a entrada, pressione `Ctrl+D` (Linux/macOS) ou `Ctrl+Z + Enter` (Windows).

#### Executando Arquivos
Para executar um arquivo de teste específico:
```bash
./src/interp < testeCases/teste1.c
```

### Execução dos Testes

#### Executar Todos os Testes
Para compilar e executar automaticamente todos os 36 casos de teste:
```bash
make test
```

Os resultados são salvos em `testeCases/results.txt` contendo:
- Saída de cada teste
- Status de sucesso/erro
- Timeouts (limite de 5 segundos por teste)

#### Executar Testes com AST
Para ver a AST durante os testes:
```bash
make test PRINT_AST=1
```

### Comandos Adicionais

#### Limpeza
Para remover arquivos compilados e resultados:
```bash
make clean
```

#### Compilação e Execução em Uma Etapa
```bash
make run PRINT_AST=1  # Compila com AST e executa
```

### Exemplos de Uso

1. **Teste rápido de funcionalidades básicas:**
   ```bash
   make test
   cat testeCases/results.txt | grep "teste1.c" -A 10
   ```

2. **Verificar implementação do while:**
   ```bash
   ./src/interp < testeCases/teste19.c
   ```

3. **Verificar implementação do for:**
   ```bash
   ./src/interp < testeCases/teste28.c
   ```

4. **Debugar com AST visível:**
   ```bash
   make PRINT_AST=1
   ./src/interp < testeCases/teste16.c
   ```