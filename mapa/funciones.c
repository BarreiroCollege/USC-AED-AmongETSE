#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "grafo.h"
#include "funciones.h"

//FUNCIONES DEL PROGRAMA DE PRUEBA DE GRAFOS

//Opción a del menú, introducir un vertice en el grafo

void nueva_habitacion(grafo *G) {
    tipovertice v1;
    printf("Nombre de la habitación: ");
    scanf("%s", v1.habitacion);
    if (existe_vertice(*G, v1)) {
        printf("Esta habitación ya esta en el mapa\n");
    } else {
        insertar_vertice(G, v1);
    }
}
//Opción b del menú, eliminar un vértice del grafo

void eliminar_habitacion(grafo *G) {
    tipovertice v1;
    printf("Nombre de la habitación: ");
    scanf("%s", v1.habitacion);
    if (existe_vertice(*G, v1)) {
        borrar_vertice(G, v1);
    } else {
        printf("Esta habitación no existe en el mapa\n");
    }
}

//Opción c del menú, crear una relación entre dos vértices

void nueva_comunicacion(grafo *G) {
    char valor[5];
    char tipo[5];
    tipovertice v1, v2;
    //Insertamos una nueva relación pidiendo los datos al usuario controlando que existan los vértices

    //Vértice origen del arco
    printf("Habitación de origen: ");
    scanf("%s", v1.habitacion);
    if (!existe_vertice(*G, v1)) {
        printf("La habitación %s no existe en el grafo\n", v1.habitacion);
        return;
    }

    //Vértice destino del arco
    printf("Habitación de destino: ");
    scanf("%s", v2.habitacion);
    if (!existe_vertice(*G, v2)) {
        printf("La habitación %s no existe en el grafo\n", v2.habitacion);
        return;
    }

    //Valor del arco
    printf("Valor de la comunicación: ");
    scanf("%s", valor);
    int v = atoi(valor);
    if (v < 1) {
        printf("El valor %d no es válido\n", v);
        return;
    }

    // Tipo de arco
    printf("Introduce el tipo de comunicación {T = Tripulante | I = Impostor}: ");
    scanf("%s", tipo);
    if (*tipo != 'C' && *tipo != 'c' && *tipo != 'T' && *tipo != 't' && *tipo != 'I' && *tipo != 'i') {
        printf("El tipo %s no es válido\n", tipo);
        return;
    }

    //Creación del arco
    int ady;
    if (*tipo == 'I' || *tipo == 'i') {
        ady = son_adyacentes_I(*G, posicion(*G, v1), posicion(*G, v2));
        if (ady == 0 || ady > v) {
            crear_arco_I(G, posicion(*G, v1), posicion(*G, v2), v);
        }
    } else {
        if (!son_adyacentes_T(*G, posicion(*G, v1), posicion(*G, v2))) {
            crear_arco_T(G, posicion(*G, v1), posicion(*G, v2), v);
        }
    }
}

//Opción d del menú, eliminar una relación entre dos vértices
void eliminar_comunicacion(grafo *G) {
    tipovertice v1, v2;
    char tipo[1];

    //Eliminamos una relación pidiendo los datos al usuario controlando que existan los vértices
    //Vértice origen del arco
    printf("Habitación de origen: ");
    scanf("%s", v1.habitacion);
    if (!existe_vertice(*G, v1)) {
        printf("La habitación %s no existe en el mapa\n", v1.habitacion);
        return;
    }

    //Vértice destino del arco
    printf("Habitación de destino: ");
    scanf("%s", v2.habitacion);
    if (!existe_vertice(*G, v2)) {
        printf("La habitación %s no existe en el mapa\n", v2.habitacion);
        return;
    }

    // Tipo de arco
    printf("Tipo de comunicación {T = Tripulante | I = Impostor}: ");
    scanf("%s", tipo);
    if (*tipo != 'C' && *tipo != 'c' && *tipo != 'T' && *tipo != 't' && *tipo != 'I' && *tipo != 'i') {
        printf("El tipo %s no es válido\n", tipo);
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

void imprimir_mapa(grafo G) {
    tipovertice *VECTOR; //Para almacenar el vector de vértices del grafo
    int N; //número de vértices del grafo

    //Para recorrerla, simplemente vamos a recorrer la matriz de adyacencia
    N = num_vertices(G);
    VECTOR = array_vertices(G);

    int i, j, valorI, valorT;
    printf("El grafo actual es:\n");
    for (i = 0; i < N; i++) {
        //Imprimo el vértice
        printf("Habitación(%d): %s\n", i, VECTOR[i].habitacion);
        //Chequeo sus arcos
        for (j = 0; j < N; j++) {
            valorI = son_adyacentes_I(G, i, j);
            valorT = son_adyacentes_T(G, i, j);

            // Si hay valor para tripulante, lo hay para impostor, por lo que
            // si impostor tiene valor siempre hay que imprimir algo
            if (valorI != 0) {
                // Si hay valor para tripulantes, se imprime
                if (valorT != 0) {
                    printf("\t--- {%d} %-14s\n", valorT, VECTOR[j].habitacion);
                }
                // Si el valor de impostor no es igual al de tripulante, hay otro camino
                if (valorI != valorT) {
                    printf("\t... {%d} %-14s\n", valorI, VECTOR[j].habitacion);
                }
            }
        }
    }
}

void leer_grafo(grafo *G) {
    // Abrir archivo
    FILE *f;
    f = fopen("among.txt", "r");
    if (!f) return;

    // Especificar si se pasa a leer los arcos y se acabó con los vértices
    int leyendoArcos = 0;

    // Los dos vértices del arco a leer (en caso de estar leyendo vértices, se
    // usa v1 sólo)
    tipovertice v1, v2;
    // -- para tripulantes, .. para impostores
    char codigo[2];
    // Valor del arco
    int valor;

    // Leer la primera línea
    char linea[40];
    fscanf(f, " %s", linea);
    // Hasta fin de archivo
    while (!feof(f)) {
        // Si la línea es un asterisco, se ha acabado de leer los vértices
        // y se debe pasar a los arcos
        if (!leyendoArcos && linea[0] == '*') {
            leyendoArcos = 1;
        } else {
            // Si no se están leyendo los arcos, se copia el nombre del vértice
            // al v1 y se inserta el vértice en el grafo
            if (!leyendoArcos) {
                strcpy(v1.habitacion, linea);
                insertar_vertice(G, v1);
            } else {
                // Si se están leyendo los arcos, entonces se lee la cadena de texto
                // con el formato especificado y se inserta en función de si es un
                // camino de impostores o de tripulantes
                sscanf(linea, "%[^-.]%[-.]%d-%s", v1.habitacion, codigo, &valor, v2.habitacion);
                if (codigo[0] == '.') {
                    crear_arco_I(G, posicion(*G, v1), posicion(*G, v2), valor);
                } else {
                    crear_arco_T(G, posicion(*G, v1), posicion(*G, v2), valor);
                }
            }
        }
        // Se lee la siguiente línea
        fscanf(f, " %s", linea);
    }

    // Cerramos archivo
    fclose(f);
}

void guardar_grafo(grafo G) {
    // Abrir archivo en modo sobreescribir
    FILE *f;
    f = fopen("among.txt", "w");
    if (!f) return;

    tipovertice *VECTOR; // Para almacenar el vector de vértices del grafo
    int N; // Número de vértices del grafo

    // Para recorrerla, simplemente vamos a recorrer la matriz de adyacencia
    N = num_vertices(G);
    VECTOR = array_vertices(G);

    int i, j, valorI, valorT;

    // Primero se recorren todos los vértices para imprimirlos de primero
    for (i = 0; i < N; i++) {
        fprintf(f, "%s\n", VECTOR[i].habitacion);
    }

    // Al acabar, se imprime un asterisco a modo de separador entre vértices y arcos
    fprintf(f, "*\n");

    // Se realiza el mismo bucle, pero se recorren todos los arcos ahora
    for (i = 0; i < N; i++) {
        // Como la matriz es simétrica, se puede comprobar un sólo triángulo,
        // ya que sino se escribirán los caminos por duplicado
        for (j = i; j < N; j++) {
            valorI = son_adyacentes_I(G, i, j);
            valorT = son_adyacentes_T(G, i, j);

            // Igual que en imprimir_mapa()
            if (valorI != 0) {
                if (valorT != 0) {
                    fprintf(f, "%s--%d-%s\n", VECTOR[i].habitacion, valorT, VECTOR[j].habitacion);
                }
                if (valorI != valorT) {
                    fprintf(f, "%s..%d-%s\n", VECTOR[i].habitacion, valorI, VECTOR[j].habitacion);
                }
            }
        }
    }

    // Se cierra el archivo
    fclose(f);
}

void _printMatrix(int **matrix, int V) {
    int i, j;
    for (i = 0; i < V; i++) {
        for (j = 0; j < V; j++) {
            if (matrix[i][j] == INFINITY)
                printf("%10s", "INF");
            else
                printf("%10d", matrix[i][j]);
        }
        printf("\n");
    }
}

char *_resolverHabitacion(grafo G, int v) {
    tipovertice *habitaciones = array_vertices(G);

    for (int i = 0; i < num_vertices(G); i++) {
        if (posicion(G, habitaciones[i]) == v) {
            return habitaciones[i].habitacion;
        }
    }

    return NULL;
}

void _imprimirCamino(grafo G, int **matrix, int origen, int destino, int anterior, char tipo, int *coste) {
    if (origen != destino) {
        _imprimirCamino(G, matrix, origen, matrix[origen][destino], destino, tipo, coste);
    }

    int ady, esImp = 0;
    if (tipo == 'I' || tipo == 'i') {
        ady = son_adyacentes_I(G, destino, anterior);
        if (ady != son_adyacentes_T(G, destino, anterior)) {
            esImp = 1;
        }
    } else {
        ady = son_adyacentes_T(G, destino, anterior);
    }

    *coste += ady;
    printf("%s%s", _resolverHabitacion(G, destino), destino != anterior ? (esImp ? " .. " : " -- ") : "");
}

int **_floyd(grafo G, char tipo) {
    int V = num_vertices(G);
    int i, j, k, ady;

    int **D = (int **) malloc(sizeof(int) * V * V);
    for (i = 0; i < V; i++) {
        D[i] = (int *) malloc(sizeof(int) * V);
    }
    int **P = (int **) malloc(sizeof(int) * V * V);
    for (i = 0; i < V; i++) {
        P[i] = (int *) malloc(sizeof(int) * V);
    }

    for (i = 0; i < V; i++) {
        for (j = 0; j < V; j++) {
            if (tipo == 'i' || tipo == 'I') {
                ady = son_adyacentes_I(G, i, j);
            } else {
                ady = son_adyacentes_T(G, i, j);
            }
            if (ady != 0 && i != j) {
                D[i][j] = ady;
                P[i][j] = i;
            } else if (i == j) {
                D[i][j] = 0;
                P[i][j] = 0;
            } else {
                D[i][j] = INFINITY;
                P[i][j] = 0;
            }
        }
    }

    for (k = 0; k < V; k++) {
        for (i = 0; i < V; i++) {
            for (j = 0; j < V; j++) {
                if (D[i][j] > D[i][k] + D[k][j]) {
                    D[i][j] = D[i][k] + D[k][j];
                    P[i][j] = P[k][j];
                }
            }
        }
    }

    return P;
}

void ruta_rapida(grafo G) {
    tipovertice v1, v2;
    char t[2];

    printf("Habitación de origen: ");
    scanf("%s", v1.habitacion);
    if (!existe_vertice(G, v1)) {
        printf("Esta habitación no existe en el mapa\n");
        return;
    }

    printf("Habitación de destino: ");
    scanf("%s", v2.habitacion);
    if (!existe_vertice(G, v2)) {
        printf("Esta habitación no existe en el mapa\n");
        return;
    }

    printf("Rol {T = Tripulante | I = Impostor}: ");
    scanf("%s", t);
    if (*t != 'I' && *t != 'i') {
        *t = 'C';
    }

    int coste = 0;
    _imprimirCamino(G, _floyd(G, *t), posicion(G, v1), posicion(G, v2), posicion(G, v2), *t, &coste);
    printf("\n");
    printf("Coste: %d\n", coste);
}

void _prim(grafo G, char tipo) {
    int N = num_vertices(G);
    int *s = (int *) malloc(sizeof(int) * N);
    memset(s, 0, N);
    int numArcos = 0, distanciaTotal = 0;
    s[0] = 1;

    int minimo, vx, vy, ady, esImp;
    int i, j;
    while (numArcos < (N - 1)) {
        minimo = INFINITY, vx = 0, vy = 0, ady = 0, esImp = 0;

        for (i = 0; i < N; i++) {
            if (s[i] == 1) {
                // printf("S=%d\n", i);
                for (j = 0; j < N; j++) {
                    if (tipo == 'I' || tipo == 'i') {
                        ady = son_adyacentes_I(G, i, j);
                        if (ady != son_adyacentes_T(G, i, j)) {
                            esImp = 1;
                        }
                    } else {
                        ady = son_adyacentes_T(G, i, j);
                    }
                    if (s[j] != 1 && ady > 0) {
                        if (minimo > ady) {
                            minimo = ady, vx = i, vy = j;
                        }
                    }
                }
            }
        }

        s[vy] = 1, numArcos++;
        printf("%15s %s %-15s : %d\n",
               _resolverHabitacion(G, vx), esImp ? ".." : "--", _resolverHabitacion(G, vy), minimo);
        distanciaTotal += minimo;
    }

    printf("Distancia Total del Árbol de Expansión de Coste Mínimo: %d\n", distanciaTotal);
}

void coste_minimo(grafo G) {
    char t[2];

    printf("Rol {T = Tripulante | I = Impostor}: ");
    scanf("%s", t);
    if (*t != 'I' && *t != 'i') {
        *t = 'C';
    }

    _prim(G, *t);
}
