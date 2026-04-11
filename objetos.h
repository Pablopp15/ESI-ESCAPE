#ifndef OBJETOS_H
#define OBJETOS_H
#include "Jugadores.h"
#include "Ficheros.h"

typedef struct 
{
    char Id_obj[5];
    char Nom_obj[36];
    char Desc_obj[151];
    char locacion[51];
}objetos;

typedef struct
{
    objetos *objetos;
    int num_objetos;
    int capacidad;
}ListaObjetos;

int leerObjetos(const char *filename, ListaObjetos *l);

void mostrarObjetosEnSala(ListaObjetos *l, const char *id_sala);

objetos *buscarObjetoPorId(ListaObjetos *lista, const char *id);


int cogerObjeto(ListaObjetos *l, jugador *j, const char *id_obj, const char *id_sala);


int soltarObjeto(ListaObjetos *l, jugador *j, const char *id_obj, const char *id_sala);


int usarObjeto(ListaObjetos *l, jugador *j, const char *id_obj, int id_sala_actual, Conexion conexiones[], int num_conexiones);

void liberarObjetos(ListaObjetos *l);

#endif
