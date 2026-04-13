#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "objetos.h"
#include "Jugadores.h"

/*==========================================================
*abre el archivo de objetos y carga los datos en la lista.
*Devuelve 0 si se ha cargado correctamente, -1 si ha habido un error.
==========================================================*/

int leerObjetos(const char *filename, ListaObjetos *l){
    if (l == NULL) return -1;

    l->num_objetos = 0;
    l->capacidad = 10;
    l->objetos = (objetos *)malloc(l->capacidad * sizeof(objetos));
    
    char lineas[300][300];
    int numLineas = leer_fichero("objetos.txt", lineas);
    
    for (int i = 0; i < numLineas; i++) {
        objetos temp;
        // Cambiamos el sscanf para que lea hasta encontrar un guion [-]
        if (sscanf(lineas[i], "%4[^-]-%35[^-]-%50[^-]-%150[^\n]", 
                   temp.Id_obj, temp.Nom_obj, temp.locacion, temp.Desc_obj) == 4) {
            
            if (l->num_objetos >= l->capacidad) {
                l->capacidad *= 2;
                l->objetos = (objetos *)realloc(l->objetos, l->capacidad * sizeof(objetos));
            }
            l->objetos[l->num_objetos] = temp;
            l->num_objetos++;
        }
    }
    return 0;
}







/*==========================================================
*Muestra por pantalla los datos de un objeto.
==========================================================*/


void mostrarObjetosEnSala(ListaObjetos *l, const char *id_sala) {
    int i;
    int encontrados = 0;

    if (l == NULL || id_sala == NULL) return;

    printf("\nObjetos en esta sala:\n");
    for (i = 0; i < l->num_objetos; i++) {
        // Comparamos cadenas "01" con "01"
        if (strcmp(l->objetos[i].locacion, id_sala) == 0) {
            printf(" - %s (ID: %s): %s\n", 
                   l->objetos[i].Nom_obj, 
                   l->objetos[i].Id_obj, 
                   l->objetos[i].Desc_obj);
            encontrados++;
        }
    }

    if (encontrados == 0) {
        printf(" No hay objetos a la vista.\n");
    }
}


/* =========================================================
 * buscarObjetoPorId
 * Recorre la lista y devuelve puntero al objeto con ese id.
 * Devuelve NULL si no existe.
========================================================= */
objetos *buscarObjetoPorId(ListaObjetos *lista, const char *id){
 
    int i;
 
    if (lista == NULL || id == NULL) return NULL;
 
    for (i = 0; i < lista->num_objetos; i++) {
        if (strcmp(lista->objetos[i].Id_obj, id) == 0) {
            return &lista->objetos[i];
        }
    }
 
    return NULL;
}






/*=========================================================
 * El jugador recoge un objeto de la sala actual.
 * Cambia la localizacion del objeto a "Inventario"
 * Lo añade al inventario del jugador.
========================================================= */
int cogerObjeto(ListaObjetos *l, jugador *j, const char *id_obj, const char *id_sala){


    objetos *obj=buscarObjetoPorId(l, id_obj);

    if (obj==NULL)
    {
        printf("El objeto no existe.\n");
        return 1;
    }

    if (strcmp(obj->locacion, id_sala )!=0)
    {
        printf("El objeto no esta en la sala actual.\n");
        return 1;
        
    }
    
    strncpy(obj->locacion, "Inventario", 20);

    agregarAlInventario(j, id_obj);

    printf("Has recogido el objeto: %s\n", obj->Nom_obj);
    return 0;

    
    
}






/*=========================================================
*El jugador suelta un objeto de su inventario.
* Cambia la localizacion del objeto de inventario a sala.
*Borra el objeto del inventario del jugador.
==========================================================*/
 

int soltarObjeto(ListaObjetos *l, jugador *j, const char *id_obj, const char *id_sala){
    objetos *obj = buscarObjetoPorId(l, id_obj);

    if (obj==NULL)
    {
        printf("El objeto no existe.\n");
        return -1;
    }

    if (strcmp(obj->locacion, "Inventario")!=0)
    {
        printf("Este objeto no se encuentra en el inventario del jugador.\n");
        return -1;

    }

    strncpy(obj->locacion, id_sala, 20);

    eliminarDelInventario(j, id_obj);

    printf("Has soltado el objeto: %s a la sala: %s", obj->Nom_obj, id_sala);

    return 0;
}







/* ==========================================================
*El jugador selecciona un objeto de su inventario para usarlo.
* El efecto del objeto se muestra por pantalla.
==========================================================*/

int usarObjeto(ListaObjetos *l, jugador *j, const char *id_obj, int id_sala_actual, Conexion conexiones[], int num_conexiones){
    objetos *obj = buscarObjetoPorId(l, id_obj);

    if (obj == NULL) {
        printf("El objeto no existe.\n");
        return -1;
    }

   
    if (strcmp(obj->locacion, "Inventario") != 0) {
        printf("No tienes este objeto en tu inventario .\n", obj->locacion);
        return -1;
    }

    int encontrado = 0;
    for (int i = 0; i < num_conexiones; i++) {
        if (conexiones[i].origen == id_sala_actual && strncmp(conexiones[i].condicion, id_obj, 4) == 0)  {
           
            strcpy(conexiones[i].estado, "Abierta"); 
            printf("¡CLACK! Has usado %s y has abierto la puerta a la sala %02d.\n", obj->Nom_obj, conexiones[i].destino);
            encontrado = 1;
        }
    }

    if (!encontrado) {
        printf("Usas %s, pero no sirve para nada en esta sala.\n", obj->Nom_obj);
    }
    return 0;
}






void liberarObjetos(ListaObjetos *l){

   if (l == NULL) return;

    if (l->objetos != NULL) {
        free(l->objetos);
        l->objetos = NULL;
    }

    l->num_objetos = 0;
    l->capacidad   = 0;
}
