#ifndef FUNCIONESAMONGETSE_H
#define FUNCIONESAMONGETSE_H

#include "abb.h"

/**
 * lee un archivo de jugadores de un fichero
 * @param A
 */
void leerArchivo(abb *A);

/**
 * Inserta un nuevo jugador en el árbol
 * @param A
 */
void altaJugador(abb *jugadores);

/**
 * Elimina un jugador en el árbol
 * @param A
 */
void bajaJugador(abb *jugadores);

/**
 * Imprime en inorden (alfabético) los nodos del árbol
 * @param A
 */
void listadoJugadores(abb jugadores);

/**
 * Genera una nueva partida, asignando valores a cada jugador
 * @param A
 */
void generarPartida(abb *jugadores);

/**
 * Consulta los datos de un jugador
 * @param A
 */
void consultarJugador(abb A);

/**
 * Consulta los jugadores que hay en una habitación
 * @param A
 */
void consultarPorHabitacion(abb A);

/**
 * Realiza el recorrido inorden del árbol de jugadores
 * @param abb A
 */
void inorden(abb A);


#endif    // FUNCIONESAMONGETSE_H

