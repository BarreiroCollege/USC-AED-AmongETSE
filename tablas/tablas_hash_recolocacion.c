#include "tablas_hash_recolocacion.h"
#include "vars.h"

/* TABLA HASH CON RECOLOCACION */

void InicializarTablaHash(TablaHash t) {
    int i;

    for (i = 0; i < Tam; i++)
        t[i].clave[0] = VACIO;

}


/******* FUNCIONES HASH *******/

/* FUNCION HASH 1 */

int Hash1(char *cad) {
    int valor;
    unsigned char *c;

    for (c = cad, valor = 0; *c; c++)
        valor += (int) *c;

    return (valor % Tam);
}

/* FUNCION HASH 2 */
int Hash2(char *cad) {
    int i, suma = 0;
    for (i = strlen(cad) - 1; i >= 0; i--) {
        suma = (suma * 256 + cad[i]) % Tam;
    }
    return suma;
}

/* FUNCION HASH 3: Probad al menos dos valores para la constante K */
int Hash3(char *cad) {
    int i, suma = 0;
    for (i = strlen(cad) - 1; i >= 0; i--) {
        suma = (suma * K + cad[i]) % Tam;
    }
    return suma;
}

int Hash(char *cad) {
    switch (HashF) {
        case 1:
            return Hash1(cad);
        case 2:
            return Hash2(cad);
        case 3:
            return Hash3(cad);
    }
    return Hash1(cad);
}


/* RECOLOCACION LINEAL: depende del valor de la constante a*/

int _ColisionesProducidasLineal(TablaHash t, char *cad) {
    int ini, aux, i;
    ini = Hash(cad);

    for (i = 0; i < Tam; i++) {
        aux = (ini + a * i) % Tam;
        if (t[aux].clave[0] == VACIO) {
            return i;
        }
    }
    return ini;
}

int _PasosAdicionalesInsercionLineal(TablaHash t, char *cad) {
    int ini, aux, i;
    ini = Hash(cad);
    for (i = 0; i < Tam; i++) {
        aux = (ini + a * i) % Tam;
        if (t[aux].clave[0] == VACIO || t[aux].clave[0] == BORRADO) {
            return i;
        }
        if (!strcmp(t[aux].clave, cad)) {
            return -1;
        }
    }
    return -1;
}

int _PasosAdicionalesBusquedaLineal(TablaHash t, char *cad) {
    int ini, aux, i;
    ini = Hash(cad);
    for (i = 0; i < Tam; i++) {
        aux = (ini + a * i) % Tam;
        if (t[aux].clave[0] == VACIO) {
            return -1;
        }
        if (!strcmp(t[aux].clave, cad)) {
            return i;
        }
    }
    return -1;
}

/* Función que localiza la posición del elemento cuando buscamos*/
int _PosicionBuscarLineal(TablaHash t, char *cad) {
    /* Devuelve el sitio donde está la clave cad, o donde debería estar. */
    /* No tiene en cuenta los borrados para avanzar.                     */

    int ini, i, aux;
    /* Hay que dar valor a la variable de recolocación a */

    ini = Hash(cad);

    for (i = 0; i < Tam; i++) {
        aux = (ini + a * i) % Tam;
        if (t[aux].clave[0] == VACIO)
            return aux;
        if (!strcmp(t[aux].clave, cad))
            return aux;
    }
    return ini;
}

/*Función que localiza la posicion para insertar un elemento */
int _PosicionInsertarLineal(TablaHash t, char *cad) {
    // Devuelve el sitio donde podriamos poner el elemento de clave cad

    int ini, aux, i;
    /* Hay que dar un valor a la variable de recolocación a */

    ini = Hash(cad);

    for (i = 0; i < Tam; i++) {
        aux = (ini + a * i) % Tam;
        if (t[aux].clave[0] == VACIO || t[aux].clave[0] == BORRADO) {
            return aux;
        }
        if (!strcmp(t[aux].clave, cad)) {
            return aux;
        }
    }
    return ini;
}

/* RECOLOCACION CUADRATICA */

int _ColisionesProducidasCuadratica(TablaHash t, char *cad) {
    int ini, aux, i;
    ini = Hash(cad);

    for (i = 0; i < Tam; i++) {
        aux = (ini + i * i) % Tam;
        if (t[aux].clave[0] == VACIO) {
            return i;
        }
    }
    return ini;
}

int _PasosAdicionalesInsercionCuadratica(TablaHash t, char *cad) {
    int ini, aux, i;
    ini = Hash(cad);
    for (i = 0; i < Tam; i++) {
        aux = (ini + i * i) % Tam;
        if (t[aux].clave[0] == VACIO || t[aux].clave[0] == BORRADO) {
            return i;
        }
        if (!strcmp(t[aux].clave, cad)) {
            return -1;
        }
    }
    return -1;
}

int _PasosAdicionalesBusquedaCuadratica(TablaHash t, char *cad) {
    int ini, aux, i;
    ini = Hash(cad);
    for (i = 0; i < Tam; i++) {
        aux = (ini + i * i) % Tam;
        if (t[aux].clave[0] == VACIO) {
            return -1;
        }
        if (!strcmp(t[aux].clave, cad)) {
            return i;
        }
    }
    return -1;
}

int _PosicionBuscarCuadratica(TablaHash t, char *cad) {
    // Devuelve el sitio donde esta cad  o donde deberia  estar.
    // No tiene en cuenta los borrados.

    int ini, i, aux;

    ini = Hash(cad);

    for (i = 0; i < Tam; i++) {
        aux = (ini + i*i) % Tam;
        if (t[aux].clave[0] == VACIO)
            return aux;
        if (!strcmp(t[aux].clave, cad))
            return aux;
    }
    return ini;
}

int _PosicionInsertarCuadratica(TablaHash t, char *cad) {
   //Devuelve el sitio donde podriamos poner cad (recolocacion cuadratica)
    int ini, i, aux;

    ini = Hash(cad);
    for (i = 0; i < Tam; i++) {
        aux = (ini + i*i) % Tam;
        if (t[aux].clave[0] == VACIO || t[aux].clave[0] == BORRADO)
            return aux;
        if (!strcmp(t[aux].clave, cad))
            return aux;
    }
    return ini;
}

int _PosicionBuscar(TablaHash t, char *cad) {
    return _PosicionBuscarLineal(t, cad);
}

int _PosicionInsertar(TablaHash t, char *cad) {
    return _PosicionInsertarLineal(t, cad);
}

int ColisionesProducidas(TablaHash t, tipo_jugador e) {
    return _ColisionesProducidasLineal(t, e.clave);
}

int PasosAdicionalesInsercion(TablaHash t, tipo_jugador elemento) {
    return _PasosAdicionalesInsercionLineal(t, elemento.clave);
}

int PasosAdicionalesBusqueda(TablaHash t, tipo_jugador elemento) {
    return _PasosAdicionalesBusquedaLineal(t, elemento.clave);
}

/* Funcion que indica si un elemento está o no en la tabla */
/* Devuelve 1 si el elemento de clave cad está en la tabla, 0 si no está */
int MiembroHash(TablaHash t, char *cad) {

    int nCol, colision;
    int pos = _PosicionBuscar(t, cad);

    if (t[pos].clave[0] == VACIO)
        return 0;
    else
        return (!strcmp(t[pos].clave, cad));
}

/* BUSCA UN ELEMENTO CON LA CLAVE INDICADA EN LA TABLA HASH, Y LO DEVUELVE,
 * ADEMAS DE INDICAR CON 1 QUE EXISTE EL ELEMENTO, Y CON 0 QUE NO ESTA EN LA TABLA */
int Busqueda(TablaHash t, char *clavebuscar, tipo_jugador *e) {

    int pos = _PosicionBuscar(t, clavebuscar);

    if (t[pos].clave[0] == VACIO)
        return 0;
    else {
        if (strcmp(t[pos].clave, clavebuscar) == 0) {
            *e = t[pos];
            return 1;
        } else return 0;
    }
}

/* Función que inserta un elemento en la tabla */
void InsertarHash(TablaHash t, tipo_jugador e) {
    int pos;

    pos = _PosicionInsertar(t, e.clave);

    if (t[pos].clave[0] == VACIO || t[pos].clave[0] == BORRADO) {
        t[pos] = e;
    } else if (strcmp(t[pos].clave, e.clave)) {
        printf("No se encuentra posicion libre.\n");
    }
}


/* Función que elimina un elemento de la tabla */
void BorrarHash(TablaHash t, char *cad) {

    int pos = _PosicionBuscar(t, cad);

    if (t[pos].clave[0] != VACIO && t[pos].clave[0] != BORRADO) {
        if (!strcmp(t[pos].clave, cad)) {
            t[pos].clave[0] = BORRADO;
            t[pos].clave[1] = VACIO;
        }
    }
}