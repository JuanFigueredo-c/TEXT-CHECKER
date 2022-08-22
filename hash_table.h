#include "glist.h"


typedef void *(*FuncionCopiadora)(void *dato);
/** Retorna una copia fisica del dato */
typedef int (*FuncionComparadora)(void *dato1, void *dato2);
/** Retorna un entero negativo si dato1 < dato2, 0 si son iguales y un entero
 * positivo si dato1 > dato2  */
typedef void (*FuncionDestructora)(void *dato);
/** Libera la memoria alocada para el dato */
typedef unsigned (*FuncionHash)(void *dato);
/** Retorna un entero sin signo para el dato */




struct _HashTable{
    GList *array;
    unsigned int capacidad;
    unsigned int elems;
    FuncionComparadora comp;
    FuncionCopiadora copy;
    FuncionDestructora destr;
    FuncionHash hash;
};

typedef struct _HashTable *HashTable;

HashTable hash_create( unsigned capacidad, FuncionComparadora comp,
                      FuncionCopiadora copy, FuncionDestructora destr,
                      FuncionHash hash );

void hash_destroy(HashTable tabla);

HashTable hash_insert(HashTable tabla, void* dato);

int hash_search(HashTable tabla, void* dato);

void impr(char* data);

void hash_show(HashTable tabla);

void hash_resize(HashTable tabla);

void hash_rearrange(HashTable tabla, unsigned limit);

void hash_pop(HashTable tabla, void* dato);

HashTable hash_dict();

