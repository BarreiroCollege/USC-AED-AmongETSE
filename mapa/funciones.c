#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"

//FUNCIONES DEL PROGRAMA DE PRUEBA DE GRAFOS

//Opción a del menú, introducir un vertice en el grafo

void introducir_vertice(grafo *G) {
    tipovertice v1;
    printf("Introduce vertice: ");
    scanf("%s", v1.habitacion);
    if (existe_vertice(*G, v1)) {
        printf("Ese vertice ya esta en el grafo\n");
    } else {
        insertar_vertice(G, v1);
    }
}
//Opción b del menú, eliminar un vértice del grafo

void eliminar_vertice(grafo *G) {
    tipovertice v1;
    printf("Introduce vertice: ");
    scanf("%s", v1.habitacion);
    if (existe_vertice(*G, v1)) {
        borrar_vertice(G, v1);
    } else {
        printf("Ese vertice no existe en el grafo\n");
    }
}

//Opción c del menú, crear una relación entre dos vértices

void nuevo_arco(grafo *G) {
    char valor[3];
    char tipo[1];
    tipovertice v1, v2;
    //Insertamos una nueva relación pidiendo los datos al usuario controlando que existan los vértices
    printf("Nueva relacion vertice1-->vertice2\n");

    //Vértice origen del arco
    printf("Introduce vertice origen: ");
    scanf("%s", v1.habitacion);
    if (!existe_vertice(*G, v1)) {
        printf("El vertice %s no existe en el grafo\n", v1.habitacion);
        return;
    }

    //Vértice destino del arco
    printf("Introduce vertice destino: ");
    scanf("%s", v2.habitacion);
    if (!existe_vertice(*G, v2)) {
        printf("El vertice %s no existe en el grafo\n", v2.habitacion);
        return;
    }

    //Valor del arco
    printf("Introduce valor del arco: ");
    scanf("%s", valor);
    if (atoi(valor) < 1) {
        printf("El valor %d no es válido\n", atoi(valor));
        return;
    }

    // Tipo de arco
    printf("Introduce el tipo de arco {T = Tripulante | I = Impostor}: ");
    scanf("%s", tipo);
    if (*tipo != 'C' && *tipo != 'c' && *tipo != 'T' && *tipo != 't' && *tipo != 'I' && *tipo != 'i') {
        printf("El tipo %s no es válido\n", tipo);
        return;
    }

    //Creación del arco
    int ady;
    if (*tipo == 'I' || *tipo == 'i') {
        ady = son_adyacentes_I(*G, posicion(*G, v1), posicion(*G, v2));
        if (ady == 0 || ady > atoi(valor)) {
            crear_arco_I(G, posicion(*G, v1), posicion(*G, v2), atoi(valor));
        }
    } else {
        if (!son_adyacentes_T(*G, posicion(*G, v1), posicion(*G, v2))) {
            crear_arco_T(G, posicion(*G, v1), posicion(*G, v2), atoi(valor));
        }
    }
}

//Opción d del menú, eliminar una relación entre dos vértices
void eliminar_arco(grafo *G) {
    tipovertice v1, v2;
    char tipo[1];

    //Eliminamos una relación pidiendo los datos al usuario controlando que existan los vértices
    printf("Eliminar relacion vertice1-->vertice2\n");
    //Vértice origen del arco
    printf("Introduce vertice origen: ");
    scanf("%s", v1.habitacion);
    if (!existe_vertice(*G, v1)) {
        printf("El vertice %s no existe en el grafo\n", v1.habitacion);
        return;
    }

    //Vértice destino del arco
    printf("Introduce vertice destino: ");
    scanf("%s", v2.habitacion);
    if (!existe_vertice(*G, v2)) {
        printf("El vertice %s no existe en el grafo\n", v2.habitacion);
        return;
    }

    // Tipo de arco
    printf("Introduce el tipo de arco {T = Tripulante | I = Impostor}: ");
    scanf("%s", tipo);
    if (*tipo != 'C' && *tipo != 'c' && *tipo != 'T' && *tipo != 't' && *tipo != 'I' && *tipo != 'i') {
        printf("El tipo %c no es válido\n", tipo);
        return;
    }

    //Eliminación del arco
    if (*tipo == 'I' || *tipo == 'i') {
        if (son_adyacentes_I(*G, posicion(*G, v1), posicion(*G, v2))) {
            borrar_arco_I(G, posicion(*G, v1), posicion(*G, v2));
        }
    } else {
        if (son_adyacentes_T(*G, posicion(*G, v1), posicion(*G, v2))) {
            borrar_arco_T(G, posicion(*G, v1), posicion(*G, v2));
        }
    }
}

//Opción i del menú, imprimir el grafo
//Función que imprime el grafo utilizando num_vertices para saber cuántos vértices tiene
//y array_vertices para recuperar el vector de vértices y recorrerlo

void imprimir_grafo(grafo G) {
    tipovertice *VECTOR; //Para almacenar el vector de vértices del grafo
    int N; //número de vértices del grafo

    //Para recorrerla, simplemente vamos a recorrer la matriz de adyacencia
    N = num_vertices(G);
    VECTOR = array_vertices(G);

    int i, j, valorI, valorT;
    printf("El grafo actual es:\n");
    for (i = 0; i < N; i++) {
        //Imprimo el vértice
        printf("Vertice(%d): %s\n", i, VECTOR[i].habitacion);
        //Chequeo sus arcos
        for (j = 0; j < N; j++) {
            valorI = son_adyacentes_I(G, i, j);
            valorT = son_adyacentes_T(G, i, j);

            printf("%d,%d\n", valorT, valorI);

            if (valorI != 0) {
                if (valorT != 0) {
                    printf("\t%s --- {%d} --- %s\n", VECTOR[i].habitacion, valorT, VECTOR[j].habitacion);
                }
                if (valorI != valorT) {
                    printf("\t%s ... {%d} ... %s\n", VECTOR[i].habitacion, valorI, VECTOR[j].habitacion);
                }
            }
        }
    }
}
