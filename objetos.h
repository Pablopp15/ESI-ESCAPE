#ifndef OBJETOS_H
#define OBJETOS_H

typedef struct 
{
    char Id_obj[5];
    char Nom_obj[16];
    char Desc_obj[51];
    char locacion[21];
}objetos;

typedef struct
{
    objetos *objetos;
    int num_objetos;
    int capacidad;
}ListaObjetos;

int leerObjetos(const char *filename, ListaObjetos *l);

void mostrarObjeto(objetos *obj);

objetos *buscarObjetoPorId(ListaObjetos *lista, const char *id);


int cogerObjeto(ListaObjetos *l, jugador *j, const char *id_obj, const char *id_sala);


int soltarObjeto(ListaObjetos *l, jugador *j, const char *id_obj, const char *id_sala);


int usarObjeto(ListaObjetos *l, jugador *j, const char *id_obj, listaConexiones *c, const char *id_sala);

void liberarObjetos(ListaObjetos *l);

#endif
