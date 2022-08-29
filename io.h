#include <stdlib.h>
#include <stdio.h>
#include "word_functions.h"
#include "utils.h"

HashTable open_file(char* file_name, HashTable dict_hash);
void write_file(HashTable wword_hash, char* file_name);

void handle_files(HashTable dict_hash, char* input_file, char* output_file);

/** Escribe la palabra erronea, su linea y sus sugerencias el archivo de salida */
void write(WWord* wrong_word, FILE * fp);
