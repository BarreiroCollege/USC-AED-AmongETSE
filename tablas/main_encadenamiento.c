#include <stdio.h>
#include <stdlib.h>

#include "tabla_hash_encadenamiento.h"

int main() {
    TablaHash tabla;
    InicializarTablaHash(tabla);

    tipo_jugador *jugadores = leerDatos();
    FILE *salida = fopen("encadenamiento.csv", "w");

    fprintf(salida, "Inserción,Colisiones\n");
    for (int i = 0; i < NUM_JUGADORES; i++) {
        fprintf(salida, "%d,%d\n", i, ColisionesProducidas(tabla, jugadores[i]));
        InsertarHash(&tabla, jugadores[i]);
    }
    fclose(salida);

    DestruirTablaHash(tabla);
    return EXIT_SUCCESS;
}
