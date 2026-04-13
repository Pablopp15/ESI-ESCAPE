#ifndef PARTIDA_H
#define PARTIDA_H
#define MAX_SALAS 100
#define MAX_CONEXIONES 100
#define MAX_PUZLES 100
#include "objetos.h"
#include "Jugadores.h"
#include "Ficheros.h"
#include "salas.h"
#include "puzles.h"

void iniciar_juego();

void menu_principal(ListaJugadores *lista_jugadores, ListaObjetos *lista_obj, Sala salas[], int num_salas, Conexion conexiones[], int num_conexiones, Puzle puzles[], int num_puzles);
void nueva_partida(jugador *jugador_actual, ListaObjetos *lista_obj, Sala salas[], int num_salas, Conexion conexiones[], int num_conexiones, Puzle puzles[], int num_puzles);
void partida(jugador *jugador_actual, ListaObjetos *lista_obj, Sala salas[], int num_salas, Conexion conexiones[], int num_conexiones, Puzle puzles[], int num_puzles, int id_sala_actual);


void guardar_partida(char id_jugador[], int id_sala, objetos objetos[], int num_objetos, Conexion conexiones[], int num_conexiones, Puzle puzles[], int num_puzles);
void cargar_partida(jugador *jugador_actual, ListaObjetos *lista_obj, Sala salas[], int num_salas, Conexion conexiones[], int num_conexiones, Puzle puzles[], int num_puzles);


void escribir_fichero(char *nombreFichero, char lineas_de_texto[][300], int cantidad_lineas);
int leer_fichero(char *nombreFichero, char texto[][300]);

//Funciones para cargar partida
void parsear_jugador(char linea[], char id_jugador[]);
void parsear_sala(char linea[], int *sala);
void parsear_objeto(char linea[], objetos *obj);
void parsear_conexion(char linea[], Conexion *con);
void parsear_puzle(char linea[], Puzle *puz);

#endif
