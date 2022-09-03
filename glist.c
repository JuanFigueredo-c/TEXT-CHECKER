// TP FINAL - ESTRUCTURAS DE DATOS Y ALGORITMOS 1
// JUAN BAUTISTA FIGUEREDO

#include <stdio.h>
#include <stdlib.h>

#include "glist.h"

GList glist_create() {
  return NULL;
}

GList glist_insert(GList list, void *data,
                   void *(*copy)(void *, int), int (*comp)(void *, void *),
                   int len) {
                    
  for(GNode * temp = list; temp != NULL; temp = temp->next) {
    if (comp(temp->data, data) == 0) {
      return list;
    }
  }

  GNode *newNode = malloc(sizeof(GNode));
  newNode->data = copy(data, len);
  newNode->next = NULL;
  newNode->last = NULL;

  if (list == NULL) {
    list = newNode;
    list->last = list;
    return list;
  }

  GNode *temp = list;
  for (; temp->next != NULL; temp = temp->next);
  temp->next = newNode;
  list->last = newNode;
  return list;
}

void glist_destroy(GList list, void (*destr)(void *)) {
  GNode *nodeToDelete;

  while (list != NULL) {
    nodeToDelete = list;
    list = list->next;
    destr(nodeToDelete->data);
    free(nodeToDelete);
  }
}
