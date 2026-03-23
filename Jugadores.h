#ifndef jugadores_h
#define jugadores_h

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


void inicializarinventario(jugador *j);
void agregarAlInventario(jugador *j, const char *id_obj);
int eliminarDelInventario(jugador *j, const char *id_obj);
void mostrarInventario(jugador *j);
void inicializarJugador(jugador *j, const char *id, const char *nom_completo, const char *nom_usuario, const char *contrasena);
void inicializarListaJugadores(ListaJugadores *lista);
void agregarJugador(ListaJugadores *lista, const char *id, const char *nom_completo, const char *nom_usuario, const char *contrasena);
void liberarJugadores(ListaJugadores *lista);

#endif /* jugadores_h */
