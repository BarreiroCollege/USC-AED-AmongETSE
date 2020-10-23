#include <stdio.h>
#include <stdlib.h> // necesaria para rand()
#include <string.h> // para comparar cadenas
#include <math.h> // para calcular el número de impostores con round()

#include "abb.h"
#include "FuncionesAmongETSE.h"
#include "ConstantesAmongETSE.h"

// Función privada que genera un número aleatorio entre inf y sup
unsigned int _aleatorio(int inf, int sup) {
    return (rand() % (sup - inf + 1)) + inf;
}

// Función privada para inicializar los datos de un jugador, necesaria en varias funciones públicas
void _inicializarJugador(tipoelem *registro) { // inicializa los campos rol,descripcionTarea y lugarTarea
    registro->rol = ' ';
    strcpy(registro->tarea, "");
    strcpy(registro->tareaLugar, "");
}

void _limpiarDatos(abb jugadores) {
    tipoelem E;
    if (!es_vacio(jugadores)) {
        leer(jugadores, &E);
        _inicializarJugador(&E);

        _limpiarDatos(izq(jugadores));
        _limpiarDatos(der(jugadores));
    }
}

// Función privada que imprime los datos de un jugador
void _imprimirJugador(tipoelem E) {
    printf("| %-12s | %c | %-14s > %-27s |\n", E.nombreJugador, E.rol, E.tareaLugar, E.tarea);
}

// Función que añade un jugador al árbol
void altaJugador(abb *jugadores) {
    tipoelem nuevo;
    printf("Nombre de usuario (tiene que empezar por @):\n");
    printf("> ");
    scanf(" %s", nuevo.nombreJugador);

    if (nuevo.nombreJugador[0] != '@') {
        printf("Los nombres de jugador han de empezar por @\n");
        return;
    }

    if (es_miembro(*jugadores, nuevo)) {
        printf("El jugador %s ya está dado de alta!\n", nuevo.nombreJugador);
    } else {
        _inicializarJugador(&nuevo);
        insertar(jugadores, nuevo);
        printf("%s dado de alta\n", nuevo.nombreJugador);
    }
}

//Función que elimina un jugador del árbol
void bajaJugador(abb *jugadores) {
    tipoelem viejo;
    printf("Nombre de usuario (tiene que empezar por @):\n");
    printf("> ");
    scanf(" %s", viejo.nombreJugador);
    if (viejo.nombreJugador[0] != '@') {
        printf("Los nombres de jugador han de empezar por @\n");
        return;
    }

    if (!es_miembro(*jugadores, viejo)) {
        printf("El jugador %s no está en el juego!\n", viejo.nombreJugador);
    } else {
        suprimir(jugadores, viejo);
        printf("%s dado de baja\n", viejo.nombreJugador);
    }
}

/* Recorrido inorden del árbol binario */
void _inorden(abb A) {
    tipoelem E;
    if (!es_vacio(A)) {
        _inorden(izq(A));
        leer(A, &E);
        _imprimirJugador(E);
        _inorden(der(A));
    }
}

//Función pública que imprime los nombres de los jugadores por orden alfabético
void listadoJugadores(abb jugadores) {
    _inorden(jugadores);
}

void _asignarTarea(tipoelem *registro) {
    switch (_aleatorio(1, 8)) {
        case 1:
            strcpy(registro->tarea, TAREA_MOTOR);
            strcpy(registro->tareaLugar, SALA_MOTORES);
            break;
        case 2:
            strcpy(registro->tarea, TAREA_DISTRIBUIDOR);
            strcpy(registro->tareaLugar, SALA_ELECTRICIDAD);
            break;
        case 3:
            strcpy(registro->tarea, TAREA_DATOS);
            switch (_aleatorio(1, 5)) {
                case 1:
                    strcpy(registro->tareaLugar, SALA_CAFETERIA);
                    break;
                case 2:
                    strcpy(registro->tareaLugar, SALA_COMUNICACIONES);
                    break;
                case 3:
                    strcpy(registro->tareaLugar, SALA_ARMERIA);
                    break;
                case 4:
                    strcpy(registro->tareaLugar, SALA_ELECTRICIDAD);
                    break;
                case 5:
                    strcpy(registro->tareaLugar, SALA_NAVEGACION);
                    break;
            }
            break;
        case 4:
            strcpy(registro->tarea, TAREA_ENERGIA);
            switch (_aleatorio(1, 7)) {
                case 1:
                    strcpy(registro->tareaLugar, SALA_NAVEGACION);
                    break;
                case 2:
                    strcpy(registro->tareaLugar, SALA_O2);
                    break;
                case 3:
                    strcpy(registro->tareaLugar, SALA_SEGURIDAD);
                    break;
                case 4:
                    strcpy(registro->tareaLugar, SALA_ARMERIA);
                    break;
                case 5:
                    strcpy(registro->tareaLugar, SALA_COMUNICACIONES);
                    break;
                case 6:
                    strcpy(registro->tareaLugar, SALA_ESCUDOS);
                    break;
                case 7:
                    strcpy(registro->tareaLugar, SALA_MOTORES);
                    break;
            }
            break;
        case 5:
            strcpy(registro->tarea, TAREA_ESCUDOS);
            strcpy(registro->tareaLugar, SALA_ESCUDOS);
            break;
        case 6:
            strcpy(registro->tarea, TAREA_DIRECCION);
            strcpy(registro->tareaLugar, SALA_NAVEGACION);
            break;
        case 7:
            strcpy(registro->tarea, TAREA_FILTRO);
            strcpy(registro->tareaLugar, SALA_O2);
            break;
        case 8:
            strcpy(registro->tarea, TAREA_MAPA);
            strcpy(registro->tareaLugar, SALA_NAVEGACION);
            break;
    }
}

//Función que genera los datos de una partida: jugadores, roles y tareas
void generarPartida(abb *jugadores) {
    char *nJugadores = (char *) malloc(sizeof(char) * 2);
    char modoJuego;

    _limpiarDatos(*jugadores);

    printf("Número de jugadores (4-10):\n");
    printf("> ");
    scanf(" %s", nJugadores);

    int numJugadores = atoi(nJugadores);
    if (numJugadores < 4 || numJugadores > 10) {
        printf("El número de jugadores ha de estar comprendido entre 4 y 10\n");
        return;
    }

    printf("Selección de jugadores (A = Aleatorio | M = Manual)\n");
    printf("> ");
    scanf(" %s", &modoJuego);

    int nImpostores = (int) round(numJugadores / 5.0);
    int *impostores = (int *) malloc(sizeof(int) * nImpostores);
    for (int i = 0; i < nImpostores; i++) {
        int pos = (int) _aleatorio(0, numJugadores - 1);
        if (i == 1) {
            while (pos == *impostores) {
                pos = (int) _aleatorio(0, numJugadores - 1);
            }
        }
        *(impostores + i) = pos;
    }

    tipoelem jugadorAux;
    int jugadoresAnadidos = 0;
    switch (modoJuego) {
        case 'M':
        case 'm':
            while (jugadoresAnadidos < numJugadores) {
                printf("Jugador a añadir a la partida(tiene que empezar por @):\n");
                printf("> ");
                scanf(" %s", jugadorAux.nombreJugador);

                if (*jugadorAux.nombreJugador != '@') {
                    printf("El nombre de jugador tiene que empezar por @\n\n");
                } if (!es_miembro(*jugadores, jugadorAux)) {
                    printf("El jugador %s no existe\n\n", jugadorAux.nombreJugador);
                } else {
                    buscar_nodo(*jugadores, jugadorAux.nombreJugador, &jugadorAux);
                    if (jugadorAux.rol != ' ') {
                        printf("El jugador %s ya está en la partida\n\n", jugadorAux.nombreJugador);
                    } else {
                        if (*impostores == jugadoresAnadidos ||
                            (nImpostores == 2 && *(impostores + 1) == jugadoresAnadidos)) {
                            jugadorAux.rol = 'I';
                        } else {
                            jugadorAux.rol = 'C';
                        }
                        _asignarTarea(&jugadorAux);
                        suprimir(jugadores, jugadorAux);
                        insertar(jugadores, jugadorAux);
                        printf("%s añadido a la partida\n\n", jugadorAux.nombreJugador);
                        jugadoresAnadidos++;
                    }
                }
            }
            break;

        default:
            printf("Modo de juego no reconocido, usando automático...\n");
        case 'A':
        case 'a':
            for (int i = 0; i < numJugadores; i++) {
                int r = 0;
                abb aux;
                crear(&aux);
                aux = *jugadores;
                tipoelem nodo;
                while (r != 2) {
                    r = (int) _aleatorio(1, 3);
                    if (r == 1) {
                        aux = izq(aux);
                    } else if (r == 3) {
                        aux = der(aux);
                    } else if (r == 2) {
                        leer(aux, &nodo);
                        buscar_nodo(*jugadores, nodo.nombreJugador, &jugadorAux);
                        if (jugadorAux.rol != ' ') {
                            r = 0;
                            aux = *jugadores;
                        }
                    }

                    if (es_vacio(aux)) {
                        aux = *jugadores;
                    }
                }
                if (*impostores == i || (nImpostores == 2 && *(impostores + 1) == i)) {
                    jugadorAux.rol = 'I';
                } else {
                    jugadorAux.rol = 'C';
                }
                _asignarTarea(&jugadorAux);
                suprimir(jugadores, jugadorAux);
                insertar(jugadores, jugadorAux);
            }
            break;
    }
    printf("Partida creada\n");
}

//Función que imprime los datos de un usuario cuyo nombre se introduce por teclado
void consultarJugador(abb jugadores) {
    tipoelem j;
    printf("Nombre de usuario (tiene que empezar por @):\n");
    printf("> ");
    scanf(" %s", j.nombreJugador);

    if (j.nombreJugador[0] != '@') {
        printf("Los nombres de jugador han de empezar por @\n");
        return;
    }

    if (!es_miembro(jugadores, j)) {
        printf("El jugador %s no existe en la partida!\n", j.nombreJugador);
    } else {
        buscar_nodo(jugadores, j.nombreJugador, &j);
        _imprimirJugador(j);
    }
}

void _buscarHabitacion(abb jugadores, abb* habitaciones, char* habitacion) {
    tipoelem E;
    if (!es_vacio(jugadores)) {
        leer(jugadores, &E);
        if (strcmp(E.tareaLugar, habitacion) == 0) {
            insertar(habitaciones, E);
        }

        _buscarHabitacion(izq(jugadores), habitaciones, habitacion);
        _buscarHabitacion(der(jugadores), habitaciones, habitacion);
    }
}

//Función que imprime todos los usuarios que están en una habitación determinada
void consultarPorHabitacion(abb jugadores) {
    char *h = (char *) malloc(sizeof(int));
    printf("Escoge una habitación:\n");
    printf("  1. %s\n", SALA_MOTORES);
    printf("  2. %s\n", SALA_ELECTRICIDAD);
    printf("  3. %s\n", SALA_CAFETERIA);
    printf("  4. %s\n", SALA_COMUNICACIONES);
    printf("  5. %s\n", SALA_ARMERIA);
    printf("  6. %s\n", SALA_NAVEGACION);
    printf("  7. %s\n", SALA_O2);
    printf("  8. %s\n", SALA_SEGURIDAD);
    printf("  9. %s\n", SALA_ESCUDOS);
    printf("> ");
    scanf(" %s", h);

    int habitacion = atoi(h);
    if (habitacion < 1 || habitacion > 9) {
        printf("El código introducido no es una habitación válida.\n");
        return;
    }
    printf("\n");

    char lugar[L];
    abb habitaciones;
    crear(&habitaciones);
    switch (habitacion) {
        case 1:
            strcpy(lugar, SALA_MOTORES);
            break;
        case 2:
            strcpy(lugar, SALA_ELECTRICIDAD);
            break;
        case 3:
            strcpy(lugar, SALA_CAFETERIA);
            break;
        case 4:
            strcpy(lugar, SALA_COMUNICACIONES);
            break;
        case 5:
            strcpy(lugar, SALA_ARMERIA);
            break;
        case 6:
            strcpy(lugar, SALA_NAVEGACION);
            break;
        case 7:
            strcpy(lugar, SALA_O2);
            break;
        case 8:
            strcpy(lugar, SALA_SEGURIDAD);
            break;
        case 9:
            strcpy(lugar, SALA_ESCUDOS);
            break;
        default:
            break;
    }

    _buscarHabitacion(jugadores, &habitaciones, lugar);
    printf("Jugadores en %s:\n", lugar);
    listadoJugadores(habitaciones);
}


// Función para leer el archivo de disco
void leerArchivo(abb *A) {
    tipoelem registro;
    FILE *fp;
    fp = fopen("ETSErsG1.txt", "rt");
    if (fp) {
        fscanf(fp, " %s", registro.nombreJugador);
        while (!feof(fp)) {
            _inicializarJugador(&registro);
            insertar(A, registro);
            fscanf(fp, " %s", registro.nombreJugador);
        }
        fclose(fp);
    }
}
