// Teste de múltiplas funções

int calcula() {
    return 5 * 8;
}

int dobra() {
    return calcula() * 2;
}

int valor;
valor = dobra();
print valor;

// Deve imprimir 80 (5 * 8 * 2)