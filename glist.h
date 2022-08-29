
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
     void* (*copy) (void*), int (*comp)(void*, void*));

/** Destruye la lista enlazada general */
void glist_destroy(GList list, void (*destr)(void*));