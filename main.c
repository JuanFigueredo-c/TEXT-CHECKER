// TP FINAL - ESTRUCTURAS DE DATOS Y ALGORITMOS 1
// JUAN BAUTISTA FIGUEREDO

#include <stdlib.h>
#include "io.h"

int main(int argc, char *argv[]) {

  (void) argc;
  (void) argv[0];

  HashTable dict = hash_dict();
  if(dict != NULL) {
    handle_files(dict, argv[1], argv[2]);
    hash_destroy(dict);
  }

  return 0;
}
