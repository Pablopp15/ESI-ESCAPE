#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include "salas.h"
// Cabecera: void describir_sala(int id_sala_actual, Sala* vector_salas, int num_salas)
/* Precondición: 'vector_salas' está cargado y contiene 'num_salas'. 'id_sala_actual'
   debe ser un ID válido presente en el vector. */
/* Postcondición: Muestra por pantalla el nombre, tipo y descripción de la sala 
   actual. Al usar el nombre almacenado en la estructura Sala, permite que las 
   conexiones puedan copiarlo posteriormente. */
void describir_sala(int id_sala_actual, Sala* vector_salas, int num_salas) {
    for (int i = 0; i < num_salas; i++) {
       
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

// Cabecera: void examinar_sala(int id_sala_actual, Sala* vector_salas, int num_salas, Conexion* vector_conexiones, int num_conexiones, ListaObjetos* lista_obj)
/*Precondición: 'vector_salas' y 'vector_conexiones' apuntan a vectores de estructuras Sala y Conexion cargadas en memoria, con memoria dinámica. 
'lista_obj' apunta a una lista de objetos. 'id_sala_actual' es el ID de la sala que se va a examinar.
*/ /*Postcondición: Muestra por pantalla la información detallada de la sala con ID 'id_sala_actual', incluyendo su nombre, tipo, descripción, objetos presentes 
y las conexiones que tiene, mostrando los nombres de las salas de origen y destino de cada conexión.
*/ 
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
// Cabecera: int entrar_en_otra_sala(int id_sala_actual, Conexion* vector_conexiones, int num_conexiones)
/* Precondición: 'vector_conexiones' debe tener los nombres de origen y destino 
   ya copiados desde las salas para poder informar al usuario a dónde se mueve. */
/* Postcondición: Busca las conexiones cuyo 'id_origen' coincida con 'id_sala_actual'.
   Muestra al usuario las opciones de destino usando los nombres de las salas 
   (nombre_destino) y devuelve el ID de la nueva sala elegida. */
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
       
        printf("-> No puedes ir a esa sala desde aqui. Revisa las salidas disponibles.\n");
        return id_sala_actual; 
    }
}
