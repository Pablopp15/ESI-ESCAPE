#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PUZLES 100

#define CARGAR 0
#define GUARDAR 1

/* ==================== ESTRUCTURA ==================== */

typedef struct {
    char id[4];              // 3 caracteres + '\0'
    char nombre[16];         // max 15
    int id_sala;             // 2 dígitos
    char tipo[10];           // "Codigo" o "Palabra"
    char descripcion[151];   // max 150
    char solucion[51];       // max 50
} Puzle;


/* ========================================================= */
/* FUNCION PARA LEER UN FICHERO DE TEXTO */
/* ========================================================= */

int leer_fichero(char *nombreFichero, char texto[][200]) {

    FILE *f;
    int i = 0;

    f = fopen(nombreFichero, "r");

    if (f == NULL) {
        printf("Error al abrir el fichero.\n");
        return 0;
    }

    while (fgets(texto[i], 200, f) != NULL) {

        // Elimina el salto de línea
        texto[i][strcspn(texto[i], "\n")] = '\0';

        i++;
    }

    fclose(f);

    return i;
}


/* ========================================================= */
/* FUNCION PARA ESCRIBIR AL FINAL DE UN FICHERO */
/* ========================================================= */

void escribir_fichero(char *nombreFichero, char texto[][200], int numLineas) {

    FILE *f;

    f = fopen(nombreFichero, "a");  // append

    if (f == NULL) {
        printf("Error al abrir el fichero.\n");
        return;
    }

    for (int i = 0; i < numLineas; i++) {
        fprintf(f, "%s\n", texto[i]);
    }

    fclose(f);
}


/* ========================================================= */
/* FUNCION PARA CARGAR PUZLES DESDE FICHERO */
/* ========================================================= */

void cargarPuzles(Puzle p[], int *np) {

    FILE *f;

    *np = 0;

    f = fopen("Puzles.txt", "r");

    if (f != NULL) {

        while (fscanf(f,"%3[^-]-%15[^-]-%d-%9[^-]-%150[^-]-%50[^\n]\n",
            p[*np].id,
            p[*np].nombre,
            &p[*np].id_sala,
            p[*np].tipo,
            p[*np].descripcion,
            p[*np].solucion) == 6) {

            (*np)++;
        }

        fclose(f);
    }
}


/* ========================================================= */
/* FUNCION PARA GUARDAR PUZLES EN FICHERO */
/* ========================================================= */

void guardarPuzles(Puzle p[], int np) {

    FILE *f;

    // Abrimos en modo "w" para sobrescribir
    f = fopen("Puzles.txt", "w");

    if (f == NULL) {
        printf("Error al abrir el fichero.\n");
        return;
    }

    // Escribimos cada puzle en el formato correcto
    for (int i = 0; i < np; i++) {

        fprintf(f, "%s-%s-%02d-%s-%s-%s\n",
            p[i].id,
            p[i].nombre,
            p[i].id_sala,
            p[i].tipo,
            p[i].descripcion,
            p[i].solucion);
    }

    fclose(f);
}


/* ========================================================= */
/* FUNCION GENERAL DEL MODULO */
/* ========================================================= */

void gestionarPuzles(Puzle p[], int *np, int modo) {

    if (modo == CARGAR) {
        cargarPuzles(p, np);
    }

    if (modo == GUARDAR) {
        guardarPuzles(p, *np);
    }
}