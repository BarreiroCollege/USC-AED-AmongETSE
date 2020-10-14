#include <stdio.h>
#include <stdlib.h> //necesaria para rand()
#include <string.h> //para comparar cadenas
#include <math.h> //para calcular el número de impostores con round()

#include "abb.h"
#include "FuncionesAmongETSE.h"

//Función privada que genera un número aleatorio entre inf y sup
unsigned int _aleatorio(int inf, int sup) {
    return (rand() % (sup - inf + 1)) +inf;
}
//Función privada para inicializar los datos de un jugador, necesaria en varias funciones públicas
void _inicializarJugador(tipoelem * registro) { //inicializa los campos rol,descripcionTarea y lugarTarea
}
//Función privada que imprime los datos de un jugador
void _imprimirJugador(tipoelem E) {
}

//Función que añade un jugador al árbol
void altaJugador(abb *Arbol) {
}

//Función que elimina un jugador del árbol
void bajaJugador(abb *Arbol) {
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


//Función para leer el archivo de disco
void leerArchivo(abb *A) {
    tipoelem registro;
    FILE *fp;
    fp = fopen("ETSErsG3.txt", "rt");
    if (fp) {
        fscanf(fp, " %s", registro.nombreJugador);
        while (!feof(fp)) {
            _inicializarJugador(&registro);
            insertar(A, registro);
            fscanf(fp, " %s", registro.nombreJugador);
        }
        fclose(fp);
        listadoJugadores(*A);
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