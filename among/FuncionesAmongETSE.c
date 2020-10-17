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
    registro->rol = '\0';
    strcpy(registro->tarea, "\0");
    strcpy(registro->tareaLugar, "\0");
}

// Función privada que imprime los datos de un jugador
void _imprimirJugador(tipoelem E) {
}

// Función que añade un jugador al árbol
void altaJugador(abb *jugadores, char *jugador) {
    if (jugador[0] != '@') {
        printf("Los nombres de jugador han de empezar por @\n");
        return;
    }

    tipoelem nuevo;
    strcpy(nuevo.nombreJugador, jugador);
    if (es_miembro(*jugadores, nuevo)) {
        printf("El jugador %s ya está dado de alta!\n", nuevo.nombreJugador);
    } else {
        _inicializarJugador(&nuevo);
        insertar(jugadores, nuevo);
        printf("%s dado de alta\n", nuevo.nombreJugador);
    }
}

//Función que elimina un jugador del árbol
void bajaJugador(abb *jugadores, char* jugador) {
    if (jugador[0] != '@') {
        printf("Los nombres de jugador han de empezar por @\n");
        return;
    }

    tipoelem viejo;
    strcpy(viejo.nombreJugador, jugador);
    if (!es_miembro(*jugadores, viejo)) {
        printf("El jugador %s no está en el juego!\n", viejo.nombreJugador);
    } else {
        suprimir(jugadores, viejo);
        printf("%s dado de baja\n", viejo.nombreJugador);
    }
}

//Función pública que imprime los nombres de los jugadores por orden alfabético
void listadoJugadores(abb A) {
    inorden(A);
}

//Función que genera los datos de una partida: jugadores, roles y tareas
void generarPartida(abb *Arbol) {
}

//Función que imprime los datos de un usuario cuyo nombre se introduce por teclado
void consultarJugador(abb Arbol) {
}

//Función que imprime todos los usuarios que están en una habitación determinada
void consultarPorHabitacion(abb Arbol) {
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


/* Recorrido inorden del árbol binario */
void inorden(abb A) {
    tipoelem E;
    if (!es_vacio(A)) {
        inorden(izq(A));
        leer(A, &E);
        printf("%s\n", E.nombreJugador);
        inorden(der(A));
    }
}

/*
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
 */