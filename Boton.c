#include <stdio.h>
#include <pigpio.h>

#define BTN_PIN 18
#define LED_PIN 17

// La función de callback recibe el "level" (estado del pin)
void manejador_boton(int gpio, int level, uint32_t tick) {
    if (level == 0) { 
        // Como usamos PULL_UP, 0 significa que el botón cerró el circuito a tierra (presionado)
        gpioWrite(LED_PIN, 1);
        printf("BOTÓN_PRESIONADO\n");
    } 
    else if (level == 1) {
        // 1 significa que el botón se soltó y la resistencia lo subió a 3.3V
        gpioWrite(LED_PIN, 0);
        printf("BOTÓN_LIBERADO\n");
    }
    fflush(stdout); // Fundamental para ver los mensajes por SSH al instante
}

int main() {
    if (gpioInitialise() < 0) return 1;

    // Configurar LED
    gpioSetMode(LED_PIN, PI_OUTPUT);
    gpioWrite(LED_PIN, 0); // Empezar apagado

    // Configurar Botón
    gpioSetMode(BTN_PIN, PI_INPUT);
    gpioSetPullUpDown(BTN_PIN, PI_PUD_UP);

    /* CAMBIO CLAVE: Usamos EITHER_EDGE para que la interrupción 
       salte tanto al bajar (presionar) como al subir (soltar).
    */
    gpioSetISRFunc(BTN_PIN, EITHER_EDGE, 200, manejador_boton);

    printf("Esperando interrupciones... (Ctrl+C para salir)\n");
    fflush(stdout);

    while (1) {
        gpioDelay(1000000); // El programa principal no hace nada, solo espera
    }

    gpioTerminate();
    return 0;
}