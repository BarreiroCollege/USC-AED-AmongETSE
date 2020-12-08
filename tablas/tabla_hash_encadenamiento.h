/* 
 * Tabla hash con encadenamiento
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"
#include "vars.h"

typedef lista TablaHash[Tam];

void InicializarTablaHash(TablaHash t);

void DestruirTablaHash(TablaHash t);

int Hash(char *cad);

int Busqueda(TablaHash t, char *clavebuscar, tipoelem *e);

int NumElementos(TablaHash t, tipoelem elemento);

int ColisionesProducidas(TablaHash t, tipoelem elemento);

int PasosAdicionalesInsercion(TablaHash t, tipoelem elemento);

int PasosAdicionalesBusqueda(TablaHash t, tipoelem elemento);

int MiembroHash(TablaHash t, char *clavebuscar);

void InsertarHash(TablaHash *t, tipoelem elemento);

void BorrarHash(TablaHash *t, char *claveborrar);

