#include <ctype.h>
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

char *ltrim(char *s) {
    while (isspace(*s)) s++;
    return s;
}

char *rtrim(char *s) {
    char *back = s + strlen(s);
    while (isspace(*--back));
    *(back + 1) = '\0';
    return s;
}

char *trim(char *s) {
    return rtrim(ltrim(s));
}

tipo_jugador *leerDatos() {
    FILE *f;
    f = fopen("jugadores_amongETSE.txt", "r");
    if (!f) return NULL;

    tipo_jugador *jugadores = (tipo_jugador *) malloc(sizeof(tipo_jugador) * NUM_JUGADORES);
    int numJugador = 0;

    char nombreCompleto[45];
    char clave[20];
    char correo[60];

    char linea[125];
    fscanf(f, " %[^\n]", linea);
    while (!feof(f)) {
        tipo_jugador jugador;
        sscanf(linea, "%[^-] - %[^-] - %s", nombreCompleto, clave, correo);

        int c, posTexto = 0;
        int leyendoNombre = 1, leyendoApellido1 = 0, leyendoApellido2 = 0;
        char *nuevoNombre = trim(nombreCompleto);
        for (c = 0; nuevoNombre[c] != '\0'; c++) {
            if (leyendoNombre) {
                if (nuevoNombre[c] == ' ') {
                    jugador.nombre[posTexto] = '\0';
                    posTexto = 0;
                    leyendoNombre = 0, leyendoApellido1 = 1;
                } else {
                    jugador.nombre[posTexto] = nuevoNombre[c];
                    posTexto++;
                }
            } else if (leyendoApellido1) {
                if (nuevoNombre[c] == ' ') {
                    jugador.apellido1[posTexto] = '\0';
                    posTexto = 0;
                    leyendoApellido1 = 0, leyendoApellido2 = 1;
                } else {
                    jugador.apellido1[posTexto] = nuevoNombre[c];
                    posTexto++;
                }
            } else if (leyendoApellido2) {
                jugador.apellido2[posTexto] = nuevoNombre[c];
                posTexto++;
            }
        }
        jugador.apellido2[c + 1] = '\0';

        strcpy(jugador.clave, trim(clave));
        strcpy(jugador.correo, trim(correo));

        jugadores[numJugador] = jugador;
        fscanf(f, " %[^\n]", linea);
        numJugador++;
    }

    // Cerramos archivo
    fclose(f);

    return jugadores;
}