/*
 * Jugadores.c
 * Módulo de gestión de jugadores para ESI-Escape
 * Metodología de la Programación
 *
 * NOTA: Este módulo gestiona la lógica de jugadores en memoria.
 * La lectura/escritura de ficheros la realiza el módulo de ficheros.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Jugadores.h"
#include "objetos.h"

/* =========================================================
 * STRUCTS
========================================================= */

typedef struct
{
    char Id_jug[3];              /* 2 digitos + '\0' */
    char nom_completo[21];       /* 20 chars  + '\0' */
    char nom_usuario[11];        /* 10 chars  + '\0' */
    char contrasena[9];          /* 8 chars   + '\0' */
    char **inventario;           /* array dinamico de IDs de objetos */
    int num_objetos;
    int capacidad_inventario;

} jugador;


typedef struct
{
    jugador *jugadores;          /* array dinamico de jugadores */
    int num_jugadores;
    int capacidad;

} ListaJugadores;


/* =========================================================
 * inicializarinventario
 * Reserva memoria inicial para el inventario del jugador.
 ========================================================= */
void inicializarinventario(jugador *j){

    j->capacidad_inventario = 2;
    j->num_objetos = 0;

    j->inventario = (char **) malloc(j->capacidad_inventario * sizeof(char *));
    if (j->inventario == NULL) {
        fprintf(stderr, "Error al asignar memoria para el inventario.\n");
        j->capacidad_inventario = 0;
        return;
    }

    int i;
    for (i = 0; i < j->capacidad_inventario; i++) {
        j->inventario[i] = NULL;
    }
}


/* =========================================================
 * agregarAlInventario
 * Añade el ID de un objeto al inventario del jugador.
 * Hace realloc si se queda sin espacio.
  ========================================================= */
void agregarAlInventario(jugador *j, const char *id_obj){

    char **aux;

    /* Ampliar si es necesario */
    if (j->num_objetos == j->capacidad_inventario) {
        j->capacidad_inventario *= 2;
        aux = (char **) realloc(j->inventario,
                                j->capacidad_inventario * sizeof(char *));
        if (aux == NULL) {
            fprintf(stderr, "Error al ampliar memoria del inventario.\n");
            return;
        }
        j->inventario = aux;
    }

    /* Reservar memoria para el string del ID y copiarlo */
    j->inventario[j->num_objetos] = (char *) malloc((strlen(id_obj) + 1) * sizeof(char));
    if (j->inventario[j->num_objetos] == NULL) {
        fprintf(stderr, "Error al reservar memoria para el objeto.\n");
        return;
    }

    strcpy(j->inventario[j->num_objetos], id_obj);
    j->num_objetos++;
}


/* =========================================================
 * eliminarDelInventario
 * Elimina el ID de un objeto del inventario del jugador.
 * Retorna 0 si OK, -1 si el objeto no estaba.
 * ========================================================= */
int eliminarDelInventario(jugador *j, const char *id_obj){

    int i, k;

    for (i = 0; i < j->num_objetos; i++) {
        if (strcmp(j->inventario[i], id_obj) == 0) {

            /* Liberar el string encontrado */
            free(j->inventario[i]);

            /* Desplazar los siguientes hacia atras */
            for (k = i; k < j->num_objetos - 1; k++) {
                j->inventario[k] = j->inventario[k + 1];
            }

            j->inventario[j->num_objetos - 1] = NULL;
            j->num_objetos--;
            return 0;
        }
    }

    printf("El objeto %s no esta en el inventario.\n", id_obj);
    return -1;
}


/* =========================================================
 * inicializarJugador
 * Rellena la struct con los datos recibidos como parametros.
 * Los datos los proporciona el modulo de ficheros ya parseados.
 * ========================================================= */
void inicializarJugador(jugador *j, const char *id, const char *nom_completo, const char *nom_usuario, const char *contrasena){

    strncpy(j->Id_jug, id, 2);
    j->Id_jug[2] = '\0';

    strncpy(j->nom_completo, nom_completo, 20);
    j->nom_completo[20] = '\0';

    strncpy(j->nom_usuario, nom_usuario, 10);
    j->nom_usuario[10] = '\0';

    strncpy(j->contrasena, contrasena, 8);
    j->contrasena[8] = '\0';

    inicializarinventario(j);
}




/* =========================================================
 * inicializarListaJugadores
 * Prepara la lista vacia antes de empezar a añadir jugadores.
 * La llama el modulo de ficheros antes de cargar el TXT.
========================================================= */
void inicializarListaJugadores(ListaJugadores *lista){

    lista->capacidad     = 5;
    lista->num_jugadores = 0;
    lista->jugadores     = (jugador *) malloc(lista->capacidad * sizeof(jugador));

    if (lista->jugadores == NULL) {
        fprintf(stderr, "Error al reservar memoria para la lista de jugadores.\n");
        lista->capacidad = 0;
    }
}

void agregarJugadorALista(ListaJugadores *lista, jugador *j){
 
    jugador *aux;
 
    if (lista->num_jugadores == lista->capacidad) {
        lista->capacidad *= 2;
        aux = (jugador *) realloc(lista->jugadores,
                                  lista->capacidad * sizeof(jugador));
        if (aux == NULL) {
            fprintf(stderr, "Error al ampliar la lista de jugadores.\n");
            return;
        }
        lista->jugadores = aux;
    }
 
    lista->jugadores[lista->num_jugadores] = *j;
    lista->num_jugadores++;
}



/* =========================================================
 * mostrarInventario
 * Lista por pantalla todos los objetos del inventario
 * del jugador con su ID.
========================================================= */
void mostrarInventario(jugador *j){

    int i;

    if (j->num_objetos == 0) {
        printf("El inventario esta vacio.\n");
        return;
    }

    printf("Inventario de %s:\n", j->nom_usuario);
    for (i = 0; i < j->num_objetos; i++) {
        printf("  [%d] %s\n", i + 1, j->inventario[i]);
    }
}


/* =========================================================
 * liberarJugadores
 * Libera toda la memoria dinamica de la lista.
 * Siempre llamar antes de cerrar el programa.
========================================================= */
void liberarJugadores(ListaJugadores *lista){

    int i, k;

    for (i = 0; i < lista->num_jugadores; i++) {

        /* Liberar cada string del inventario */
        for (k = 0; k < lista->jugadores[i].num_objetos; k++) {
            if (lista->jugadores[i].inventario[k] != NULL) {
                free(lista->jugadores[i].inventario[k]);
            }
        }

        /* Liberar el array de punteros */
        free(lista->jugadores[i].inventario);
    }

    /* Liberar el array de jugadores */
    free(lista->jugadores);
    lista->jugadores     = NULL;
    lista->num_jugadores = 0;
    lista->capacidad     = 0;
}