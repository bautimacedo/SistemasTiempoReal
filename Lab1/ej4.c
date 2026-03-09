#include <stdio.h>
#include <unistd.h> 

int main() {
    int estado = 0; 
    // 0: Verde, 1: Amarillo, 2: Rojo

    printf("Iniciando simulador de semaforo...\n");

    while(1) { 
        switch(estado) {
            case 0:
                printf("[VERDE] - Cruce permitido (5s)\n");
                sleep(5);
                estado = 1;
                break;
            
            case 1:
                printf("[AMARILLO] - Precaucion (2s)\n");
                sleep(2);
                estado = 2;
                break;

            case 2:
                printf("[ROJO] - Alto (5s)\n");
                sleep(5);
                estado = 0; 
                break;
        }
    }
    return 0;
}