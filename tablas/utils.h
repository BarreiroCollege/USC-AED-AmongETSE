#ifndef TABLAS_UTILS_H
#define TABLAS_UTILS_H

#define NUM_JUGADORES 10000

typedef struct {
    char nombre[15];
    char apellido1[15];
    char apellido2[15];
    char clave[20];
    char correo[60];
} tipo_jugador;

// https://stackoverflow.com/questions/656542/trim-a-string-in-c
char *trim(char *s);

tipo_jugador * leerDatos();

#endif //TABLAS_UTILS_H
