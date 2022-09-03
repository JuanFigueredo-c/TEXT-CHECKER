// TP FINAL - ESTRUCTURAS DE DATOS Y ALGORITMOS 1
// JUAN BAUTISTA FIGUEREDO

// TP FINAL - ESTRUCTURAS DE DATOS Y ALGORITMOS 1
// JUAN BAUTISTA FIGUEREDO

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "io.h"
#include "utils.h"


// FUNCIONES PARA NODOS TIPO 'WWord'

void impr(WWord * data) {
  printf("%s\n", data->string);
}

WWord *copy_wword(WWord * wrongWord, int len) {
  WWord *copy = malloc(sizeof(WWord));
  copy->string = malloc(sizeof(char) * len + 1);
  memcpy(copy->string, wrongWord->string, len + 1);
  copy->cant = wrongWord->cant;
  copy->line = wrongWord->line;
  copy->options = malloc(sizeof(char*) * 5);
  for (int i = 0; i < 5; i++) {
    copy->options[i] = malloc(sizeof(char) * len + 3);
    if (i < wrongWord->cant)
      memcpy(copy->options[i], wrongWord->options[i], len + 3);
  }
  return copy;
}

int comp_wword(WWord * wrongWord1, WWord * wrongWord2) {
  return strcmp(wrongWord1->string, wrongWord2->string);
}

void destr_wword(WWord * wrongWord) {
  for (int i = 0; i < 5; i++) {
    free(wrongWord->options[i]);
  }
  free(wrongWord->options);
  free(wrongWord->string);
  free(wrongWord);
  return;
}

unsigned hash_wword(WWord * wrongWord) {
  return KRHash(wrongWord->string);
}


// FUNCIONES PARA EL MANEJO DE ARCHIVOS/PALABRAS

void handle_files(HashTable dict, char *inputFileName, char *outputFileName) {
  FILE *inputFile = fopen(inputFileName, "r+");

  if(inputFile == NULL) {
    printf("El archivo \"%s\" no existe en el directorio\n", inputFileName);
    return;
  }

  printf("corrigiendo texto del archivo \"%s\"....\n", inputFileName);

  FILE *outputFile = fopen(outputFileName, "w+");

  HashTable wwordHash =
    hash_create(500, (FuncionComparadora) comp_wword,
                  (FuncionCopiadora) copy_wword,
                  (FuncionDestructora) destr_wword, (FuncionHash) hash_wword);
  
  char caracter;
  char buffer[MAX_LEN];
  int len = 0, currentLine = 1;

  WWord *wrongWord = ww_create();

  while (!feof(inputFile)) {
    caracter = tolower(fgetc(inputFile));
    if ((unsigned int) caracter >= 97 && (unsigned int) caracter <= 122) {
      buffer[len] = caracter;
      len++;
    } 
    else {
      buffer[len] = '\0';  
      if (len > 0) {
        wrongWord->len = len;
        memcpy(wrongWord->string, buffer, len + 1);
        analyze_word(wrongWord, dict, wwordHash, currentLine, outputFile);
      }
      if (caracter == '\n' || caracter == EOF)
        currentLine++;
      len = 0;
    }
  }
  printf("El archivo con las correcciones \"%s\" ha sido escrito.\n", outputFileName);
  fclose(inputFile);
  fclose(outputFile);
  destr_wword(wrongWord);
  hash_destroy(wwordHash);
}

void analyze_word(WWord* wrongWord, HashTable dict, HashTable wwordHash, int currentLine, FILE* outputFile) {
  WWord *aux;
  if (hash_search(dict, wrongWord->string) == 0) {
    wrongWord->cant = 0;
    if (hash_search(wwordHash, wrongWord) == 0) {
      wrong_word_handler(wrongWord->string, wrongWord->len, dict, wrongWord);
      wrongWord->line = currentLine;
      wwordHash = hash_insert(wwordHash, wrongWord, wrongWord->len);
      write(wrongWord, outputFile);
    } else {
      aux = get_wword(wwordHash, wrongWord, currentLine);
      write(aux, outputFile);
      destr_wword(aux);
    }
  }
}

WWord* get_wword(HashTable wwordHash, WWord * data, int currentLine) {
  unsigned idx = wwordHash->hash(data) % wwordHash->capacity;
  WWord *aux;
  GNode *temp = wwordHash->array[idx];
  while (temp != NULL) {
    if (wwordHash->comp(temp->data, data) == 0) {
      aux = copy_wword(temp->data, data->len);
      aux->line = currentLine;
      break;
    }
    temp = temp->next;
  }
  return aux;
}

void write(WWord * wrongWord, FILE * outputFile) { 
  fprintf(outputFile, "Linea %d, \"%s\" no esta en el diccionario.\n", wrongWord->line,
          wrongWord->string);
  if (wrongWord->cant > 0) {
    fprintf(outputFile, "Quizas quiso decir: ");
    for (int j = 0; j < wrongWord->cant; j++) {
      fprintf(outputFile, "%s, ", wrongWord->options[j]);
    }
    fprintf(outputFile, "\n");
  } else {
    fprintf(outputFile, "No se han encontrado sugerencias para esta palabra.\n");
  }
}
