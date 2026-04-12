#ifndef SALAS_H
#define SALAS_H
#include "conexiones.h"
#include "Ficheros.h" 
#include "objetos.h"


void describir_sala(int id_sala_actual, Sala* vector_salas, int num_salas);
void examinar_sala(int id_sala_actual, Sala* vector_salas, int num_salas, Conexion* vector_conexiones, int num_conexiones, ListaObjetos* lista_obj);
int entrar_en_otra_sala(int id_sala_actual, Conexion* vector_conexiones, int num_conexiones);

#endif