#include <stdlib.h>
#include <string.h>
#include "conexiones.h"

Conexion* buscar_conexion(Conexion* vector_conexiones, int num_conexiones, int id_origen, int id_destino) {
    for (int i = 0; i < num_conexiones; i++) {
        
        if (vector_conexiones[i].origen == id_origen &&
            vector_conexiones[i].destino == id_destino) {
            
            
            return &vector_conexiones[i];
        }
    }
    return NULL;
}

void liberar_conexiones(Conexion* vector_conexiones) {
    if (vector_conexiones != NULL) {
    }
}