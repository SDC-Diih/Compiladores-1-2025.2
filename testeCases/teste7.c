// Teste de função com variáveis globais

int global = 100;

int teste() {
    return 50 + global;
}

print global;
int resultado = teste();
print resultado;

// Deve imprimir 100 e depois 150