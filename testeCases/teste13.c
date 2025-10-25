// Teste de float com funções

float pi = 3.14159;

float calcularArea() {
    float raio = 5.0;
    return pi * raio * raio;
}

float area = calcularArea();
print area;  // Deve imprimir aproximadamente 78.53975

// Teste com variáveis globais float
float temperatura = 36.5;

float converterParaFahrenheit() {
    float fahrenheit = temperatura * 1.8 + 32.0;
    return fahrenheit;
}

float tempF = converterParaFahrenheit();
print tempF;  // Deve imprimir 97.7

// Teste de precisão
float x = 0.1;
float y = 0.2;
float z = x + y;
print z;  // Deve imprimir 0.3 (com possíveis imprecisões de ponto flutuante)