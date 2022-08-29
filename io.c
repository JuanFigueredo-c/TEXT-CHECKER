#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "io.h"

void impr(WWord* data){
    printf("%s\n",data->string);
}

WWord* copy_wword(WWord* wrong_word){
    WWord* copy = malloc(sizeof(WWord));
    copy->string = malloc(sizeof(char)*40);
    strcpy(copy->string, wrong_word->string);
    copy->cant = wrong_word->cant;
    copy->line = wrong_word->line;
    copy->options = malloc(sizeof(char*)*5);
    for(int i = 0; i < 5; i ++){
        copy->options[i] = malloc(sizeof(char)*40);
        if(i < wrong_word->cant) 
            strcpy(copy->options[i], wrong_word->options[i]);    
    }
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

void get_wword(HashTable wword_hash, WWord* data, int current_line, FILE * fp2){
    unsigned idx = wword_hash->hash(data) % wword_hash->capacidad;
    WWord* aux;
    GNode* temp = wword_hash->array[idx];
    while(temp!= NULL){
        if(wword_hash->comp(temp->data, data) == 0){
            aux = copy_wword(temp->data);
            aux->line = current_line;
            write(aux, fp2);
            break;
        }
        temp = temp->next;
    }
    destr_wword(aux);
}

void write(WWord* wrong_word, FILE * fp){

    fprintf(fp,"------------------\n");
    fprintf(fp,"Linea %d, \"%s\" no esta en el diccionario.\n",wrong_word->line, wrong_word->string);
    if(wrong_word->cant > 0){
        fprintf(fp,"Quizas quiso decir: ");
        for(int j = 0; j < wrong_word->cant; j++){
            fprintf(fp,"%s, ",wrong_word->options[j]);
        }        
        fprintf(fp,"\n");
    }
    else{
        fprintf(fp, "No se han encontrado sugerencias para esta palabra.\n");
    }
}

void handle_files(HashTable dict_hash, char* input_file, char* output_file){

    HashTable wword_hash = hash_create(500, (FuncionComparadora) comp_wword, (FuncionCopiadora) copy_wword,
                                        (FuncionDestructora) destr_wword, (FuncionHash) hash_wword);
                                        
    char* string = malloc(sizeof(char)*40);
    char caracter;
    char buffer[40];
    int len = 0, current_line= 1;

    WWord* wrong_word= ww_create();
    WWord* aux = malloc(sizeof(WWord));
    aux->string = malloc(sizeof(char)*40);

    FILE * fp1 = fopen(input_file, "r+");
    FILE * fp2 = fopen(output_file, "w+");

    printf("corrigiendo texto del archivo \"%s\"....\n",input_file);
    while(!feof(fp1)){
        caracter = tolower(fgetc(fp1));
        if((unsigned int) caracter >= 97 && (unsigned int)caracter <= 122){
            buffer[len] = caracter;
            len++;
        }
        else{
            buffer[len] = '\0';
            if(len > 0){
                strcpy(string, buffer);
                if(hash_search(dict_hash, string) == 0){
                    strcpy(wrong_word->string,string); 
                    wrong_word->cant = 0;
                    if(hash_search(wword_hash, wrong_word) == 0){
                        word_handler(string, len, dict_hash, wrong_word);
                        wrong_word->line = current_line;
                        wword_hash = hash_insert(wword_hash, wrong_word);
                        write(wrong_word, fp2);
                    }
                    else{
                        get_wword(wword_hash, wrong_word,current_line, fp2);
                    }
                }
            }
            if(caracter == '\n'|| caracter == EOF) current_line++;
            len = 0;
        }
    }
    printf("El archivo con las correcciones \"%s\" ha sido escrito.\b",output_file);
    fclose(fp1);
    fclose(fp2);
    
    destr_wword(wrong_word);
    hash_destroy(wword_hash);
    
    free(string);
    free(aux->string);
    free(aux);
}
