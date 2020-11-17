#ifndef FUNCIONES_H
#define FUNCIONES_H

#include "grafo.h"

#define INFINITY 1000

//FUNCIONES DEL PROGRAMA DE PRUEBA DE GRAFOS
//Opción a del menú, introducir un vertice en el grafo
void nueva_habitacion(grafo *G);

//Opción b del menú, eliminar un vértice del grafo
void eliminar_habitacion(grafo *G);

//Opción c del menú, crear una relación entre dos vértices
void nueva_comunicacion(grafo *G);

//Opción d del menú, eliminar una relación entre dos vértices
void eliminar_comunicacion(grafo *G);

//Opción i del menú, imprimir el grafo
void imprimir_mapa(grafo G);

//Función para leer el grafo de un archivo
void leer_grafo(grafo *G);

//Función para escribir el grafo a un archivo
void guardar_grafo(grafo G);

void ruta_rapida(grafo G);

void coste_minimo(grafo G);


#endif	/* FUNCIONES_H */

