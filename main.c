#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "io.h"

int main(int argc,char* argv[]){
    
    (void) argc;
    (void) argv[0];
    
    HashTable dict_hash = hash_dict();
    //HashTable wword_hash = open_file(argv[1], dict_hash);
    handle_files(dict_hash, argv[1], argv[2]);
    //write_file(wword_hash, argv[2]);

    hash_destroy(dict_hash);
    //hash_destroy(wword_hash);

    return 0;
}
