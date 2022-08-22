#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "WORD.h"

int main(int argc,char* argv[]){
    
    (void) argc;
    (void) argv[0];
    
    HashTable dict_hash = hash_dict();

    FILE * file_to_read = fopen(argv[1], "r+");
    FILE * file_to_write = fopen(argv[2], "w+");

    char* string =  malloc(sizeof(char)*40);
    int len, current_line = 0;

    WWord *wrong_word = malloc(sizeof(WWord));
    wrong_word->string = malloc(sizeof(char)*40);
    wrong_word->options = malloc(sizeof(char*)*5);
    for(int i = 0; i < 5; i++)
            wrong_word->options[i] = malloc(sizeof(char)*40);
    
    while(!feof(file_to_read)){
        fscanf(file_to_read, "%s", string);

        len = strlen(string);
        current_line = normalize_word(string, len, current_line);
        
        if(hash_search(dict_hash, string) == 0){
            wrong_word->line = current_line;
            printf("la palabra %s NO esta \n", string);
            strcpy(wrong_word->string, string);
            wrong_word->cant = 0;
            word_handler(string, len, dict_hash, wrong_word);
            fprintf(file_to_write,"la palabra %s es incorrecta en la linea %d\n", wrong_word->string, wrong_word->line);
            fprintf(file_to_write, "las opciones son: \n");
            for(int i = 0; i < wrong_word->cant; i++)
                fprintf(file_to_write, "%s, ", wrong_word->options[i]);
            fprintf(file_to_write, "\n");            
       }
        else{
            printf("la palabra %s SI esta \n", string);
        }
    }

    fclose(file_to_read);
    fclose(file_to_write);

    hash_destroy(dict_hash);
    printf("hash destoyed\n");
    for(int i = 0; i < 5; i++)
        free(wrong_word->options[i]);
    free(wrong_word->options);
    free(wrong_word->string);
    free(wrong_word);
    free(string);

    
    return 0;
}
