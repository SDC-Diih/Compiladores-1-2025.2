// Teste de while calculando soma de 1 a 10
// Deve imprimir: 55 (soma de 1+2+3+4+5+6+7+8+9+10)

int sum = 0;
int num = 1;

while (num <= 10) {
    sum = sum + num;
    num = num + 1;
}

print sum;