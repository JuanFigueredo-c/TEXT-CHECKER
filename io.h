#include <stdlib.h>
#include <stdio.h>
#include "word_functions.h"
#include "utils.h"

WWord* copy_wword(WWord* wrong_word);
int comp_wword(WWord* wrong_word1, WWord* wrong_word2);
void destr_wword(WWord* wrong_word);
unsigned hash_wword(WWord* wrong_word);

HashTable open_file(char* file_name, HashTable dict_hash);
void write_file(HashTable wword_hash, char* file_name);