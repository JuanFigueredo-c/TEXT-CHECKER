// TP FINAL - ESTRUCTURAS DE DATOS Y ALGORITMOS 1
// JUAN BAUTISTA FIGUEREDO

#ifndef __GLIST_H__
#define __GLIST_H__

typedef struct _GNode{
    struct _GNode *next;
    struct _GNode *last;
    void* data;
} GNode;

typedef GNode *GList;

/** Inicializa una lista enlazada general en NULL */
GList glist_create();

/** Inserta el dato recibido al final de la lista enlazada recibida */
GList glist_insert(GList list, void* data,
     void* (*copy) (void*, int), int (*comp)(void*, void*), int len);

/** Destruye la lista enlazada general */
void glist_destroy(GList list, void (*destr)(void*));

#endif