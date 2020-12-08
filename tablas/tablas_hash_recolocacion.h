/*
 * File:   tablas_hash_recolocacion.h
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"
#include "vars.h"

/*DEFINIR NUMERO de entradas en la tabla.*/
#define VACIO '\0'
#define BORRADO ' '

typedef tipo_jugador TablaHash[Tam];

void InicializarTablaHash(TablaHash t);

int Hash(char *cad);

int MiembroHash(TablaHash t, char *cad);

int NumElementos(TablaHash t, tipo_jugador e);

int ColisionesProducidas(TablaHash t, tipo_jugador e);

int PasosAdicionalesInsercion(TablaHash t, tipo_jugador elemento);

int PasosAdicionalesBusqueda(TablaHash t, tipo_jugador elemento);

int Busqueda(TablaHash t, char *cad, tipo_jugador *e);

void InsertarHash(TablaHash t, tipo_jugador e);

void BorrarHash(TablaHash t, char *cad);
