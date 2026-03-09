#include <stdio.h>

int main() {
    int array[10];
    int i, j, tmp;

    for(i=0; i<10; i++){
        printf("Ingrese un numero (%d/10): ", i+1);
        scanf("%d", &array[i]);
    }

    for(j = 0; j < 9; j++) { 
        for(i = 0; i < 9 - j; i++) {
            if(array[i] > array[i+1]) {
                tmp = array[i];
                array[i] = array[i+1];
                array[i+1] = tmp;
            }
        }
    }

    printf("\nArray Ordenado\n");
    for(i = 0; i < 10; i++) {
        printf("Posicion %d: %d\n", i+1, array[i]);
    }

    return 0;
}