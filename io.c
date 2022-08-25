#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "io.h"

WWord* copy_wword(WWord* wrong_word){
    WWord* copy = malloc(sizeof(WWord));
    copy->string = malloc(sizeof(char)*40);
    strcpy(copy->string, wrong_word->string);
    copy->cant = wrong_word->cant;
    copy->line = wrong_word->line;
    copy->options = malloc(sizeof(char*)*5);
    for(int i = 0; i < 5; i ++)
        copy->options[i] = malloc(sizeof(char)*40);
    
    for(int i = 0; i < wrong_word->cant; i++)
        strcpy(copy->options[i], wrong_word->options[i]);
    
    return copy;
}
 
int comp_wword(WWord* wrong_word1, WWord* wrong_word2){
    return strcmp(wrong_word1->string, wrong_word2->string);
}

void destr_wword(WWord* wrong_word){
    for(int i = 0; i < 5; i++){
        free(wrong_word->options[i]);
    }
    free(wrong_word->options);
    free(wrong_word->string);
    free(wrong_word);
    return;
}

unsigned hash_wword(WWord* wrong_word){
    return KRHash(wrong_word->string);
}


HashTable open_file(char* file_name, HashTable dict_hash){ 
    
    HashTable wword_hash = hash_create(10, (FuncionComparadora) comp_wword, (FuncionCopiadora) copy_wword,
                                        (FuncionDestructora) destr_wword, (FuncionHash) hash_wword);
                                        
    char* string = malloc(sizeof(char)*40);
    int len, current_line= 0;

    WWord* wrong_word;
    WWord* aux = malloc(sizeof(WWord));
    aux->string = malloc(sizeof(char)*40);

    FILE * fp = fopen(file_name, "r+");
    while(!feof(fp)){
        fscanf(fp,"%s",string);

        len = strlen(string);
        current_line = normalize_word(string, len, current_line);    
        printf("%s \n", string);
        strcpy(aux->string,string);

        if(hash_search(dict_hash, string) == 0 && hash_search(wword_hash, aux) == 0){
            wrong_word = word_handler(string, len, dict_hash);
            wword_hash = hash_insert(wword_hash, wrong_word);
            printf("a\n");
            
        }
    }
    fclose(fp);
    
    destr_wword(wrong_word);
    free(string);
    free(aux->string);
    free(aux);
    return wword_hash;
}


void write_file(HashTable wword_hash, char* file_name){

    FILE * fp = fopen(file_name, "w+");
    
    GNode* temp;
    WWord* wrong_word;
    for(unsigned i = 0; i < wword_hash->capacidad; i++){
        temp = wword_hash->array[i];
        while(temp!= NULL){
            wrong_word = temp->data;
            fprintf(fp,"------------------\n");
            fprintf(fp,"Linea %d, \"%s\" no esta en el diccionario.\n",wrong_word->line, wrong_word->string);
            fprintf(fp,"Quizas quiso decir: ");
            for(int j = 0; j < wrong_word->cant; j++){
                fprintf(fp,"%s, ",wrong_word->options[j]);
            }        
            fprintf(fp,"\n");
            temp = temp->next;
        }
    }

    fclose(fp);
}