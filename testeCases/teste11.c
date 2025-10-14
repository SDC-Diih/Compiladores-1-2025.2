int x = 10;

int array[10];

array[5] = x;
array[2] = 6;

int y = array[5];
int z = array[2];

print x;
print y; // Tem que retornar 10 -> y = array[5] = x = 10
print z; // Tem que retornar 6 -> z = array[2] = 6