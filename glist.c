
#include <stdio.h>
#include <stdlib.h>

#include "glist.h"



GList glist_create(){ return NULL;}

GList glist_insert(GList list, void* data,
     void* (*copy) (void*), int (*comp)(void*, void*)){
    
    for(GNode *temp = list ;temp!=NULL; temp = temp->next){
        if(comp(temp->data, data) == 0){
            // printf("EL DATO YA ESTA ALMACENADO!\n");
            return list;
        }
    }
    
    GNode *newnode = malloc(sizeof(GNode));
    newnode->data = copy(data);
    newnode->next = NULL;
    newnode->last = NULL;

    if(list == NULL){
        list = newnode;
        list->last = list;
        return list;
    }


    // printf("COLISION!\n");
    GNode *temp = list;
    for(; temp->next!=NULL; temp = temp->next);
    temp->next = newnode;
    list->last = newnode;
    return list;
}

void glist_destroy(GList list, void (*destr)(void*)){
    GNode *node_to_delete;

    while(list != NULL){
        node_to_delete = list;
        list = list->next;
        destr(node_to_delete->data);
        free(node_to_delete);
        }
}


