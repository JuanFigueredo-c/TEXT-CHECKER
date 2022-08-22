#include <stdio.h>
#include <stdlib.h>

#include "HASH.h"

typedef struct{
    char* string;
    int line;
    char** options;
    int cant;
} WWord;

// intercambiar letras adyacentes
int rule_1(char* string, int len, HashTable dict_hash, HashTable* dist_array, WWord *wrong_word, int current_dist);
// insertar las letras A - Z en cualquier posicion de la palabra
int rule_2(char* string, int len, HashTable dict_hash, HashTable* dist_array, WWord *wrong_word, int current_dist);
// eliminar cada caracter
int rule_3(char* string, int len, HashTable dict_hash, HashTable* dist_array, WWord* wrong_word, int current_dist);
// Intercambia cada caracter por A - Z
int rule_4(char* string, int len, HashTable dict_hash, HashTable* dist_array, WWord* wrong_word, int current_dist);
// divide a la palabra
int rule_5(char* string, int len, HashTable dict_hash, WWord* wrong_word);

void split(char* string, int pos, int len);

int normalize_word(char* string, int len, int current_line);

void word_handler(char* string, int len, HashTable dict_hash, WWord* wrong_word);

void word_check(char* string, int len, int current_dist, HashTable dict_hash, HashTable* dist_array, WWord* wrong_word);

int apply_rules(char* string,int len,HashTable dict_hash,HashTable* dist_array,WWord* wrong_word, int current_dist);