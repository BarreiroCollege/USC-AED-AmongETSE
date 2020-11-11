#include "abb.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "FuncionesAmongETSE.h"

/**
 * Los cambios adicionales son varios cambios pequeños para mejorar las posibilidades de juego:
 * menu() -> en vez de jugar partida continuamente, se permiten usar otras opciones del menú durante la partida
 * _expulsarImpostor() -> se permite NO expulsar a algún jugador al final de cada turno
 * generarPartida() -> se permite jugar sin saber cuando se expulsa a un impostor ni cuantos hay
 */


int menu(abb *jugadores, unsigned short *jugando);

int main(int argc, char **argv) {
    // Semilla para aleatorios, se llamar sólo una vez al principio de main
    srand((unsigned int) time(NULL));
    unsigned short jugando = 0;

    // Crear el árbol de jugadores
    abb jugadores;
    crear(&jugadores);

    // Leer el archivo de disco
    leerArchivo(&jugadores);

    // Menú
    int partida = 1;
    while (partida) {
        partida = menu(&jugadores, &jugando);
    }


    // Destruir el árbol al finalizar
    destruir(&jugadores);

    return EXIT_SUCCESS;
}

int menu(abb *jugadores, unsigned short *jugando) {
    printf("\n---------------------\n\n");
    printf("Among ETSE\n\n");
    if (!*jugando) {
        printf("a.\tAlta de un jugador\n");
        printf("b.\tBaja de un jugador\n");
    }
    printf("l.\tListado por orden alfabética de los jugadores\n");
    if (!*jugando) {
        printf("g.\tGenerar datos iniciales de la partida\n");
    } else {
        printf("g.\tJugar partida\n");
    }
    printf("u.\tConsulta por usuario de la última tarea asignada\n");
    printf("h.\tConsulta por habitación\n");
    if (!*jugando) {
        printf("f.\tGuardar archivo\n");
    }
    printf("s.\tSalir de la partida\n");
    printf("\n> ");

    char c;
    scanf(" %c", &c);
    printf("\n");

    switch (c) {
        // Alta de un jugador
        case 'a':
        case 'A':
            if (!*jugando)
                altaJugador(jugadores);
            break;

        // Baja de un jugador
        case 'b':
        case 'B':
            if (!*jugando)
                bajaJugador(jugadores);
            break;

        // Listado por orden alfabética de los jugadores
        case 'l':
        case 'L':
            listadoJugadores(*jugadores, *jugando);
            break;

        // Generar datos iniciales de la partida
        case 'g':
        case 'G':
        case 'j':
        case 'J':
            if (!*jugando) {
                *jugando = generarPartida(jugadores);
            } else if (jugarPartida(jugadores, *jugando)) {
                *jugando = 0;
            }
            break;

        // Consulta por usuario de la última tarea asignada
        case 'u':
        case 'U':
            consultarJugador(*jugadores);
            break;

        // Consulta por habitación
        case 'h':
        case 'H':
            consultarPorHabitacion(*jugadores, *jugando);
            break;

        // Guardar árbol de jugadores en el archivo
        case 'F':
        case 'f':
            if (!*jugando)
                guardarArchivo(*jugadores);
            break;

        // Salir del programa...
        case 's':
            // Se destruye en el main
            printf("Saliendo...\n");
            return 0;

        default:
            printf("Opción no válida\n");
            break;
    }

    return 1;
}
