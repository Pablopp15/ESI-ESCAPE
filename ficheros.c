#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PUZLES 100
#define MAX_SALAS 100
#define MAX_CONEXIONES 100
#define MAX_OBJETOS 100
#define MAX_JUGADORES 100

#define CARGAR 0
#define GUARDAR 1

/* ==================== ESTRUCTURAS ==================== */

typedef struct {
    char id[4];
    char nombre[16];
    int id_sala;
    char tipo[10];
    char descripcion[151];
    char solucion[51];
} Puzle;

typedef struct {
    int id;
    char nombre[31];
    char tipo[10];
    char descripcion[151];
} Sala;

typedef struct {
    char id[4];
    int origen;
    int destino;
    char estado[15];
    char condicion[10];
} Conexion;

typedef struct {
    char id[5];
    char nombre[16];
    char descripcion[51];
    char localizacion[15];
} Objeto;

typedef struct {
    int id;
    char nombre[21];
    char usuario[11];
    char password[9];
} Jugador;


/* ========================================================= */
/* FUNCION PARA LEER UN FICHERO DE TEXTO LINEA A LINEA */
/* ========================================================= */

int leer_fichero(char *nombreFichero, char texto[][100]) {

    FILE *f;      // Puntero al fichero
    int i = 0;    // Contador de líneas

    // Abrimos el fichero en modo lectura
    f = fopen(nombreFichero, "r");

    // Si hay error
    if (f == NULL) {
        printf("Error al abrir el fichero.\n");
        return 0;
    }

    // Leemos línea a línea
    while (fgets(texto[i], 100, f) != NULL) {

        // Quitamos el salto de línea '\n'
        texto[i][strcspn(texto[i], "\n")] = '\0';

        i++;
    }

    fclose(f);  // Cerramos fichero

    return i;   // Devolvemos número de líneas leídas
}


/* ========================================================= */
/* FUNCION PARA ESCRIBIR AL FINAL DE UN FICHERO */
/* ========================================================= */

void escribir_fichero(char *nombreFichero, char texto[][100], int numLineas) {

    FILE *f;

    // Abrimos en modo append (añadir al final)
    f = fopen(nombreFichero, "a");

    if (f == NULL) {
        printf("Error al abrir el fichero.\n");
        return;
    }

    // Escribimos cada línea
    for (int i = 0; i < numLineas; i++) {
        fprintf(f, "%s\n", texto[i]);
    }

    fclose(f);
}


/* ========================================================= */
/* FUNCION PARA CARGAR DATOS EN ESTRUCTURAS */
/* ========================================================= */

void gestionarFicheros(Puzle p[], int *np,
                       Sala s[], int *ns,
                       Conexion c[], int *nc,
                       Objeto o[], int *no,
                       Jugador j[], int *nj,
                       int modo) {

    FILE *f;

    if (modo == CARGAR) {

        /* ==================== PUZLES ==================== */
        *np = 0;
        f = fopen("Puzles.txt", "r");

        if (f != NULL) {
            while (fscanf(f,"%3[^-]-%15[^-]-%d-%9[^-]-%150[^-]-%50[^\n]\n",
                p[*np].id, p[*np].nombre, &p[*np].id_sala,
                p[*np].tipo, p[*np].descripcion, p[*np].solucion) == 6) {

                (*np)++;
            }
            fclose(f);
        }

        /* ==================== SALAS ==================== */
        *ns = 0;
        f = fopen("Salas.txt", "r");

        if (f != NULL) {
            while (fscanf(f,"%d-%30[^-]-%9[^-]-%150[^\n]\n",
                &s[*ns].id, s[*ns].nombre, s[*ns].tipo, s[*ns].descripcion) == 4) {

                (*ns)++;
            }
            fclose(f);
        }

        /* ==================== CONEXIONES ==================== */
        *nc = 0;
        f = fopen("Conexiones.txt", "r");

        if (f != NULL) {
            while (fscanf(f,"%3[^-]-%d-%d-%14[^-]-%9[^\n]\n",
                c[*nc].id, &c[*nc].origen, &c[*nc].destino,
                c[*nc].estado, c[*nc].condicion) == 5) {

                (*nc)++;
            }
            fclose(f);
        }

        /* ==================== OBJETOS ==================== */
        *no = 0;
        f = fopen("Objetos.txt", "r");

        if (f != NULL) {
            while (fscanf(f,"%4[^-]-%15[^-]-%50[^-]-%14[^\n]\n",
                o[*no].id, o[*no].nombre, o[*no].descripcion,
                o[*no].localizacion) == 4) {

                (*no)++;
            }
            fclose(f);
        }

        /* ==================== JUGADORES ==================== */
        *nj = 0;
        f = fopen("Jugadores.txt", "r");

        if (f != NULL) {
            while (fscanf(f,"%d-%20[^-]-%10[^-]-%8[^\n]\n",
                &j[*nj].id, j[*nj].nombre, j[*nj].usuario, j[*nj].password) == 4) {

                (*nj)++;
            }
            fclose(f);
        }
    }
}