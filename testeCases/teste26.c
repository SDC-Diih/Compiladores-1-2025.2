// Teste de while com operações mais complexas
// Deve imprimir: 100, 90, 70, 40, 0 (cada número em uma linha)

int valor = 100;
int decremento = 10;

while (valor >= 0) {
    print valor;
    valor = valor - decremento;
    decremento = decremento + 10;
}