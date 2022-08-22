

typedef struct _GNode{
    struct _GNode *next;
    struct _GNode *last;
    void* data;
} GNode;

typedef GNode *GList;

GList glist_insert(GList list, void* data,
     void* (*copy) (void*), int (*comp)(void*, void*));

GList glist_create();

void glist_destroy(GList list, void (*destr)(void*));