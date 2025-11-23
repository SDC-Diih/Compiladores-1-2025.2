// Teste de for calculando soma de 1 a 10
// Deve imprimir: 55 (soma de 1+2+3+4+5+6+7+8+9+10)

int sum = 0;
int i;

for (i = 1; i <= 10; i = i + 1) {
    sum = sum + i;
}

print sum;