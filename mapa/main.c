#include <stdio.h>
#include <stdlib.h>
#include "funciones.h"

int main(int argc, char **argv) {
    grafo G;
    char opcion;

    //Creo el grafo
    crear_grafo(&G);

    leer_grafo(&G);

    do {
        printf("\n\n");
        printf("a. Añadir habitación\n");
        printf("b. Clausurar habitación\n");
        printf("c. Crear comunicación\n");
        printf("d. Eliminar comunicación\n");
        printf("i. Imprimir mapa\n");
        printf("r. Ruta más rápida entre dos habitaciones\n");
        printf("p. Árbol de expansión de coste mínimo\n");
        printf("s. Salir\n");

        printf("Opcion: ");
        scanf(" %c", &opcion);

        switch (opcion) {
            case 'a':
            case 'A':
                nueva_habitacion(&G);
                break;
            case 'b':
            case 'B':
                eliminar_habitacion(&G);
                break;
            case 'c':
            case 'C':
                nueva_comunicacion(&G);
                break;
            case 'd':
            case 'D':
                eliminar_comunicacion(&G);
                break;
            case 'i':
            case 'I':
                imprimir_mapa(G);
                break;
            case 'r':
            case 'R':
                ruta_rapida(G);
                break;
            case 'P':
            case 'p':
                coste_minimo(G);
                break;
            case 's':
            case 'S':
                opcion = 's';
                break;
            default:
                printf("Opción equivocada\n");
        }
    } while (opcion != 's');

    guardar_grafo(G);

    // Al salir, liberamos la memoria del TAD, lo destruimos
    borrar_grafo(&G);

    return (EXIT_SUCCESS);
}

