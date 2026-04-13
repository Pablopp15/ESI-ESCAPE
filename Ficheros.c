#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Ficheros.h"

/* ========================================================= */
/* FUNCION PARA LEER UN FICHERO DE TEXTO LINEA A LINEA       */
/* ========================================================= */
int leer_fichero(char *nombreFichero, char texto[][300]) {
    FILE *f;      
    int i = 0;    

    f = fopen(nombreFichero, "r");

    if (f == NULL) {
        printf("Error al abrir el fichero %s.\n", nombreFichero);
        return 0;
    }

    while (fgets(texto[i], 300, f) != NULL) {
        texto[i][strcspn(texto[i], "\n")] = '\0';
        i++;
    }

    fclose(f);  
    return i;   
}

/* ========================================================= */
/* FUNCION PARA ESCRIBIR AL FINAL DE UN FICHERO              */
/* ========================================================= */
void escribir_fichero(char *nombreFichero, char texto[][300], int numLineas) {
    FILE *f;

    f = fopen(nombreFichero, "a");

    if (f == NULL) {
        printf("Error al abrir el fichero %s para escritura.\n", nombreFichero);
        return;
    }

    for (int i = 0; i < numLineas; i++) {
        fprintf(f, "%s\n", texto[i]);
    }

    fclose(f);
}

/* ========================================================= */
/* FUNCION PARA CARGAR DATOS EN ESTRUCTURAS ESTATICAS        */
/* ========================================================= */

void gestionarFicheros(Puzle p[], int *np, Sala s[], int *ns, Conexion c[], int *nc, int modo) {

    FILE *f;

    if (modo == CARGAR) {

        /* ==================== PUZLES ==================== */
        *np = 0;
        f = fopen("Puzles.txt", "r");

        if (f != NULL) {
            // Hemos añadido un bloque más al final para leer el estado
            while (fscanf(f,"%3[^-]-%15[^-]-%d-%9[^-]-%150[^-]-%50[^-]-%14[^\n]\n",
                p[*np].id, p[*np].nombre, &p[*np].id_sala,
                p[*np].tipo, p[*np].descripcion, p[*np].solucion, p[*np].estado) == 7) {
                
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
    }
}