#include <stdio.h>
#include <string.h> // <--- ¡La clave está acá!

int main() {
    char texto[100];
    int largo;

    printf("Ingrese una frase: ");
    // Usamos fgets para que no se corte en el primer espacio
    fgets(texto, sizeof(texto), stdin);

    texto[strcspn(texto, "\n")] = 0;

    // USANDO LA LIBRERÍA:
    largo = strlen(texto);

    printf("La frase '%s' tiene %d caracteres.\n", texto, largo);

    return 0;
}