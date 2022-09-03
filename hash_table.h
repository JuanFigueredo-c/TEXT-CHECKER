// TP FINAL - ESTRUCTURAS DE DATOS Y ALGORITMOS 1
// JUAN BAUTISTA FIGUEREDO

#ifndef __HASH_TABLE_H__
#define __HASH_TABLE_H__
#include "glist.h"

/** Retorna una copia fisica del dato */
typedef void *(*FuncionCopiadora)(void *dato, int dato2);
/** Retorna 1 si son iguales, 0 si no*/
typedef int (*FuncionComparadora)(void *dato1, void *dato2);
/** Libera la memoria alocada para el dato */
typedef void (*FuncionDestructora)(void *dato);
/** Retorna un entero sin signo para el dato */
typedef unsigned (*FuncionHash)(void *dato);


struct _HashTable{
    GList *array;
    unsigned int capacity;
    unsigned int elems;
    FuncionComparadora comp;
    FuncionCopiadora copy;
    FuncionDestructora destr;
    FuncionHash hash;
};

typedef struct _HashTable *HashTable;

/** Crea una tabla hash */
HashTable hash_create( unsigned capacity, FuncionComparadora comp,
                      FuncionCopiadora copy, FuncionDestructora destr,
                      FuncionHash hash );

/** Inserta un elemento en la tabla hash recibida,
 * si el dato ya estaba almacenado, no lo almacena.
 * Verfica que el factor de carga de la tabla se mantenga dentro de un
 * limite establecido, si lo sobre pasa, redimensiona la tabla */
HashTable hash_insert(HashTable tabla, void* dato, int len);

/** Redimensiona la tabla hash recibida. Duplica su capacidad
 * y re-hashea los datos. */
void hash_resize(HashTable tabla);

/** Busca un elemento en la tabla hash recibida. 
 * Devuelve 1 si el dato se encuentra en la tabla o 0 si no. */
int hash_search(HashTable tabla, void* dato);

/** Destruye una tabla hash*/
void hash_destroy(HashTable tabla);

/** Pide por teclado el ingreso del nombre del archivo que contiene el diccionario a leer.
 * Devuelve una tabla hash con los datos del diccionario leido. */
HashTable hash_dict();

#endif

