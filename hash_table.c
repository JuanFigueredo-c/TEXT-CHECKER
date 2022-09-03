// TP FINAL - ESTRUCTURAS DE DATOS Y ALGORITMOS 1
// JUAN BAUTISTA FIGUEREDO

#include <stdlib.h>
#include <stdio.h>

#include "hash_table.h"

#define CHARGE_FACTOR 0.75

HashTable hash_create(unsigned capacity,
                      FuncionComparadora comp, FuncionCopiadora copy,
                      FuncionDestructora destr, FuncionHash hash) {
  HashTable tabla = malloc(sizeof(struct _HashTable));

  tabla->comp = comp;
  tabla->destr = destr;
  tabla->copy = copy;
  tabla->hash = hash;

  tabla->capacity = capacity;
  tabla->elems = 0;

  tabla->array = malloc(sizeof(GList) * capacity);
  for (unsigned i = 0; i < capacity; i++) {
    tabla->array[i] = NULL;
  }
  return tabla;
}

HashTable hash_insert(HashTable tabla, void *dato, int len) {
  unsigned idx = tabla->hash(dato) % tabla->capacity;

  tabla->array[idx] =
      glist_insert(tabla->array[idx], dato, tabla->copy, tabla->comp, len);
  tabla->elems++;
  float chargeFactor = (float) tabla->elems / tabla->capacity;
  if (chargeFactor > CHARGE_FACTOR) {
    hash_resize(tabla);
  }
  return tabla;
}

void hash_resize(HashTable tabla) {
  unsigned newCapacity = tabla->capacity * 2;

  GList *newArray = malloc(sizeof(GList) * newCapacity);
  for (unsigned i = 0; i < newCapacity; i++)
    newArray[i] = NULL;

  unsigned idx;

  for (unsigned i = 0; i < tabla->capacity; i++) {
    GNode *temp = tabla->array[i];
    while (temp != NULL) {
      idx = tabla->hash(temp->data) % newCapacity;
      if (newArray[idx] == NULL) {
        newArray[idx] = temp;
      } else {
        newArray[idx]->last->next = temp;
      }
      newArray[idx]->last = temp;
      temp = temp->next;
      newArray[idx]->last->next = NULL;
    }
  }
  tabla->capacity = newCapacity;
  GList *oldArray = tabla->array;
  tabla->array = newArray;
  free(oldArray);
}

int hash_search(HashTable tabla, void *dato) {
  unsigned idx = tabla->hash(dato) % tabla->capacity;

  if (tabla->array[idx] == NULL)
    return 0;
  GNode *temp = tabla->array[idx];
  while (temp != NULL) {
    if (tabla->comp(dato, temp->data) == 0)
      return 1;
    temp = temp->next;
  }
  return 0;
}

void hash_destroy(HashTable tabla) {
  for (unsigned i = 0; i < tabla->capacity; i++)
    glist_destroy(tabla->array[i], tabla->destr);
  free(tabla->array);
  free(tabla);
}