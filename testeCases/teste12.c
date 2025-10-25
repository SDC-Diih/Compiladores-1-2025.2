// Teste de operações com float

float x = 3.14;
float y = 2.5;

print x;
print y;

float soma = x + y;
print soma;  // Deve imprimir 5.64

float mult = x * y;
print mult;  // Deve imprimir 7.85

// Teste de conversão implícita
int a = 10;
float b = 3.5;

float resultado = a + b;
print resultado;  // Deve imprimir 13.5

// Teste de divisão com float
float c = 10.0;
float d = 3.0;
float divisao = c / d;
print divisao;  // Deve imprimir 3.333333

// Teste de mistura int e float
int e = 5;
int f = 2;
float g = e / f;
print g;  // Deve imprimir 2 (divisão inteira convertida para float)