#include <stdio.h>
#include <pigpio.h>

#define BTN_PIN 18
#define LED_PIN 17
#define MAX_MUESTRAS 20

uint32_t latencias[MAX_MUESTRAS];
int contador = 0;
uint32_t min_lat = 0xFFFFFFFF, max_lat = 0, suma_lat = 0;
uint32_t ultimo_tick_procesado = 0; // Para bloqueo manual

void manejador_latencia(int gpio, int level, uint32_t tick_evento) {
    uint32_t tick_software = gpioTick();

    // 1. BLOQUEO MANUAL: Si el evento ocurrió menos de 250ms después del último, lo ignoramos.
    // Esto mata cualquier rebote mecánico del botón.
    if ((tick_evento - ultimo_tick_procesado) < 250000) {
        return; 
    }

    if (level == 0) { // PRESIONADO
        gpioWrite(LED_PIN, 1);
        uint32_t latencia = tick_software - tick_evento;

        if (contador < MAX_MUESTRAS) {
            latencias[contador] = latencia;
            suma_lat += latencia;
            if (latencia < min_lat) min_lat = latencia;
            if (latencia > max_lat) max_lat = latencia;

            printf("Muestra [%d]: Latencia = %u us\n", contador + 1, latencia);
            fflush(stdout);
            contador++;

            if (contador == MAX_MUESTRAS) {
                float promedio = (float)suma_lat / MAX_MUESTRAS;
                printf("\n--- RESULTADOS ESTADÍSTICOS ---\n");
                printf("Muestras: %d | Promedio: %.2f us | JITTER: %u us\n", 
                        MAX_MUESTRAS, promedio, max_lat - min_lat);
                printf("-------------------------------\n");
                
                contador = 0; suma_lat = 0; min_lat = 0xFFFFFFFF; max_lat = 0;
            }
        }
        ultimo_tick_procesado = tick_evento; // Marcamos que ya procesamos este pulso
    } 
    else if (level == 1) { // LIBERADO
        gpioWrite(LED_PIN, 0);
        // No actualizamos ultimo_tick_procesado aquí para permitir detectar el siguiente "press"
    }
}

int main() {
    if (gpioInitialise() < 0) return 1;

    gpioSetMode(LED_PIN, PI_OUTPUT);
    gpioSetMode(BTN_PIN, PI_INPUT);
    gpioSetPullUpDown(BTN_PIN, PI_PUD_UP);

    // Filtro de ruido digital extra (5ms)
    gpioGlitchFilter(BTN_PIN, 5000);

    // Escuchar flancos con 0ms de timeout de librería (lo manejamos nosotros arriba)
    gpioSetISRFunc(BTN_PIN, EITHER_EDGE, 0, manejador_latencia);
    
    printf("Prueba de Latencia.\n");
    fflush(stdout);

    while (1) {
        gpioDelay(1000000);
    }

    gpioTerminate();
    return 0;
}