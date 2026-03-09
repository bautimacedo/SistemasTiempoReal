#include <stdio.h> // <--- 1. Faltaba esta librería esencial

int main() {
    /* Calculadora simple: escribe un programa que permita al usuario ingresar dos números y
    luego realice operaciones básicas como suma, resta, multiplicación y división. */ // <--- 2. Corregí el cierre del comentario

    int num1, num2, resultado, operacion;

    printf("Por favor ingrese la operacion que desea hacer\n1: Suma\n2: Resta\n3: Division\n4: Multiplicacion\n");
    scanf("%d", &operacion);

    printf("Ingrese el primer numero: ");
    scanf("%d", &num1);

    printf("Ingrese el segundo numero: ");
    scanf("%d", &num2);

    switch (operacion) {
        case 1: // <--- 3. IMPORTANTE: El espacio entre 'case' y el número
            resultado = num1 + num2;
            printf("El resultado de la suma es: %d\n", resultado);
            break;

        case 2:
            resultado = num1 - num2;
            printf("El resultado de la resta es: %d\n", resultado);
            break;

        case 3:
            if (num2 != 0) { // Un detalle: evitemos que explote si dividís por cero
                resultado = num1 / num2;
                printf("El resultado de la division es: %d\n", resultado);
            } else {
                printf("Error: No se puede dividir por cero.\n");
            }
            break;

        case 4:
            resultado = num1 * num2;
            printf("El resultado de la multiplicacion es: %d\n", resultado);
            break;
            
        default:
            printf("Opcion no valida.\n");
            break;
    }

    return 0; // Buena práctica para indicar que el programa terminó bien
}