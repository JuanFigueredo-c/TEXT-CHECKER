#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "hash_table.h"
#include "utils.h"

#define CAPACITY 500

/** Funcion copiadora para strings*/
char* copy_string(char* string){
    char* copy = malloc(sizeof(char)*40);
    strcpy(copy, string);
    return copy;
}

/** Funcion comparadora para strings*/
int comp_string(char* string1, char* string2){
    return strcmp(string1, string2);
}

/** Funcion destructora para strings*/
void destr_string(char* string){
    free(string);
    return;
}

/** Funcion hash para strings*/
unsigned hash_string(char* string){
    return KRHash(string);
}


HashTable hash_dict(){
    HashTable dict_hash = hash_create(CAPACITY, (FuncionComparadora) comp_string,
                            (FuncionCopiadora) copy_string, (FuncionDestructora) destr_string,
                            (FuncionHash) hash_string);
                    
    char* filename = malloc(sizeof(char)*40);
    printf("Ingrese el nombre del archivo de diccionario a utilizar: ");
    scanf("%s", filename);

    FILE * fp;
    fp = fopen(filename,"r+");

    char *string = malloc(sizeof(char)*40);
    
    while(!feof(fp)){
        fscanf(fp,"%s", string);
        hash_insert(dict_hash, string);
    }

    fclose(fp);

    free(string);
    free(filename);

    return dict_hash;
}
