#ifndef CONEXIONES_H
#define CONEXIONES_H

#include "Ficheros.h"

Conexion* buscar_conexion(Conexion* vector_conexiones, int num_conexiones, int id_origen, int id_destino);
void liberar_conexiones(Conexion* vector_conexiones);

#endif