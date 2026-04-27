#ifndef FICHEROS_H
#define FICHEROS_H

typedef struct {
    int id;
    char nombre[31];
    char tipo[10];
    char descripcion[151];
} Sala;

typedef struct {
    char id[4];              
    char nombre[16];         
    int id_sala;             
    char tipo[10];           
    char descripcion[151];   
    char solucion[51];       
    char estado[15];         
} Puzle;
typedef struct {
    char id[4];
    int origen;
    int destino;
    char estado[15];
    char condicion[10];
} Conexion;

// Constantes
#define CARGAR 0
#define GUARDAR 1

// Declaraciones de funciones
int leer_fichero(char *nombreFichero, char texto[][300]);
void escribir_fichero(char *nombreFichero, char texto[][300], int numLineas);
void gestionarFicheros(Puzle p[], int *np, Sala s[], int *ns, Conexion c[], int *nc, int modo);

#endif