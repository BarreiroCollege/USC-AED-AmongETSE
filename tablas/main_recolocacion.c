#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "tablas_hash_recolocacion.h"

int main() {
    TablaHash tabla;
    InicializarTablaHash(tabla);

    tipo_jugador *jugadores = leerDatos();
    // FILE *salida = fopen("recolocacion.csv", "w");

    // fprintf(salida, "Inserción,Colisiones\n");
    for (int i = 0; i < NUM_JUGADORES; i++) {
        // fprintf(salida, "%d,%d\n", i, ColisionesProducidas(tabla, jugadores[i]));
        InsertarHash(tabla, jugadores[i]);
    }
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
    printf("%d,", Tam);
    // printf("%d,", a);
    printf("%d", HashF);
    if (HashF == 3) {
        printf(",%d", K);
    } else {
        printf(",-1");
    }
    printf(",%lf\n", tiempoconsumido);

    return EXIT_SUCCESS;
}
