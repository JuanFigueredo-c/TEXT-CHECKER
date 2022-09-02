// TP FINAL - ESTRUCTURAS DE DATOS Y ALGORITMOS 1
// JUAN BAUTISTA FIGUEREDO

#ifndef __WORD_FUNCTIONS_H__
#define __WORD_FUNCTIONS_H__

#include <stdio.h>

#include "hash_table.h"

#define MAX_DIST 3
#define MAX_LEN 40

typedef struct{
    char* string;
    int line;
    char** options;
    int cant;
    int len;
} WWord;

/** Intercambia dos letras adyacentes.
 * A cada palabra formada, se la analiza mediante la funcion 'word_check'.
 * Adicionalmente se verifica el contador de sugerencias, si este es 5 la funcion termina y devuelve 1.
 * Si nunca se llega a  que el contador de sugerencias es 5 devuelve 0 */
int swap_rule(char* string, int len, HashTable dict, HashTable* distArray, WWord *wrongWord, int currentDist);

/** Inserta las letras A - Z en cualquier espacio entre las letras de la palabra, incluyendo el principio y el final
 * A cada palabra formada, se la analiza mediante la funcion 'word_check'.
 * Adicionalmente se verifica el contador de sugerencias, si este es 5 la funcion termina y devuelve 1.
 * Si nunca se llega a  que el contador de sugerencias es 5 devuelve 0 */
int insert_rule(char* string, int len, HashTable dict, HashTable* distArray, WWord *wrongWord, int currentDist);

/** Elimina los caracteres de la palabra uno por uno
 * A cada palabra formada, se la analiza mediante la funcion 'word_check'.
 * Adicionalmente se verifica el contador de sugerencias, si este es 5 la funcion termina y devuelve 1.
 * Si nunca se llega a  que el contador de sugerencias es 5 devuelve 0 */
int eliminate_rule(char* string, int len, HashTable dict, HashTable* distArray, WWord* wrongWord, int currentDist);

/** Reemplaza cada caracter de la palabra por A - Z
 * A cada palabra formada, se la analiza mediante la funcion 'word_check'.
 * Adicionalmente se verifica el contador de sugerencias, si este es 5 la funcion termina y devuelve 1.
 * Si nunca se llega a  que el contador de sugerencias es 5 devuelve 0 */
int replace_rule(char* string, int len, HashTable dict, HashTable* distArray, WWord* wrongWord, int currentDist);

/** divide a la palabra en 2 palabras, ubicando un espacio por cada caracter de la palabra
 * Para cada par de palabras formadas, se las verifica si cada una de ellas pertenece al diccionario.
 * Si es asi se agregan a las sugerencias.
 * Adicionalmente se verifica el contador de sugerencias, si este es 5 la funcion termina y devuelve 1.
 * Si nunca se llega a  que el contador de sugerencias es 5 devuelve 0 */
int divide_rule(char* string, int len, HashTable dict, WWord* wrongWord);


void wrong_word_handler(char* string, int len, HashTable dict, WWord* wrongWord);

/** Verifica distintos puntos sobre la palabra recibida:
 * Primero, verifica si la palabra recibida no ha sido analizada previamente en alguna de las distancias anteriores o la actual.
 * Si es asi, verifica si la palabra pertenece al diccionario.
 * En cuyo caso, verifica si la palabra no haya sido sugerida previamente.
 * Si ocurre esto, agrega la palabra a las posibles sugerencias de la palabra erronea.
 * Adicionalmente, mientras la distancia actual no sea la maxima, inserta la palabra en la tabla hash correspondiente a la distancia. */
void word_check(char* string, int len, int currentDist, HashTable dict, HashTable* distArray, WWord* wrongWord);

/** Aplica las reglas 1 - 5 a la palabra recibida */
int apply_rules(char* string, int len,HashTable dict, HashTable* distArray, WWord* wrongWord, int currentDist);

/** Crea e inicializa un nodo del tipo WWord */
WWord* ww_create();

#endif