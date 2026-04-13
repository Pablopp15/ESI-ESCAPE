#include <stdio.h>
#include <string.h>
#include "puzles.h"
#include "conexiones.h" // Ojo, asegúrate de que esto esté incluido

void resolver_puzle(int id_sala_actual, Puzle puzles[], int num_puzles, Conexion conexiones[], int num_conexiones) {
    int puzle_encontrado = 0;

    for (int i = 0; i < num_puzles; i++) {
        if (puzles[i].id_sala == id_sala_actual) {
            puzle_encontrado = 1;

            // 1. Comprobar si ya lo habíamos resuelto
            if (strcmp(puzles[i].estado, "Resuelto") == 0) {
                printf("\n-> Ya resolviste este puzle anteriormente.\n");
                return;
            }

            // 2. Mostrar el puzle
            printf("\n--- PUZLE: %s ---\n", puzles[i].nombre);
            printf("%s\n", puzles[i].descripcion);
            printf("------------------------\n");
            printf("Introduce tu solucion: ");
            
            char respuesta_jugador[51];
            if (scanf(" %50[^\n]", respuesta_jugador) != 1) {
                while(getchar() != '\n');
                return;
            }
            while(getchar() != '\n'); // Limpiar buffer

            // 3. Comprobar si ha acertado
            if (strcmp(respuesta_jugador, puzles[i].solucion) == 0) {
                printf("\n-> ¡CORRECTO! Has resuelto el misterio.\n");
                strcpy(puzles[i].estado, "Resuelto");
                
                for(int j = 0; j < num_conexiones; j++) {
                  
                    if(conexiones[j].origen == id_sala_actual && strcmp(conexiones[j].condicion, puzles[i].id) == 0) {
                        strcpy(conexiones[j].estado, "Abierta"); // "Abierta", no "ABIERTA"
                        printf("-> La puerta hacia la sala %02d ahora esta Abierta.\n", conexiones[j].destino);
                    }
                }
                
            } else {
                printf("\n '%s' no es la solucion correcta. Piensa un poco mas...\n", respuesta_jugador);
            }
            return;
        }
    }

    if (!puzle_encontrado) {
        printf("\n-> No parece haber ningun puzle en esta sala.\n");
    }
}
