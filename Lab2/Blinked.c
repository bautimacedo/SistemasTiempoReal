#include <stdio.h>
#include <pigpio.h>

#define LED_PIN 17          // GPIO 17 (Cámbialo según tu conexión)
#define INTERVALO 500000    // 500ms en microsegundos

int main() {
    // 1. Inicializar la librería
    if (gpioInitialise() < 0) {
        printf("Error al inicializar pigpio\n");
        return 1;
    }

    // 2. Configurar el pin como salida
    gpioSetMode(LED_PIN, PI_OUTPUT);

    uint32_t tiempoAnterior = gpioTick(); // Marca de tiempo inicial
    int estadoLed = 0;                    // 0 = apagado, 1 = encendido

    printf("Iniciando parpadeo (Presiona Ctrl+C para detener)...\n");

    // 3. Bucle infinito
    while (1) {
        uint32_t tiempoActual = gpioTick();

        // Lógica de timer no bloqueante
        if (tiempoActual - tiempoAnterior >= INTERVALO) {
            estadoLed = !estadoLed; // Conmutar estado (0 a 1, o 1 a 0)
            
            gpioWrite(LED_PIN, estadoLed); // Activar/Desactivar GPIO

            // Imprimir estado según consigna
            if (estadoLed) {
                printf("LED_ON\n");
            } else {
                printf("LED_OFF\n");
            }

            tiempoAnterior = tiempoActual; // Actualizar la marca de tiempo
        }

        // Aquí el CPU está libre para hacer otras tareas simultáneamente
    }

    // Limpieza (aunque en este loop infinito no se llegue aquí)
    gpioTerminate();
    return 0;
}