#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "objetos.h"
#include "Jugadores.h"

typedef struct 
{
    char Id_obj[5];
    char Nom_obj[16];
    char Desc_obj[51];
    //id sala del .h de salas
    char locacion[21];

}objetos;

typedef struct
{
    objetos *objetos;
    int num_objetos;
    int capacidad;

}ListaObjetos;

/*==========================================================
*abre el archivo de objetos y carga los datos en la lista.
*Devuelve 0 si se ha cargado correctamente, -1 si ha habido un error.
==========================================================*/

int leerObjetos(const char *filename, ListaObjetos *l){
    
    if (l == NULL) {
        fprintf(stderr, "La lista de objetos es NULL.\n");
        return -1;
    }

    // Inicializar la lista
    l->num_objetos = 0;
    l->capacidad = 10;  // Capacidad inicial
    l->objetos = (objetos *)malloc(l->capacidad * sizeof(objetos));
    
    if (l->objetos == NULL) {
        fprintf(stderr, "Error al asignar memoria para los objetos.\n");
        return -1;
    }

    // Matriz para almacenar las líneas del fichero
    char lineas[100][100];
    
    // Llamar a leer_fichero para obtener el contenido
    int numLineas = leer_fichero("objetos.txt", lineas);
    
    if (numLineas == 0) {
        fprintf(stderr, "Error al leer el archivo de objetos o archivo vacío.\n");
        return -1;
    }

    objetos temp;
    int i;
    
    // Procesar cada línea leída
    for (i = 0; i < numLineas; i++) {
        
        // Parsear la línea con sscanf
        if (sscanf(lineas[i], "%4s %15s %50s %20s", 
                   temp.Id_obj, 
                   temp.Nom_obj, 
                   temp.Desc_obj, 
                   temp.locacion) == 4) {
            
            // Si la capacidad se alcanza, expandir la lista
            if (l->num_objetos >= l->capacidad) {
                l->capacidad *= 2;
                objetos *temp_ptr = (objetos *)realloc(l->objetos, l->capacidad * sizeof(objetos));
                
                if (temp_ptr == NULL) {
                    fprintf(stderr, "Error al expandir la memoria para los objetos.\n");
                    return -1;
                }
                l->objetos = temp_ptr;
            }

            // Copiar el objeto temporal a la lista
            strcpy(l->objetos[l->num_objetos].Id_obj, temp.Id_obj);
            strcpy(l->objetos[l->num_objetos].Nom_obj, temp.Nom_obj);
            strcpy(l->objetos[l->num_objetos].Desc_obj, temp.Desc_obj);
            strcpy(l->objetos[l->num_objetos].locacion, temp.locacion);
            
            l->num_objetos++;
        }
    }

    return 0;
}







/*==========================================================
*Muestra por pantalla los datos de un objeto.
==========================================================*/


void mostrarObjeto(objetos *obj){
    if (obj  == NULL)
    {
        printf("El objeto no existe.\n");
        return;
    }

    printf("----Imprimiendo objeto----\n");

    printf("ID: %s\n", obj->Id_obj);
    printf("Nombre: %s\n", obj->Nom_obj);
    printf("Descripcion: %s\n", obj->Desc_obj);
    printf("Locacion: %s\n", obj->locacion);
    
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

int usarObjeto(ListaObjetos *l, jugador *j, const char *id_obj, listaConexiones *c, const char *id_sala){
    objetos *obj = buscarObjetoPorId(l, id_obj);

    if (obj==NULL)
    {
        printf("El objeto no existe.\n");
        return -1;
    }

    if (strcmp(obj->locacion, "inventario")!=0)
    {
        printf("Este objeto no se encuentra en el inventario del jugador.\n");
        return -1;

    }

    /*-Falta lo correspondiente a conexiones
    -Buscar la conexion porque no tengo id_sala(en el pdf pone que tiene que coincidir con el objeto)
    -Si existe hay que cambiarla a activa
    -Si no existe la relacion de conexiones no se podria usar el objeto*/



    printf("Usas el objeto: %s\n", obj->Nom_obj);
    printf("Descripcion: %s\n", obj->Desc_obj);

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