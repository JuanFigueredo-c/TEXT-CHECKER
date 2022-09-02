// TP FINAL - ESTRUCTURAS DE DATOS Y ALGORITMOS 1
// JUAN BAUTISTA FIGUEREDO

#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "word_functions.h"

WWord *ww_create() {
  WWord *wrongWord = malloc(sizeof(WWord));
  wrongWord->string = malloc(sizeof(char) * MAX_LEN);
  wrongWord->cant = 0;
  wrongWord->len = 0;
  wrongWord->options = malloc(sizeof(char *) * 5);
  for (int i = 0; i < 5; i++)
    wrongWord->options[i] = malloc(sizeof(char) * MAX_LEN);
  wrongWord->line = 0;

  return wrongWord;
}


void wrong_word_handler(char *string, int len, HashTable dict, WWord * wrongWord) {

  HashTable *distArray = malloc(sizeof(HashTable) * (MAX_DIST - 1));
  for (int i = 0; i < (MAX_DIST - 1); i++)
    distArray[i] = hash_create(500, (FuncionComparadora) dict->comp,
                    (FuncionCopiadora) dict->copy,
                    (FuncionDestructora) dict->destr,
                    (FuncionHash) dict->hash);

  int flag = 0;
  GNode *temp;

  for (int dist = 1; dist <= MAX_DIST; dist++) {
    if (dist == 1) {
      flag = apply_rules(string, len, dict, distArray, wrongWord, dist);
      if (flag == 1) {
        break;
      }
    }
    else {
      for (unsigned j = 0; j < distArray[dist - 2]->capacity; j++) {
        temp = distArray[dist - 2]->array[j];
        while (temp != NULL) {
          flag =
              apply_rules(temp->data, strlen(temp->data), dict, distArray,
                          wrongWord, dist);
          temp = temp->next;
          if (flag == 1) {
            for (int i = 0; i < MAX_DIST - 1; i++) {
              hash_destroy(distArray[i]);
            }
            free(distArray);
            return;
          }
        }
      }
    }
  }

  for (int i = 0; i < MAX_DIST - 1; i++) {
    hash_destroy(distArray[i]);
  }
  free(distArray);
}


void word_check(char *string, int len, int currentDist, HashTable dict,
                HashTable * distArray, WWord * wrongWord) {

  int flag = 0;

  // Verificacion en hash de distancias anteriores y actual
  for (int i = 0; i <= currentDist - 1 && currentDist < MAX_DIST; i++) {
    if (hash_search(distArray[i], string) == 1) {
      flag = 1;
      break;
    }
  }

  if (flag == 0) {
    if (hash_search(dict, string) == 1) {  // Verificacion palabra en diccionario
      for (int i = 0; i < wrongWord->cant; i++) {      // Verificacion palabra en sugerencias
        if (strcmp(string, wrongWord->options[i]) == 0) {
          flag = 1;
          break;
        }
      }
      if (flag == 0) {
        memcpy(wrongWord->options[wrongWord->cant], string, len + 1);
        wrongWord->cant++;
      }
    }
  }
  if (currentDist < MAX_DIST)
    distArray[currentDist - 1] =
        hash_insert(distArray[currentDist - 1], string, len);
}


int apply_rules(char *string, int len, HashTable dict,
                HashTable * distArray, WWord * wrongWord, int currentDist) {
  if (insert_rule(string, len, dict, distArray, wrongWord, currentDist)
      == 1)
    return 1;
  if (replace_rule(string, len, dict, distArray, wrongWord, currentDist)
      == 1)
    return 1;
  if (len > 1) {
    if (divide_rule(string, len, dict, wrongWord) == 1)
      return 1;
    if (swap_rule(string, len, dict, distArray, wrongWord, currentDist)
        == 1)
      return 1;
    if (eliminate_rule
        (string, len, dict, distArray, wrongWord, currentDist) == 1)
      return 1;
  }
  return 0;
}


int swap_rule(char *string, int len, HashTable dict,
              HashTable * distArray, WWord * wrongWord, int currentDist) {

  char *result = malloc(sizeof(char) * len + 2);
  char auxChar;

  memcpy(result, string, len + 1);
  for (int i = 0; i < len - 1; i++) {
    auxChar = result[i];
    result[i] = result[i + 1];
    result[i + 1] = auxChar;

    word_check(result, len + 1, currentDist, dict, distArray,
               wrongWord);

    if (wrongWord->cant == 5) {
      free(result);
      return 1;
    }
    result[i + 1] = result[i];
    result[i] = auxChar;
  }
  free(result);
  return 0;
}


int insert_rule(char *string, int len, HashTable dict,
                HashTable * distArray, WWord * wrongWord, int currentDist) {

  char *result = malloc(sizeof(char) * len + 2);
  char auxChar;
  result[0] = ' ';
  memcpy(result + 1, string, len + 1);
  for (int i = 0; i < len + 1; i++) {
    for (int j = 97; j < 123; j++) {
      result[i] = (char) j;

      word_check(result, len + 1, currentDist, dict, distArray,
                 wrongWord);

      if (wrongWord->cant == 5) {
        free(result);
        return 1;
      }
    }
    auxChar = result[i + 1];
    result[i + 1] = result[i];
    result[i] = auxChar;
  }
  free(result);
  return 0;
}


int eliminate_rule(char *string, int len, HashTable dict,
                   HashTable * distArray, WWord * wrongWord,
                   int currentDist) {
  char *result = malloc(sizeof(char) * len + 2);
  memcpy(result, string + 1, len);
  for (int i = 0; i < len; i++) {

    word_check(result, len + 1, currentDist, dict, distArray,
               wrongWord);

    result[i] = string[i];
    if (wrongWord->cant == 5) {
      free(result);
      return 1;
    }
  }
  free(result);
  return 0;
}


int replace_rule(char * string, int len, HashTable dict,
                 HashTable * distArray, WWord * wrongWord, int currentDist) {

  char *result = malloc(sizeof(char) * len + 2);
  char auxChar;
  memcpy(result, string, len + 1);
  for (int i = 0; i < len; i++) {
    auxChar = result[i];
    for (int j = 97; j < 123; j++) {
      result[i] = (char) j;

      word_check(result, len + 1, currentDist, dict, distArray,
                 wrongWord);

      if (wrongWord->cant == 5) {
        free(result);
        return 1;
      }
    }
    result[i] = auxChar;
  }

  free(result);
  return 0;
}



int divide_rule(char *string, int len, HashTable dict, WWord * wrongWord) {
  char *result = malloc(sizeof(char) * len + 2);
  char *auxWord = malloc(sizeof(char) * len + 1);

  char auxChar;
  memcpy(result + 1, string, len + 1);
  result[0] = ' ';
  for (int i = 1; i < len; i++) {
    auxChar = result[i];
    result[i] = result[i - 1];
    result[i - 1] = auxChar;
    result[i] = '\0';
    for (int j = i + 1; j < len + 1; j++) {
      auxWord[j - i - 1] = result[j];
    }
    auxWord[len - i] = '\0';
    if (hash_search(dict, result) == 1
        && hash_search(dict, auxWord) == 1) {
      result[i] = ' ';
      memcpy(wrongWord->options[wrongWord->cant], result, len + 2);
      wrongWord->cant++;
    }

    if (wrongWord->cant == 5) {
      free(result);
      free(auxWord);
      return 1;
    }
    result[i] = ' ';
  }
  free(result);
  free(auxWord);
  return 0;
}
