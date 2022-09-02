// TP FINAL - ESTRUCTURAS DE DATOS Y ALGORITMOS 1
// JUAN BAUTISTA FIGUEREDO

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

#include "hash_table.h"
#include "utils.h"

#define CAPACITY 500
#define MAX_LEN 40

// FUNCIONES PARA MANEJO DE STRINGS

/** Funcion copiadora para strings*/
char* copy_string(char* string, int len) {
  char* copy = malloc(sizeof(char)*len+1);
  memcpy(copy, string, len+1);
    return copy;
}

/** Funcion comparadora para strings*/
int comp_string(char* string1, char* string2) {
  return strcmp(string1, string2);
}

/** Funcion destructora para strings*/
void destr_string(char* string) {
  free(string);
  return;
}

/** Funcion hash para strings*/
unsigned hash_string(char* string) {
    return KRHash(string);
}

// MANEJO DEL DICCIONARIO

HashTable hash_dict() {
  HashTable dict = hash_create(CAPACITY, (FuncionComparadora) comp_string,
                        (FuncionCopiadora) copy_string, (FuncionDestructora) destr_string,
                        (FuncionHash) hash_string);
                    
  char* fileName = malloc(sizeof(char)*MAX_LEN);
  printf("Ingrese el nombre del archivo de diccionario a utilizar: ");
  scanf("%s", fileName);

  FILE * fp;
  fp = fopen(fileName,"r+");

  if (fp == NULL) {
    printf("El archivo \"%s\" no se encuentra en el directorio.\n", fileName);
    hash_destroy(dict);
    free(fileName);
    return NULL;
  }

  char buffer[MAX_LEN], caracter;
  int len = 0;
    
  while(!feof(fp)){
    caracter = tolower(fgetc(fp));
    if((unsigned int) caracter >= 97 && (unsigned int) caracter <= 122) {
      buffer[len] = caracter;
      len++;
    }
    else {
      buffer[len] = '\0';
      if(len > 0)
        hash_insert(dict, buffer, len);
      len = 0;
    }
}

  fclose(fp);
  free(fileName);

  return dict;
}
