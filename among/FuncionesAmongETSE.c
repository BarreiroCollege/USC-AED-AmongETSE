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
    // Se utiliza el caracter de espacio para indicar un rol sin asignar
    registro->rol = ' ';
    // Cadenas de texto vacías para las tareas
    crear_cola(&registro->tareas);
}

void _limpiarDatos(abb jugadores) {
    tipoelem E;
    if (!es_vacio(jugadores)) {
        leer(jugadores, &E);
        _inicializarJugador(&E);
        modificar(jugadores, E);

        _limpiarDatos(izq(jugadores));
        _limpiarDatos(der(jugadores));
    }
}

// Función privada que imprime una tarea
void _imprimirTarea(tipoelemCola tarea) {
    printf("| %-12s | %c || %-27s > %-14s |\n", "", ' ', tarea.tarea, tarea.tareaLugar);
}

// Función privada que imprime las tareas de un jugador
void _imprimirTareas(cola *tareas) {
    cola aux;
    crear_cola(&aux);

    tipoelemCola tarea;
    for (int i = 1; !es_vacia_cola(*tareas); i++) {
        tarea = primero(*tareas);
        suprimir_cola(tareas);
        _imprimirTarea(tarea);
        insertar_cola(&aux, tarea);
    }
    for (int i = 1; !es_vacia_cola(aux); i++) {
        tarea = primero(aux);
        suprimir_cola(&aux);
        insertar_cola(tareas, tarea);
    }
}

// Función privada que imprime los datos de un jugador
void _imprimirJugador(tipoelem E) {
    // Se formatean los datos del jugador
    printf("| %-12s | %c || %-14s   %-27s |\n", E.nombreJugador, E.rol, "", "");
}

// Función que añade un jugador al árbol
void altaJugador(abb *jugadores) {
    tipoelem nuevo;
    printf("Nombre de usuario (tiene que empezar por @):\n");
    printf("> ");
    scanf(" %s", nuevo.nombreJugador);

    // Si el nombre no comienza por arroba, rechazar
    if (nuevo.nombreJugador[0] != '@') {
        printf("Los nombres de jugador han de empezar por @\n");
        return;
    }

    if (es_miembro(*jugadores, nuevo)) {
        printf("El jugador %s ya está dado de alta!\n", nuevo.nombreJugador);
    } else {
        // Si el jugador no está en la partida, se inicializa y se inserta en el árbol
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

    // Si el nombre no comienza por arroba, rechazar
    if (viejo.nombreJugador[0] != '@') {
        printf("Los nombres de jugador han de empezar por @\n");
        return;
    }

    if (!es_miembro(*jugadores, viejo)) {
        printf("El jugador %s no está en el juego!\n", viejo.nombreJugador);
    } else {
        // Si el jugador está en la partida, se elimina del árbol
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
        _imprimirTareas(&E.tareas);
        _inorden(der(A));
    }
}

//Función pública que imprime los nombres de los jugadores por orden alfabético
void listadoJugadores(abb jugadores) {
    // El listado de jugadores se realiza mediante un recorrido inorden
    _inorden(jugadores);
}

void _asignarTarea(tipoelem *registro) {
    // Se genera un número aleatorio entr 1 y 8 para escoger la tarea
    tipoelemCola tarea;
    switch (_aleatorio(1, 8)) {
        case 1:
            strcpy(tarea.tarea, TAREA_MOTOR);
            strcpy(tarea.tareaLugar, SALA_MOTORES);
            break;
        case 2:
            strcpy(tarea.tarea, TAREA_DISTRIBUIDOR);
            strcpy(tarea.tareaLugar, SALA_ELECTRICIDAD);
            break;
        case 3:
            strcpy(tarea.tarea, TAREA_DATOS);
            // En caso de datos, hay 5 posibles localizaciones
            switch (_aleatorio(1, 5)) {
                case 1:
                    strcpy(tarea.tareaLugar, SALA_CAFETERIA);
                    break;
                case 2:
                    strcpy(tarea.tareaLugar, SALA_COMUNICACIONES);
                    break;
                case 3:
                    strcpy(tarea.tareaLugar, SALA_ARMERIA);
                    break;
                case 4:
                    strcpy(tarea.tareaLugar, SALA_ELECTRICIDAD);
                    break;
                case 5:
                    strcpy(tarea.tareaLugar, SALA_NAVEGACION);
                    break;
            }
            break;
        case 4:
            strcpy(tarea.tarea, TAREA_ENERGIA);
            // En caso de energía, hay 5 posibles localizaciones
            switch (_aleatorio(1, 7)) {
                case 1:
                    strcpy(tarea.tareaLugar, SALA_NAVEGACION);
                    break;
                case 2:
                    strcpy(tarea.tareaLugar, SALA_O2);
                    break;
                case 3:
                    strcpy(tarea.tareaLugar, SALA_SEGURIDAD);
                    break;
                case 4:
                    strcpy(tarea.tareaLugar, SALA_ARMERIA);
                    break;
                case 5:
                    strcpy(tarea.tareaLugar, SALA_COMUNICACIONES);
                    break;
                case 6:
                    strcpy(tarea.tareaLugar, SALA_ESCUDOS);
                    break;
                case 7:
                    strcpy(tarea.tareaLugar, SALA_MOTORES);
                    break;
            }
            break;
        case 5:
            strcpy(tarea.tarea, TAREA_ESCUDOS);
            strcpy(tarea.tareaLugar, SALA_ESCUDOS);
            break;
        case 6:
            strcpy(tarea.tarea, TAREA_DIRECCION);
            strcpy(tarea.tareaLugar, SALA_NAVEGACION);
            break;
        case 7:
            strcpy(tarea.tarea, TAREA_FILTRO);
            strcpy(tarea.tareaLugar, SALA_O2);
            break;
        case 8:
            strcpy(tarea.tarea, TAREA_MAPA);
            strcpy(tarea.tareaLugar, SALA_NAVEGACION);
            break;
    }

    insertar_cola(&registro->tareas, tarea);
}

// Función privada para copiar los datos de los jugadores en partida
void _copiarPartida(abb *jugadores, abb partida) {
    tipoelem E;
    if (!es_vacio(partida)) {
        leer(partida, &E);
        // Asignar tarea a jugador
        for (int i = 0; i < 5; i++) {
            _asignarTarea(&E);
        }
        modificar(*jugadores, E);
        _copiarPartida(jugadores, izq(partida));
        _copiarPartida(jugadores, der(partida));
    }
}

// Función que genera los datos de una partida: jugadores, roles y tareas
void generarPartida(abb *jugadores) {
    abb partida;
    crear(&partida);

    // nJugadores = char que se obtiene de preguntar el número de jugadores
    char *nJugadores = (char *) malloc(sizeof(char) * 2);
    // Modo de juego que el usuario desea, siendo M manual y A automático
    char modoJuego;

    // Se limpian los datos antes de cada generación
    _limpiarDatos(*jugadores);

    printf("Número de jugadores (4-10):\n");
    printf("> ");
    scanf(" %s", nJugadores);

    // numJugadores = número de jugadores que se quiere meter en la partida
    int numJugadores = atoi(nJugadores);
    // Se comprueba que el número de jugadores está comprendido entre 4 y 10
    if (numJugadores < 4 || numJugadores > 10) {
        printf("El número de jugadores ha de estar comprendido entre 4 y 10\n");
        return;
    }

    // Se pregunta el modo de selección de jugadores
    printf("Selección de jugadores (A = Aleatorio | M = Manual)\n");
    printf("> ");
    scanf(" %s", &modoJuego);

    // nImposores = número de impostores que tendrá la partida
    int nImpostores = (int) round(numJugadores / 5.0);
    // impostores = lista de ints, siendo cada int la posición del
    //              jugador que va a ser impostor, siendo entre 0 y 10
    int *impostores = (int *) malloc(sizeof(int) * nImpostores);
    for (int i = 0; i < nImpostores; i++) {
        // Primero se genera un número aleatorio entre 0 y el número de jugadores
        // para saber quien va a ser el primer impostor
        int pos = (int) _aleatorio(0, numJugadores - 1);
        if (i == 1) {
            // Como hay de máximo dos impostores, en el segundo impostor
            // hay que asegurarse de que no coincida con el primero
            while (pos == *impostores) {
                pos = (int) _aleatorio(0, numJugadores - 1);
            }
        }
        // Se guarda esta posición
        *(impostores + i) = pos;
    }

    tipoelem jugadorAux;
    // En el caso de Manual, esta variable va a tener el número de jugadores que tenemos hasta el momento
    int jugadoresAnadidos = 0;
    switch (modoJuego) {
        case 'M':
        case 'm':
            // Mientras no hemos añadido suficientes jugadores
            while (jugadoresAnadidos < numJugadores) {
                // Se pregunta por usuarios
                printf("Jugador a añadir a la partida(tiene que empezar por @):\n");
                printf("> ");
                scanf(" %s", jugadorAux.nombreJugador);

                // Si el jugador no empieza por arroba, se rechaza, igual que si no es miembro
                if (*jugadorAux.nombreJugador != '@') {
                    printf("El nombre de jugador tiene que empezar por @\n\n");
                } else if (!es_miembro(*jugadores, jugadorAux)) {
                    printf("El jugador %s no existe\n\n", jugadorAux.nombreJugador);
                } else if (es_miembro(partida, jugadorAux)) {
                    // Y en caso de ya tener un rol, quiere decir que ya se metió en la partida
                    printf("El jugador %s ya está en la partida\n\n", jugadorAux.nombreJugador);
                } else {
                    // Se busca el nodo de jugadores que coincide con el nombre introducido
                    buscar_nodo(*jugadores, jugadorAux.nombreJugador, &jugadorAux);
                    // Si el índice del jugador coincide con algún índice de impostor, se le asigna
                    // el rol de impostor, sino el de tripulante (crewmate)
                    if (*impostores == jugadoresAnadidos ||
                        (nImpostores == 2 && *(impostores + 1) == jugadoresAnadidos)) {
                        jugadorAux.rol = 'I';
                    } else {
                        jugadorAux.rol = 'C';
                    }
                    // Se inserta en el árbol de la partida
                    insertar(&partida, jugadorAux);
                    printf("%s añadido a la partida\n\n", jugadorAux.nombreJugador);
                    jugadoresAnadidos++;
                }
            }
            break;

        default:
            // Por defecto se usa el modo aleatorio
            printf("Modo de juego no reconocido, usando automático...\n");
        case 'A':
        case 'a':
            // Se hace un for loop para el máximo de jugadores
            for (int i = 0; i < numJugadores; i++) {
                // Esta variable r es una variable comodín para recorrer el árbol de forma totalmente
                // aleatoria. Se explica más abajo los posibles valores.
                int r = 0;
                // Arbol auxiliar para recorrer los jugadores
                abb aux;
                crear(&aux);
                aux = *jugadores;
                tipoelem nodo;
                // Si r=2, entonces es que la raiz actual del arbol auxiliar es apta para ser seleccionada
                while (r != 2) {
                    // Se genera un valor aleatorio posible de 1, 2 o 3
                    r = (int) _aleatorio(1, 3);
                    // Si es r=1, se mueve a la izquierda
                    if (r == 1) {
                        aux = izq(aux);
                        // Si es r=3, se mueve a la derecha
                    } else if (r == 3) {
                        aux = der(aux);
                        // Si es r=2, se queda en el nodo y lo lee
                    } else if (r == 2) {
                        leer(aux, &nodo);
                        // En el caso de ya tener un rol asignado, se pone r=0 y se vuelve a empezar
                        if (es_miembro(partida, nodo)) {
                            r = 0;
                            aux = *jugadores;
                        } else {
                            buscar_nodo(*jugadores, nodo.nombreJugador, &jugadorAux);
                        }
                    }

                    // Y si el arbol auxiliar está vació, se vuelve a la cima de jugadores
                    // y se repite el proceso
                    if (es_vacio(aux)) {
                        aux = *jugadores;
                    }
                }

                // Se comprueba si el índice del jugador es alguno de los impostores
                if (*impostores == i || (nImpostores == 2 && *(impostores + 1) == i)) {
                    jugadorAux.rol = 'I';
                } else {
                    jugadorAux.rol = 'C';
                }
                // Se inserta en el árbol de la partida
                insertar(&partida, jugadorAux);
            }
            break;
    }

    // Se copian los datos de partida a los jugadores de main
    _copiarPartida(jugadores, partida);
    printf("Partida creada\n");
}

// Función que imprime los datos de un usuario cuyo nombre se introduce por teclado
void consultarJugador(abb jugadores) {
    // Se pregunta al usuario por el nombre del jugador
    tipoelem j;
    printf("Nombre de usuario (tiene que empezar por @):\n");
    printf("> ");
    scanf(" %s", j.nombreJugador);

    // Se rechaza si no empieza por arroba
    if (j.nombreJugador[0] != '@') {
        printf("Los nombres de jugador han de empezar por @\n");
        return;
    }

    // Si no es miembro no se hace nada, pero si existe se busca el nodo y se imprime
    if (!es_miembro(jugadores, j)) {
        printf("El jugador %s no existe en la partida!\n", j.nombreJugador);
    } else {
        buscar_nodo(jugadores, j.nombreJugador, &j);
        _imprimirJugador(j);
        if (!es_vacia_cola(j.tareas)) {
            _imprimirTarea(primero(j.tareas));
        } else {
            printf("| %-12s | %c || %-44s |\n", "", ' ', "No hay tarea asignada");
        }
    }
}

// Función privada recursiva que imprime los jugadores en la misma habitación
void _buscarHabitacion(abb jugadores, abb *habitaciones, char *habitacion) {
    tipoelem E;
    // Si los jugadores no están vacíos, se lee el elemento
    if (!es_vacio(jugadores)) {
        leer(jugadores, &E);
        if (!es_vacia_cola(E.tareas)) {
            // Y si la habitación es la misma a la deseada, se mete en el árbol de habitaciones
            tipoelemCola tarea = primero(E.tareas);
            if (strcmp(tarea.tareaLugar, habitacion) == 0) {
                insertar(habitaciones, E);
            }
        }

        // Se repite el mismo proceso con los posibles hijos
        _buscarHabitacion(izq(jugadores), habitaciones, habitacion);
        _buscarHabitacion(der(jugadores), habitaciones, habitacion);
    }
}

//Función que imprime todos los usuarios que están en una habitación determinada
void consultarPorHabitacion(abb jugadores) {
    // Se pregunta la habitación que se desea
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

    // Se comprueba que el número de habitación sea correcto
    int habitacion = atoi(h);
    if (habitacion < 1 || habitacion > 9) {
        printf("El código introducido no es una habitación válida.\n");
        return;
    }
    printf("\n");

    char lugar[L * 2];
    // Se crea un árbol auxiliar con el que poder detectar la habitación
    abb habitaciones;
    crear(&habitaciones);
    // Se copia la habitación a la variable a mandar a la función recursiva
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

    // Se busca pro habitación
    _buscarHabitacion(jugadores, &habitaciones, lugar);
    printf("Jugadores en %s:\n", lugar);
    // Y se imprime los jugadores en la habitación
    listadoJugadores(habitaciones);
    // No se puede destruir el árbol, ya que sus hijos son los jugadores
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

// Función privada para insertar una línea en el archivo
void _insertarLinea(abb jugadores) {
    tipoelem jugador;
    if (!es_vacio(jugadores)) {
        _insertarLinea(izq(jugadores));
        leer(jugadores, &jugador);
        FILE *fp;
        fp = fopen("ETSErsG1.txt", "a+");
        fprintf(fp, "%s\n", jugador.nombreJugador);
        fclose(fp);
        _insertarLinea(der(jugadores));
    }
}

// Función para guardar el archivo en el disco
void guardarArchivo(abb jugadores) {
    // Vacía el archivo
    FILE *fp;
    fp = fopen("ETSErsG1.txt", "w");
    fclose(fp);
    // Leer mediante recorrido inorden
    _insertarLinea(jugadores);
}
