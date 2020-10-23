#include "abb.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "FuncionesAmongETSE.h"


int menu(abb *jugadores);

int main(int argc, char** argv) {
    // Semilla para aleatorios, se llamar sólo una vez al principio de main
    srand((unsigned int) time(NULL));
    
    // Crear el árbol de jugadores
    abb jugadores;
    crear(&jugadores);
    
    // Leer el archivo de disco
    leerArchivo(&jugadores);
    
    // Menú
    int partida = 1;
    while (partida) {
        partida = menu(&jugadores);
    }

    
    // Destruir el árbol al finalizar
    destruir(&jugadores);

    return EXIT_SUCCESS;
}

int menu(abb *jugadores) {
    printf("\n---------------------\n\n");
    printf("Among ETSE\n\n");
    printf("a.\tAlta de un jugador\n");
    printf("b.\tBaja de un jugador\n");
    printf("l.\tListado por orden alfabética de los jugadores\n");
    printf("g.\tGenerar datos iniciales de la partida\n");
    printf("u.\tConsulta por usuario de la última tarea asignada\n");
    printf("h.\tConsulta por habitación\n");
    printf("s.\tSalir de la partida\n");
    printf("\n> ");

    char c;
    scanf(" %c", &c);
    printf("\n");

    switch (c) {
        // Alta de un jugador
        case 'a':
        case 'A':
            altaJugador(jugadores);
            break;

        // Baja de un jugador
        case 'b':
        case 'B':
            bajaJugador(jugadores);
            break;

        // Listado por orden alfabética de los jugadores
        case 'l':
        case 'L':
            listadoJugadores(*jugadores);
            break;

        // Generar datos iniciales de la partida
        case 'g':
        case 'G':
            generarPartida(jugadores);
            break;

        // Consulta por usuario de la última tarea asignada
        case 'u':
        case 'U':
            consultarJugador(*jugadores);
            break;

        // Consulta por habitación
        case 'h':
        case 'H':
            consultarPorHabitacion(*jugadores);
            break;

        case 's':
            printf("Saliendo...\n");
            return 0;

        default:
            printf("Opción no válida\n");
            break;
    }

    return 1;
}
