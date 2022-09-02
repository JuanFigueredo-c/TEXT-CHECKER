// TP FINAL - ESTRUCTURAS DE DATOS Y ALGORITMOS 1
// JUAN BAUTISTA FIGUEREDO

#ifndef __IO_H__
#define __IO_H__

#include "word_functions.h"

/** Maneja los archivos de entrada y salida.
 * Abre ambos archivos y lee el archivo de entrada. 
 * Analiza cada palabra encontrada mediante la funcion 'analize_word'.
 */
void handle_files(HashTable dict, char* inputFileName, char* outputFileName);

/** Escribe la palabra erronea, su linea y sus sugerencias el archivo de salida */
void write(WWord* wrongWord, FILE * fp);

/** Busca y extrae un nodo de la tabla hash recibida. */
WWord* get_wword(HashTable wwordHash, WWord * data, int currentLine);

/** Analiza la palabra recibida y verifica si esta pertenece al diccionario.
 * Si esta no pertenece, la funcion verifica si esta pertenece a la tabla hash de las palabras
 * calculadas previamente.
 * Si no pertenece, mediante la funcion 'wrong_word_handler' se obtienen todas las posibles sugerencias y se
 * imprimen mediante la funcion 'write'.
 * Si pertenece, se extrae el nodo ya calculado de la tabla y se imprime
 */ 
void analyze_word(WWord* wrongWord, HashTable dict, HashTable wwordHash, int currentLine, FILE* outputFile);

#endif