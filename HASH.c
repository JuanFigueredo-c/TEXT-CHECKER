#include <stdlib.h>
#include <stdio.h>
#include "HASH.h"
#define CHARGE_FACTOR 0.75

HashTable hash_create(unsigned capacidad,
                FuncionComparadora comp, FuncionCopiadora copy,
                FuncionDestructora destr, FuncionHash hash){
    
    HashTable tabla = malloc(sizeof(struct _HashTable));

    tabla->comp = comp;
    tabla->destr = destr;
    tabla->copy = copy;
    tabla->hash = hash;

    tabla->capacidad = capacidad;
    tabla->elems = 0;

    tabla->array = malloc(sizeof(GList)*capacidad);
    for(unsigned i = 0; i < capacidad; i++){
        tabla->array[i] = NULL;
    }
    return tabla; 
    }

HashTable hash_insert(HashTable tabla, void* dato){

    unsigned idx = tabla->hash(dato) % tabla->capacidad;

    tabla->array[idx] = glist_insert(tabla->array[idx], dato, tabla->copy, tabla->comp);
    tabla->elems++;
    float charge_factor = (float) tabla->elems / tabla->capacidad;
    if(charge_factor > CHARGE_FACTOR){
        hash_resize(tabla);
    }
    return tabla;
}

void hash_pop(HashTable tabla, void* dato){
    unsigned idx = tabla->hash(dato) % tabla->capacidad;
    GNode *node_to_delete;

    if (tabla->array[idx] == NULL){
        printf("El dato a eliminar no esta en la tabla hash\n");
        return;
    }
    if (tabla->comp(tabla->array[idx]->data, dato) == 1){
        node_to_delete = tabla->array[idx];
        tabla->destr(node_to_delete->data);
        tabla->array[idx] = node_to_delete->next;
        free(node_to_delete);
        return;
    }

    GNode *temp = tabla->array[idx];
    for(; temp->next != NULL; temp = temp->next){
        if(tabla->comp(temp->next->data, dato) == 1)
        node_to_delete = temp->next;
        temp->next = node_to_delete->next;
        tabla->destr(node_to_delete->data);
        free(node_to_delete);
        return;
    }
}

void hash_destroy(HashTable tabla){

    for(unsigned i = 0; i < tabla->capacidad; i++)
        glist_destroy(tabla->array[i], tabla->destr);

    free(tabla->array);
    free(tabla);
}

int hash_search(HashTable tabla, void* dato){
    unsigned idx = tabla->hash(dato) % tabla->capacidad;

    if(tabla->array[idx] == NULL)
        return 0;
    
    // for(GNode *temp = tabla->array[idx]; temp!=NULL; temp = temp->next){
    //     if(tabla->comp(dato, temp->data) == 0){
    //         // printf("DATO ENCONTRADO EN LA POSICION %u\n", idx);
    //         return 1;
    //     }   
    // }

    GNode *temp = tabla->array[idx];
    while(temp != NULL){
        if(tabla->comp(dato, temp->data) == 0) return 1;
        temp = temp->next;
    }

    return 0;
}

void hash_show(HashTable tabla){
    for(unsigned i = 0; i < tabla->capacidad; i++){
        printf("%u) ",i);
        for(GNode *temp = tabla->array[i]; temp!=NULL; temp = temp->next){
        impr(temp->data);
        printf(" ---> ");
      }
      printf("\n");
      }
}

void hash_resize(HashTable tabla){
    unsigned new_capacity = tabla->capacidad*2;

    GList *resized_array = malloc(sizeof(GList)*new_capacity);
    for(unsigned i = 0; i < new_capacity; i++)
        resized_array[i] = NULL;

    unsigned idx;

    GNode *temp;

    for(unsigned i = 0; i < tabla->capacidad; i++){
        GNode *temp = tabla->array[i];
        while(temp!=NULL){
            idx = tabla->hash(temp->data) % new_capacity;
            if(resized_array[idx]==NULL){
                resized_array[idx] = temp;
            }
            else{
                resized_array[idx]->last->next = temp;
            }
            resized_array[idx]->last = temp;
            temp = temp->next;
            resized_array[idx]->last->next = NULL;
        }
    }
    tabla->capacidad = new_capacity;
    GList* old_array = tabla->array;
    tabla->array = resized_array;
    free(old_array);
     
}





