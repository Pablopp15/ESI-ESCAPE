#include <stdio.h>
#include <string.h> 
#include "Partida.h"


//Cabecera: void iniciar_juego()
/*Precondición: Los ficheros de la base de datos existen, son accesibles y cumplen su formato. Las constantes MAX_SALAS, MAX_CONEXIONES y 
MAX_PUZLES están definidas en el sistema y son > 0.*/
/*Postcondición: Inicializa las estructuras del sistema, transfiere el control de ejecución al bucle del menú principal y, tras su finalización, 
libera toda la memoria dinámica.*/
void iniciar_juego() {
    printf("Arrancando el motor de ESI ESCAPE...\n");

    ListaJugadores mi_lista_jugadores;
    inicializarListaJugadores(&mi_lista_jugadores);

    ListaObjetos mi_lista_objetos;
    leerObjetos("objetos.txt", &mi_lista_objetos); 

    //CARGAMOS LOS JUGADORES DESDE EL TXT
    char lineas_jugadores[300][300];
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
    Sala mis_salas[MAX_SALAS];           int total_salas = 0;
    Conexion mis_conexiones[MAX_CONEXIONES]; int total_conexiones = 0;
    Puzle mis_puzles[MAX_PUZLES];        int total_puzles = 0;

    gestionarFicheros(mis_puzles, &total_puzles, mis_salas, &total_salas, mis_conexiones, &total_conexiones, CARGAR);

    printf(">> Datos cargados: %d jugadores, %d salas, %d conexiones.\n", 
            mi_lista_jugadores.num_jugadores, total_salas, total_conexiones);

    //LLamamos a la funcion menu_principal
    menu_principal(&mi_lista_jugadores, &mi_lista_objetos, mis_salas, total_salas, mis_conexiones, total_conexiones, mis_puzles, total_puzles);

    //Limpiamos memoria al salir
    liberarJugadores(&mi_lista_jugadores);
    liberarObjetos(&mi_lista_objetos);
    
    printf("\nCerrando el programa de forma segura. Hasta pronto!\n");
}



/*Cabecera: void menu_principal(ListaJugadores *lista_jugadores, ListaObjetos *lista_obj, Sala salas[], int num_salas, Conexion conexiones[], int num_conexiones, 
Puzle puzles[], int num_puzles)*/
/*Precondición: Las estructuras de datos pasadas por parámetro deben estar previamente inicializadas en memoria y no ser nulas. Los parámetros numéricos de 
cantidad deben ser >= 0.*/
/*Postcondición: Gestiona el sistema de autenticación. Muestra el menú iterativo y deja el control a nueva_partida()
o cargar_partida() según la elección del usuario, hasta que este elige "Salir".*/
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
            printf("Quieres registrarte con este perfil? (s/n): ");
            
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

                char linea_nueva[1][300]; 
                sprintf(linea_nueva[0], "%s-%s-%s-%s", 
                        nuevo_j.Id_jug, 
                        nuevo_j.nom_completo, 
                        nuevo_j.nom_usuario, 
                        nuevo_j.contrasena);
                
                escribir_fichero("Jugadores.txt", linea_nueva, 1);

                logueado = 1;
                id_jugador_idx = lista_jugadores->num_jugadores - 1; 
                printf("Registro completado, bienvenido, %s.\n", lista_jugadores->jugadores[id_jugador_idx].nom_completo);
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
                cargar_partida(&(lista_jugadores->jugadores[id_jugador_idx]), lista_obj, salas, num_salas, conexiones, num_conexiones, puzles, num_puzles);
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


/*Cabecera: void nueva_partida(jugador *jugador_actual, ListaObjetos *lista_obj, Sala salas[], int num_salas, Conexion conexiones[], int num_conexiones, 
Puzle puzles[], int num_puzles)*/
/*Precondición: El puntero jugador_actual hace referencia a un perfil de usuario válido y logueado en el sistema. Las listas y vectores del entorno del juego 
están correctamente inicializados en memoria y sus respectivos contadores numéricos son >= 0.*/
/*Postcondición: Imprime por pantalla la cabecera visual de inicio y transfiere el control a la función de la lógica central, inicializando la posición 
del jugador en la sala de inicio.*/
void nueva_partida(jugador *jugador_actual, ListaObjetos *lista_obj, Sala salas[], int num_salas, Conexion conexiones[], int num_conexiones, Puzle puzles[], int num_puzles){
    printf("\n-------------------------\n");
    printf("  Iniciando nueva partida\n");
    printf("-------------------------\n");

    int sala_inicial = 1;
    partida(jugador_actual, lista_obj, salas, num_salas, conexiones, num_conexiones, puzles, num_puzles, sala_inicial);
}


/*Cabecera: void partida(jugador *jugador_actual, ListaObjetos *lista_obj, Sala salas[], int num_salas, Conexion conexiones[], int num_conexiones, Puzle puzles[], 
int num_puzles, int id_sala_actual)*/
/*Precondición: El puntero jugador_actual hace referencia a un perfil válido. Las estructuras de datos del entorno están correctamente inicializadas y cargadas en 
memoria con sus respectivos contadores >= 0. La variable id_sala_actual contiene un identificador numérico válido correspondiente a una sala existente.*/
/*Postcondición: Ejecuta el bucle principal de interacción del juego, mostrando el menú de la sala actual y procesando las acciones del jugador. 
El bucle finaliza y devuelve el control al menú principal únicamente si el jugador elige la opción de salir o si logra alcanzar la sala final.*/
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
                    printf("\n  Felicidades has llegado a la sala final. Saliendo del juego!!\n");
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
    } while (opcion != 10);
}


/*Cabecera: void guardar_partida(char id_jugador[], int id_sala, objetos objetos[], int num_objetos, Conexion conexiones[], int num_conexiones, Puzle puzles[], 
int num_puzles)*/
/*Precondición: Los vectores de datos (objetos, conexiones, puzles) están correctamente inicializados en memoria y sus respectivos tamaños 
son >= 0. La suma total de los datos a guardar (jugador + sala + objetos + conexiones + puzles) no debe superar la capacidad máxima de la matriz temporal (150 líneas).*/
/*Postcondición: Traduce el estado actual de la partida (jugador activo, sala en la que se encuentra, ubicación de los objetos, estado de las puertas/conexiones y 
estado de los puzles) a un formato de texto plano y llama al módulo de ficheros para persistir los datos en el disco duro ("Partida.txt").*/
void guardar_partida(char id_jugador[], int id_sala, objetos objetos[], int num_objetos, Conexion conexiones[], int num_conexiones, Puzle puzles[], int num_puzles) {
    
    char lineas_a_guardar[150][300]; 
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
    
    printf(">>> Partida guardada\n");
}



//Cabecera: void parsear_jugador(char linea[], char id_jugador[])
/*Precondición: El vector de caracteres 'linea' contiene texto válido con el formato esperado ("JUGADOR: %s"). La cadena 'id_jugador' tiene memoria suficiente 
reservada para almacenar el identificador extraído.*/
/*Postcondición: Extrae el ID del jugador de la cadena de texto de entrada y lo almacena en la variable 'id_jugador' pasada por referencia.*/
void parsear_jugador(char linea[], char id_jugador[]) {
    sscanf(linea, "JUGADOR: %s", id_jugador);
}

//Cabecera: void parsear_sala(char linea[], int *sala)
/*Precondición: El vector de caracteres 'linea' contiene texto válido con el formato esperado ("SALA: %d"). El puntero 'sala' apunta a una dirección de memoria 
entera válida.*/
/*Postcondición: Extrae el identificador numérico de la sala desde la cadena de texto y modifica el valor de la variable apuntada por 'sala'.*/
void parsear_sala(char linea[], int *sala) {
    sscanf(linea, "SALA: %d", sala);
}

//Cabecera: void parsear_objeto(char linea[], objetos *obj)
/*Precondición: El vector de caracteres 'linea' respeta el formato de guardado de objetos ("OBJETO: %[^-]-%s"). El puntero 'obj' apunta a una estructura 'objetos' 
válida y reservada en memoria.*/
/*Postcondición: Analiza la línea de texto y extrae el identificador del objeto y su locación, almacenando ambos valores en los campos correspondientes de la 
estructura apuntada por 'obj'.*/
void parsear_objeto(char linea[], objetos *obj) {
    sscanf(linea, "OBJETO: %[^-]-%s", obj->Id_obj, obj->locacion);
}

//Cabecera: void parsear_conexion(char linea[], Conexion *con)
/*Precondición: El vector de caracteres 'linea' cumple con la sintaxis de guardado de conexiones ("CONEXIÓN: %[^-]-%s"). El puntero 'con' hace referencia a una 
estructura 'Conexion' existente.*/
/*Postcondición: Extrae el identificador y el estado actual de la conexión desde la línea de texto, y actualiza los campos respectivos en la estructura apuntada 
por 'con'.*/
void parsear_conexion(char linea[], Conexion *con) {
    sscanf(linea, "CONEXIÓN: %[^-]-%s", con->id, con->estado);
}

//Cabecera: void parsear_puzle(char linea[], Puzle *puz)
/*Precondición: El vector de caracteres 'linea' contiene una cadena válida con el formato "PUZLE: %[^-]-%s". El puntero 'puz' apunta a una estructura 'Puzle' 
previamente inicializada.*/
/*Postcondición: Parsea el texto introducido para separar el identificador del puzle y su estado (ej. "Resuelto" o "Pendiente"), guardando esta información en 
los campos correspondientes de la estructura 'puz'.*/
void parsear_puzle(char linea[], Puzle *puz) {
    sscanf(linea, "PUZLE: %[^-]-%s", puz->id, puz->estado);
}


/*Cabecera: void cargar_partida(jugador *jugador_actual, ListaObjetos *lista_obj, Sala salas[], int num_salas, Conexion conexiones[], int num_conexiones, 
Puzle puzles[], int num_puzles)*/
/*Precondición: El puntero jugador_actual hace referencia a un usuario válido logueado en el sistema. Las estructuras de datos del juego (lista de objetos, vectores 
de salas, conexiones y puzles) están correctamente inicializadas en memoria. La función de lectura de ficheros está operativa.*/
/*Postcondición: Lee el archivo "Partida.txt" para recuperar el estado del juego. Si la partida guardada pertenece al jugador actual, actualiza la memoria con la sala
guardada, ubicaciones de objetos y estados de conexiones y puzles, para luego ceder el control a la función partida() y continuar jugando. Si la partida pertenece
a otro usuario o no existe, aborta la carga sin modificar la memoria y devuelve el control al menú.*/
void cargar_partida(jugador *jugador_actual, ListaObjetos *lista_obj, Sala salas[], int num_salas, Conexion conexiones[], int num_conexiones, Puzle puzles[], int num_puzles) {
    
    char lineas_leidas[300][300];
    int total_lineas = leer_fichero("Partida.txt", lineas_leidas);

    if (total_lineas == 0) {
        printf("-> No hay ninguna partida guardada.\n");
        return;
    }

    char id_jugador_recuperado[10] = ""; 
    int sala_recuperada = 1;


    for (int i = 0; i < total_lineas; i++) {
        if (strncmp(lineas_leidas[i], "JUGADOR:", 8) == 0) {
            parsear_jugador(lineas_leidas[i], id_jugador_recuperado);
            break;
        }
    }


    if (strcmp(jugador_actual->Id_jug, id_jugador_recuperado) != 0) {
        printf("\n>>> Error: No tienes ninguna partida guardada con este perfil.\n");
        printf(">>> Debes empezar una Nueva Partida.\n");
        return; 
    }

    for (int i = 0; i < total_lineas; i++) {
        if (strncmp(lineas_leidas[i], "SALA:", 5) == 0) {
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

    printf("\n>>> Partida cargada con exito. Retomando mision...\n");
    partida(jugador_actual, lista_obj, salas, num_salas, conexiones, num_conexiones, puzles, num_puzles, sala_recuperada);
}
