#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include "salas.h"
void describir_sala(int id_sala_actual, Sala* vector_salas, int num_salas) {
    for (int i = 0; i < num_salas; i++) {
        // Ahora comparamos números enteros
        if (vector_salas[i].id == id_sala_actual) {
            printf("\n--- %s ---\n", vector_salas[i].nombre);
            printf("%s\n", vector_salas[i].descripcion);
        
            if (strcmp(vector_salas[i].tipo, "SALIDA") == 0) {
                printf("\n¡ENHORABUENA! Has encontrado la salida y escapado con exito.\n");
            }
            return;
        }
    }
    printf("Error: No se encuentra la descripcion de la sala actual.\n");
}


void examinar_sala(int id_sala_actual, Sala* vector_salas, int num_salas, Conexion* vector_conexiones, int num_conexiones, ListaObjetos* lista_obj) {
    
    printf("\n--- EXAMINANDO LA SALA ---\n");

    
    char id_sala_str[10];
    sprintf(id_sala_str, "%02d", id_sala_actual); 

 
    mostrarObjetosEnSala(lista_obj, id_sala_str);


    printf("\n[ SALIDAS DISPONIBLES ]\n");
    int salidas_vistas = 0;
    for (int i = 0; i < num_conexiones; i++) {
        if (vector_conexiones[i].origen == id_sala_actual) {
            printf(" -> Puerta hacia la sala %02d (Estado: %s)\n", 
                   vector_conexiones[i].destino, vector_conexiones[i].estado);
            salidas_vistas = 1;
        }
    }
    
    if (salidas_vistas == 0) printf(" -> No hay salidas directas desde aqui.\n");
    printf("---------------------------\n");
}

int entrar_en_otra_sala(int id_sala_actual, Conexion* vector_conexiones, int num_conexiones) {
    int id_destino_solicitado;

    printf("\nIntroduce el ID de la sala a la que quieres ir (ej: 02): ");
    
    if (scanf("%d", &id_destino_solicitado) != 1) {
        while (getchar() != '\n'); 
        printf("-> ID no valido. Debes introducir un numero.\n");
        return id_sala_actual; 
    }
    while (getchar() != '\n'); 

    Conexion* enlace = buscar_conexion(vector_conexiones, num_conexiones, id_sala_actual, id_destino_solicitado);

    if (enlace != NULL) {
       
        if (strcmp(enlace->estado, "Activa") == 0 || strcmp(enlace->estado, "Abierta") == 0) {
            printf("-> Te has movido a la sala %02d.\n", id_destino_solicitado);
            return id_destino_solicitado;
        } else {
            printf("-> La puerta esta Bloqueada. Necesitas el objeto o resolver el puzle: %s\n", enlace->condicion);
            return id_sala_actual;
        }
    } else {
        // Si buscar_conexion devolvió NULL
        printf("-> No puedes ir a esa sala desde aqui. Revisa las salidas disponibles.\n");
        return id_sala_actual; 
    }
}