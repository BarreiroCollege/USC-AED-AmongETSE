#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "tabla_hash_encadenamiento.h"

int main() {
    TablaHash tabla;
    InicializarTablaHash(tabla);

    tipo_jugador *jugadores = leerDatos();
    // FILE *salida = fopen("encadenamiento.csv", "w");

    // fprintf(salida, "Insercion,NumElementos\n");
    int colisiones = 0;
    for (int i = 0; i < NUM_JUGADORES; i++) {
        // fprintf(salida, "%d,%d\n", i, NumElementos(tabla, jugadores[i]));
        colisiones += ColisionesProducidas(tabla, jugadores[i]);
        InsertarHash(&tabla, jugadores[i]);
    }
    printf("Colisiones=%d\n", colisiones);
    // fclose(salida);

    clock_t inicio, fin;
    double tiempoconsumido;

    inicio=clock();
    tipo_jugador tmp;
    for (int i = 0; i < NUM_JUGADORES; i++) {
        Busqueda(tabla, jugadores[i].clave, &tmp);
    }
    fin=clock();

    tiempoconsumido=((double)(fin-inicio))/CLOCKS_PER_SEC;
    printf("%d,%d", Tam, HashF);
    if (HashF == 3) {
        printf(",%d", K);
    } else {
        printf(",-1");
    }
    printf(",%lf\n", tiempoconsumido);

    DestruirTablaHash(tabla);
    return EXIT_SUCCESS;
}
