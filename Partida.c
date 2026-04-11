#include <stdio.h>
#include <string.h> 
#include "Partida.h"

void iniciar_juego() {
    printf("Arrancando el motor de ESI ESCAPE...\n");

    //Inicializamos las listas dinámicas
    ListaJugadores mi_lista_jugadores;
    inicializarListaJugadores(&mi_lista_jugadores);

    ListaObjetos mi_lista_objetos;
    leerObjetos("objetos.txt", &mi_lista_objetos); 

    //CARGAMOS LOS JUGADORES DESDE EL TXT
    char lineas_jugadores[100][100];
    int num_jug_leidos = leer_fichero("Jugadores.txt", lineas_jugadores);

    for (int i = 0; i < num_jug_leidos; i++) {
        char id_temp[3];
        char nom_temp[21];
        char usu_temp[11];
        char cont_temp[9];
        
        if (sscanf(lineas_jugadores[i], "%[^-]-%[^-]-%[^-]-%[^\n]", id_temp, nom_temp, usu_temp, cont_temp) == 4) {
            jugador j_temp;
            inicializarJugador(&j_temp, id_temp, nom_temp, usu_temp, cont_temp);
            agregarJugadorALista(&mi_lista_jugadores, &j_temp);
        }
    }
    
    //Declararamos y cargamos Salas, Conexiones y Puzles
    Sala mis_salas[MAX_SALAS];           int total_salas = 0;
    Conexion mis_conexiones[MAX_CONEXIONES]; int total_conexiones = 0;
    Puzle mis_puzles[MAX_PUZLES];        int total_puzles = 0;

    // Llamamos a la función que lee Salas.txt y Conexiones.txt
    gestionarFicheros(mis_puzles, &total_puzles, mis_salas, &total_salas, mis_conexiones, &total_conexiones, CARGAR);

    printf(">> Datos cargados: %d jugadores, %d salas, %d conexiones.\n", 
            mi_lista_jugadores.num_jugadores, total_salas, total_conexiones);

    //LLamamos a la funcion menu_principal
    menu_principal(&mi_lista_jugadores, &mi_lista_objetos, mis_salas, total_salas, mis_conexiones, total_conexiones, mis_puzles, total_puzles);

    //Limpiamos memoria al salir
    liberarJugadores(&mi_lista_jugadores);
    liberarObjetos(&mi_lista_objetos);
    
    printf("\nCerrando el programa de forma segura. ¡Hasta pronto!\n");
}




void menu_principal(ListaJugadores *lista_jugadores, ListaObjetos *lista_obj, Sala salas[], int num_salas, Conexion conexiones[], int num_conexiones, Puzle puzles[], int num_puzles) {
    char usu[11];
    char cont[9];
    int logueado = 0;
    int id_jugador_idx = -1; 

    printf("\n-------------------------------\n");
    printf("  Bienvenido al juego\n");
    printf("  ESI ESCAPE\n");
    printf("\n-------------------------------\n");

    while (!logueado) {
        printf("Introduce tu usuario: ");
        scanf("%10s", usu);
        printf("Introduce tu contrasenya: ");
        scanf("%8s", cont);
        
        int encontrado = 0;
        
        for(int i = 0; i < lista_jugadores->num_jugadores; i++) {
            if (strcmp(lista_jugadores->jugadores[i].nom_usuario, usu) == 0) {
                encontrado = 1;
                if(strcmp(lista_jugadores->jugadores[i].contrasena, cont) == 0) {
                    logueado = 1;
                    id_jugador_idx = i;
                    printf("\n Login correcto. Acceso concedido.\n");
                } else {
                    printf("\n Contrasenya incorrecta. Intentalo de nuevo.\n");
                }
                break;
            }
        }

        if(!encontrado) {
            char respuesta;
            printf("\n El usuario '%s' no existe.\n", usu);
            printf("¿Quieres registrarte con este perfil? (s/n): ");
            
            while (getchar() != '\n'); 
            scanf("%c", &respuesta);
            
            if(respuesta == 's' || respuesta == 'S') {
                char nombre_completo[21];
                char id_nuevo[3];

                while (getchar() != '\n');

                
                printf("Introduce tu Nombre Completo: ");
                scanf(" %20[^\n]", nombre_completo); 
                while (getchar() != '\n');

                sprintf(id_nuevo, "%02d", lista_jugadores->num_jugadores + 1);

                jugador nuevo_j;
                inicializarJugador(&nuevo_j, id_nuevo, nombre_completo, usu, cont);
                
                agregarJugadorALista(lista_jugadores, &nuevo_j);

                char linea_nueva[1][100]; 
                sprintf(linea_nueva[0], "%s-%s-%s-%s", 
                        nuevo_j.Id_jug, 
                        nuevo_j.nom_completo, 
                        nuevo_j.nom_usuario, 
                        nuevo_j.contrasena);
                
                escribir_fichero("Jugadores.txt", linea_nueva, 1);

                logueado = 1;
                id_jugador_idx = lista_jugadores->num_jugadores - 1; 
                printf("Registro completado y guardado en disco. Bienvenido, %s.\n", lista_jugadores->jugadores[id_jugador_idx].nom_completo);
            } else {
                printf("\nRegistro cancelado. Volviendo al inicio...\n\n");
            }
        }
    }
    
    // --- MENÚ DEL JUEGO ---
    int opcion_menu = 0;
    char id_activo[10];
    strcpy(id_activo, lista_jugadores->jugadores[id_jugador_idx].Id_jug);

    do {
        printf("\n-----------------------\n");
        printf("  MENU PRINCIPAL \n");
        printf("-----------------------\n");
        printf("  1. Nueva partida\n");
        printf("  2. Cargar partida\n");
        printf("  3. Salir\n");
        printf("Selecciona una opcion: ");
        
        
        if (scanf("%d", &opcion_menu) != 1) {
            while (getchar() != '\n'); 
            opcion_menu = 0; 
        }

        switch(opcion_menu) {
            case 1:
                printf("\nEmpezando una nueva partida...\n");
                nueva_partida(&(lista_jugadores->jugadores[id_jugador_idx]), lista_obj, salas, num_salas, conexiones, num_conexiones, puzles, num_puzles);
                break;
            case 2:
                printf("\nCargando partida...\n");
                cargar_partida(lista_jugadores, lista_obj, salas, num_salas, conexiones, num_conexiones, puzles, num_puzles);
                break;
            case 3:
                printf("\nSaliendo del juego...\n");
                return;
            default:
                printf("\nOpcion [%d] no valida. Intentalo de nuevo.\n", opcion_menu);
                break;
        }
    } while(opcion_menu != 3);
}

void nueva_partida(jugador *jugador_actual, ListaObjetos *lista_obj, Sala salas[], int num_salas, Conexion conexiones[], int num_conexiones, Puzle puzles[], int num_puzles){
    printf("\n-------------------------\n");
    printf("  Iniciando nueva partida\n");
    printf("-------------------------\n");

    int sala_inicial = 1;
    partida(jugador_actual, lista_obj, salas, num_salas, conexiones, num_conexiones, puzles, num_puzles, sala_inicial);
}



void partida(jugador *jugador_actual, ListaObjetos *lista_obj, Sala salas[], int num_salas, Conexion conexiones[], int num_conexiones, Puzle puzles[], int num_puzles, int id_sala_actual) {
    int opcion = 0;
    char id_obj_input[5];
    char id_sala_str[21];
    char nombre_sala_actual[31] = "Desconocida"; 

    do {
        sprintf(id_sala_str, "%02d", id_sala_actual);

        //Buscamos el nombre de la sala actual
        for (int i = 0; i < num_salas; i++) {
            if (salas[i].id == id_sala_actual) {
                strcpy(nombre_sala_actual, salas[i].nombre);
                break;
            }
        }

        printf("\n-------------------------------\n");
        // Imprimimos el nombre en lugar del numero
        printf("  Menu de Partida, sala: %s\n", nombre_sala_actual); 
        printf("---------------------------------\n");
        printf("  1. Describir sala\n");
        printf("  2. Examinar (objetos y salidas)\n");
        printf("  3. Entrar en otra sala\n");
        printf("  4. Coger objeto\n");
        printf("  5. Soltar objeto\n");
        printf("  6. Inventario\n");
        printf("  7. Usar objeto\n");
        printf("  8. Resolver puzle / introducir codigo\n");
        printf("  9. Guardar partida\n");
        printf(" 10. Volver al menu principal\n");
        printf("-------------------------------\n");
        printf("Elige una opcion: ");
        
        if (scanf("%d", &opcion) != 1) {
            while (getchar() != '\n'); 
            opcion = 0; 
        }

        switch(opcion) {
            case 1:
                printf("\n  Has elegido Describir sala\n");
                describir_sala(id_sala_actual, salas, num_salas);
                break;

            case 2: 
                printf("\n  Has elegido Examinar\n");
                examinar_sala(id_sala_actual, salas, num_salas, conexiones, num_conexiones, lista_obj);
                break;

            case 3: 
                printf("\n  Has elegido Entrar en otra sala\n");
                id_sala_actual = entrar_en_otra_sala(id_sala_actual, conexiones, num_conexiones);
                
                if(id_sala_actual == 20){
                    printf("\n  !!Felicidades has llegado a la sala final. Saliendo del juego!!\n");
                    return;
                }
                break;

            case 4: {
                int num_obj;
                printf("\n  Has elegido Coger objeto\n");
                printf("  Introduce el numero del objeto (ej: 01): ");
                
                if (scanf("%d", &num_obj) == 1) {
                    sprintf(id_obj_input, "OB%02d", num_obj);
                    cogerObjeto(lista_obj, jugador_actual, id_obj_input, id_sala_str);
                } else {
                    while (getchar() != '\n');
                    printf("  Error: Debes introducir un numero.\n");
                }
                break;
            }

            case 5: {
                int num_obj;
                printf("\n  Has elegido Soltar objeto\n");
                printf("  Introduce el numero del objeto que quieres soltar: ");
                
                if (scanf("%d", &num_obj) == 1) {
                    sprintf(id_obj_input, "OB%02d", num_obj);
                    soltarObjeto(lista_obj, jugador_actual, id_obj_input, id_sala_str);
                } else {
                    while (getchar() != '\n');
                    printf("  Error: Debes introducir un numero.\n");
                }
                break;
            }

            case 6: 
                printf("\n  Has elegido Inventario\n");
                printf("-------------------------------\n");
                mostrarInventario(jugador_actual);
                printf("-------------------------------\n");
                break;

            case 7: {
                int num_obj;
                printf("\n  Has elegido Usar objeto\n");
                printf("  Introduce el numero del objeto que quieres usar: ");
                
                if (scanf("%d", &num_obj) == 1) {
                    sprintf(id_obj_input, "OB%02d", num_obj);
                    usarObjeto(lista_obj, jugador_actual, id_obj_input, id_sala_actual, conexiones, num_conexiones);
                } else {
                    while (getchar() != '\n');
                    printf("  Error: Debes introducir un numero.\n");
                }
                break;
            }

            case 8:
                printf("\n  Has elegido Resolver puzle\n");
                resolver_puzle(id_sala_actual, puzles, num_puzles, conexiones, num_conexiones);
                break;
            case 9:
                printf("\n  Guardando partida...\n");
                guardar_partida(jugador_actual->Id_jug, id_sala_actual, lista_obj->objetos, lista_obj->num_objetos, conexiones, num_conexiones, puzles, num_puzles);
                break;
            case 10:
                printf("\n  Saliendo de la partida... Volviendo al menu principal.\n");
                return;
            default:
                printf("\n  Opcion invalida. Intentalo de nuevo (1-10).\n");
                break;
        }
    } while (opcion != 10 && id_sala_actual != 15);
}


//Funcion para guardar la partida
void guardar_partida(char id_jugador[], int id_sala, objetos objetos[], int num_objetos, Conexion conexiones[], int num_conexiones, Puzle puzles[], int num_puzles) {
    
    char lineas_a_guardar[50][100]; 
    int total_lineas = 0;

    //Guardar Jugador
    sprintf(lineas_a_guardar[total_lineas], "JUGADOR: %s", id_jugador);
    total_lineas++;
    
    //Guardar Sala actual 
    sprintf(lineas_a_guardar[total_lineas], "SALA: %02d", id_sala);
    total_lineas++;
    
    //Guardar Objetos
    for (int i = 0; i < num_objetos; i++) {
        sprintf(lineas_a_guardar[total_lineas], "OBJETO: %s-%s", objetos[i].Id_obj, objetos[i].locacion);
        total_lineas++;
    }
    
    //Guardar Conexiones 
    for (int i = 0; i < num_conexiones; i++) {
        sprintf(lineas_a_guardar[total_lineas], "CONEXIÓN: %s-%s", conexiones[i].id, conexiones[i].estado);
        total_lineas++;
    }
    
    //Guardar Puzles 
    for (int i = 0; i < num_puzles; i++) {
        sprintf(lineas_a_guardar[total_lineas], "PUZLE: %s-%s", puzles[i].id, puzles[i].estado);
        total_lineas++;
    }

    printf("\n>>> Datos del juego traducidos a texto correctamente...\n");


    char *nombreFichero = "Partida.txt";

    //Funcion para escribir en fichero
    escribir_fichero(nombreFichero, lineas_a_guardar, total_lineas);
    
    printf(">>> Partida enviada al disco duro. ¡Guardado completado!\n");
}



// Especialista en Jugadores
void parsear_jugador(char linea[], char id_jugador[]) {
    sscanf(linea, "JUGADOR: %s", id_jugador);
}

// Especialista en Salas 
void parsear_sala(char linea[], int *sala) {
    sscanf(linea, "SALA: %d", sala);
}

// Especialista en Objetos
void parsear_objeto(char linea[], objetos *obj) {
    sscanf(linea, "OBJETO: %[^-]-%s", obj->Id_obj, obj->locacion);
}

// Especialista en Conexiones
void parsear_conexion(char linea[], Conexion *con) {
    sscanf(linea, "CONEXIÓN: %[^-]-%s", con->id, con->estado);
}

// Especialista en Puzles
void parsear_puzle(char linea[], Puzle *puz) {
    sscanf(linea, "PUZLE: %[^-]-%s", puz->id, puz->estado);
}


void cargar_partida(ListaJugadores *lista_jugadores, ListaObjetos *lista_obj, Sala salas[], int num_salas, Conexion conexiones[], int num_conexiones, Puzle puzles[], int num_puzles) {
    
    char lineas_leidas[100][100];
    int total_lineas = leer_fichero("Partida.txt", lineas_leidas);

    if (total_lineas == 0) {
        printf("-> No hay ninguna partida guardada o hubo un error al leer el archivo.\n");
        return;
    }

    char id_jugador_recuperado[10] = ""; 
    int sala_recuperada = 1;

    for (int i = 0; i < total_lineas; i++) {
        
        if (strncmp(lineas_leidas[i], "JUGADOR:", 8) == 0) {
            parsear_jugador(lineas_leidas[i], id_jugador_recuperado);
            
        } else if (strncmp(lineas_leidas[i], "SALA:", 5) == 0) {
            parsear_sala(lineas_leidas[i], &sala_recuperada);
            
        } else if (strncmp(lineas_leidas[i], "OBJETO:", 7) == 0) {
            objetos obj_temp;
            parsear_objeto(lineas_leidas[i], &obj_temp);
            for(int j = 0; j < lista_obj->num_objetos; j++) {
                if(strcmp(lista_obj->objetos[j].Id_obj, obj_temp.Id_obj) == 0) {
                    strcpy(lista_obj->objetos[j].locacion, obj_temp.locacion);
                    break;
                }
            }
            
        } else if (strncmp(lineas_leidas[i], "CONEXIÓN:", 10) == 0) {
            Conexion con_temp;
            parsear_conexion(lineas_leidas[i], &con_temp);
            for(int j = 0; j < num_conexiones; j++) {
                if(strcmp(conexiones[j].id, con_temp.id) == 0) {
                    strcpy(conexiones[j].estado, con_temp.estado);
                    break;
                }
            }
            
        } else if (strncmp(lineas_leidas[i], "PUZLE:", 6) == 0) {
            Puzle puz_temp;
            parsear_puzle(lineas_leidas[i], &puz_temp);
            for(int j = 0; j < num_puzles; j++) {
                if(strcmp(puzles[j].id, puz_temp.id) == 0) {
                    strcpy(puzles[j].estado, puz_temp.estado);
                    break;
                }
            }
        }
    }

    // Buscamos al jugador
    jugador *jugador_encontrado = NULL;
    for(int i = 0; i < lista_jugadores->num_jugadores; i++) {
        if(strcmp(lista_jugadores->jugadores[i].Id_jug, id_jugador_recuperado) == 0) {
            jugador_encontrado = &(lista_jugadores->jugadores[i]);
            break;
        }
    }

    if(jugador_encontrado != NULL) {
        printf("\n>>> Partida cargada con exito. Retomando mision...\n");
        partida(jugador_encontrado, lista_obj, salas, num_salas, conexiones, num_conexiones, puzles, num_puzles, sala_recuperada);
    } else {
        printf("\n>>> Error: El jugador de la partida guardada no existe en el sistema.\n");
    }
}
