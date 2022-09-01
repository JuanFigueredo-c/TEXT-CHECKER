#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "hash_table.h"
#include "utils.h"

#define CAPACITY 500
#define MAX_LEN 40

/** Funcion copiadora para strings*/
char* copy_string(char* string, int len){
    char* copy = malloc(sizeof(char)*len+1);
    memcpy(copy, string, len+1);
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
                    
    char* filename = malloc(sizeof(char)*MAX_LEN);
    printf("Ingrese el nombre del archivo de diccionario a utilizar: ");
    scanf("%s", filename);

    FILE * fp;
    fp = fopen(filename,"r+");

    char buffer[MAX_LEN], caracter;
    int len = 0;
    
    while(!feof(fp)){
        caracter = tolower(fgetc(fp));
        if((unsigned int) caracter >= 97 && (unsigned int)caracter <= 122){
            buffer[len] = caracter;
            len++;
        }
        else{
            buffer[len] = '\0';
            if(len > 0){
                hash_insert(dict_hash, buffer, len);
            }
            len = 0;
        }
    }

    fclose(fp);

    free(filename);

    return dict_hash;
}
