// Teste de if com funções

int maior() {
    int a = 15;
    int b = 10;
    
    if (a > b) {
        return a;
    } else {
        return b;
    }
}

int resultado = maior();
print resultado;  // Deve imprimir 15

int menor() {
    int x = 5;
    int y = 8;
    
    if (x < y) {
        return x;
    } else {
        return y;
    }
}

int res2 = menor();
print res2;  // Deve imprimir 5