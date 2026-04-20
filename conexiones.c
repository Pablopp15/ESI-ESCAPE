#include <stdlib.h>
#include <string.h>
#include "conexiones.h"
// Cabecera: Conexion* buscar_conexion(Conexion* vector_conexiones, int num_conexiones, int id_origen, int id_destino)
/* Precondición: 'vector_conexiones' apunta a un vector de estructuras Conexion de tamaño 'num_conexiones' cargadas en memoria, 
con sus campos id_origen y id_destino correctamente asignados. Los nombres de origen y destino están vacíos o no actualizados.*/
/* Postcondición: Busca y devuelve un puntero a la conexión que une las salas con ID 'id_origen' y 'id_destino'. Si la encuentra, 
actualiza los campos nombre_origen y nombre_destino de la estructura devuelta. Si no, devuelve NULL.*/
Conexion* buscar_conexion(Conexion* vector_conexiones, int num_conexiones, int id_origen, int id_destino) {
    for (int i = 0; i < num_conexiones; i++) {
        
        if (vector_conexiones[i].origen == id_origen &&
            vector_conexiones[i].destino == id_destino) {
            
            
            return &vector_conexiones[i];
        }
    }
    return NULL;
}
// Cabecera: void liberar_conexiones(Conexion* vector_conexiones)
// Precondición: 'vector_conexiones' apunta a un vector de estructuras Conexion cargadas en memoria con memoria dinámica.
/* Postcondición: Libera la memoria dinámica asociada a cada estructura Conexion del vector, incluyendo la memoria para 
los nombres de origen y destino si se reservó dinámicamente, y finalmente libera la memoria del vector en sí.*/
void liberar_conexiones(Conexion* vector_conexiones) {
    if (vector_conexiones != NULL) {
    }
}