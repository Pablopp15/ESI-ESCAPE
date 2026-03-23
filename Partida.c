#include <stdio.h>
#include <string.h> 
#include "Partida.h"

void menu_principal(Jugador lista_jugadores[], int *num_jugadores){
    char usu[11];
    char cont[9];
    int logueado = 0;
    int id_jugador = -1;
    printf("\n-------------------------------\n");
    printf("  Bienvenido al juego\n");
    printf("  ESI ESCAPE\n");
    printf("\n-------------------------------\n");
    while (!logueado){
        printf("Introduce tu usuario: ");
        scanf("%10s", usu);
        printf("Introduce tu contrasenya: ");
        scanf("%8s", cont);
        int encontrado = 0;
        for(int i = 0; i< *num_jugadores; i++){
            if (strcmp(lista_jugadores[i].usuario, usu) == 0){
                encontrado = 1;
                if(strcmp(lista_jugadores[i].contrasena, cont) == 0){
                    logueado = 1;
                    id_jugador = i;
                    printf("\n Login correcto. Acceso concedido.\n");
                }else {
                    printf("\n Contrasenya incorrecta. Intentalo de nuevo.\n");
                }
                break;
            }
        }

        if(!encontrado){
            char respuesta;
            printf("\n El usuario '%s' no existe.\n", usu);
            printf("¿Quieres registrarte con este perfil? (s/n): ");
            scanf(" %c", &respuesta);
            if(respuesta == 's' || respuesta == 'S'){
                int nuevo_idx = *num_jugadores;
                sprintf(lista_jugadores[nuevo_idx].id_jugador, "%02d", nuevo_idx + 1);
                strcpy(lista_jugadores[nuevo_idx].usuario, usu);
                strcpy(lista_jugadores[nuevo_idx].contrasena, cont);

                printf("Introduce tu Nombre Completo ");
                scanf("%20s", lista_jugadores[nuevo_idx].nomb_jugador);
                (*num_jugadores)++;
                logueado = 1;
                id_jugador = nuevo_idx;
                printf("Registro completado. Acceso concedido. \n");
            }
        }
    }
    
    //Menu de nueva partida, cargar partida y salir
    int opcion_menu = 0;
    char id_activo[3];
    strcpy(id_activo, lista_jugadores[id_jugador].id_jugador);
    do{
    printf("\n-----------------------\n");
    printf("  Menu: \n");
    printf("\n-----------------------\n");
    printf("\n       ESI ESCAPE      \n");
    printf("\n-----------------------\n");
    printf("  1. Nueva partida\n");
    printf("  2. Cargar partida\n");
    printf("  3. Salir\n");

    switch(opcion_menu){
        case 1:
            printf("Empezando una nueva partida\n");
            nueva_partida(id_jugador);
            break;
        case 2:
            printf("Cargando partida...\n");
            //cargar_partida()
            break;
        case 3:
            printf("Salir\n");
            return 0;
        default:
            printf("Opcion no valida. Intentalo de nuevo");
            break;
        }
    }
}

void nueva_partida(char id_jugador[]){

    printf("-------------------------");
    printf("  Iniciando nueva partida");
    printf("-------------------------");

    int sala_inicial = 1;
    menu(id_jugador, sala_inicial);
}



void partida(char id_jugador[], int id_sala_actual) {
    int opcion = 0;

    do {
        printf("\n  Menu de Partida:\n");
        printf("       Sala Actual: %02d        \n", id_sala_actual);
        printf("-------------------------------\n");
        printf("  1. Describir sala\n");
        printf("  2. Examinar (objetos y salidas)\n");
        printf("  3. Entrar en otra sala\n");
        printf("  4. Coger objeto\n");
        printf("  5. Soltar objeto\n");
        printf("  6. Inventario\n");
        printf("  7. Usar objeto\n");
        printf("  8. Resolver puzle / introducir codigo\n");
        printf("  9. Guardar partida\n");
        printf("  10. Volver al menu principal\n");
        printf("-------------------------------\n");
        printf("Elige una opcion: ");
        scanf("%d", &opcion);

        switch(opcion) {
            case 1:
                printf("\n  Has elegido Describir sala\n");
                // describir_sala();
                break;
            case 2: 
                printf("\n  Has elegido Examinar\n");
                // examinar_sala();
                break;
            case 3: 
                printf("\n  Has elegido Entrar en otra sala\n");
                // id_sala_actual = entrar_sala();
                if(id_sala_actual = 15){
                    printf("  !!Felicidades has llegado a la sala final. Saliendo del juego");
                }
                break;
            case 4:
                printf("\n  Has elegido Coger objeto\n");
                // coger_objeto();
                break;
            case 5: 
                printf("\n  Has elegido Soltar objeto\n");
                // soltar_objeto();
                break;
            case 6: 
                printf("\n  Has elegido Inventario\n");
                // mostrar_inventario();
                break;
            case 7:
                printf("\n  Has elegido Usar objeto\n");
                // usar_objeto());
                break;
            case 8:
                printf("\n  Has elegido Resolver puzle\n");
                // resolver_puzle(id_sala_actual);
                break;
            case 9:
                printf("\n  Guardando partida...\n");
                //guardar_partida(id_jugador, id_sala_actual, mis_objetos, num_objetos, mis_conexiones, num_conexiones, mis_puzles, num_puzles);
                break;
            case 10:
                printf("\n  Saliendo de la partida... Volviendo al menu principal.\n");
                break;
            default:
                printf("\n  Opcion invalida. Intentalo de nuevo (1-10).\n");
                break;
        }
    } while ((opcion != 10) || (id_sala_actual = 15));
}
