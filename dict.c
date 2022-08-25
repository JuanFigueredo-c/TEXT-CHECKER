#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "hash_table.h"
#include "utils.h"

#define CAPACIDAD 6


char* copy_string(char* string){
    char* copy = malloc(sizeof(char)*30);
    strcpy(copy, string);
    return copy;
}

int comp_string(char* string1, char* string2){
    return strcmp(string1, string2);
}

void destr_string(char* string){
    free(string);
    return;
}

unsigned hash_string(char* string){
    return KRHash(string);
}

void impr(char* string){
    printf("*%s",string);
}

HashTable hash_dict(){
    char *palabra;
    palabra = malloc(sizeof(char)*30);


    HashTable dict_hash = hash_create(CAPACIDAD, (FuncionComparadora) comp_string,
                            (FuncionCopiadora) copy_string, (FuncionDestructora) destr_string,
                            (FuncionHash) hash_string);
                    
    char* filename = malloc(sizeof(char)*40);
    printf("Ingrese el nombre del archivo de diccionario a utilizar: ");
    scanf("%s", filename);

    FILE * fp;
    fp = fopen(filename,"r+");


    while(!feof(fp)){
        fscanf(fp,"%s", palabra);
        hash_insert(dict_hash, palabra);
    }

    fclose(fp);
    // hash_show(dict_hash);

    // hash_destroy(dict_hash);
    free(palabra);
    free(filename);

    return dict_hash;
}