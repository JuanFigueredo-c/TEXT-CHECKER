#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "word_functions.h"


void word_handler(char* string, int len, HashTable dict_hash, WWord* wrong_word){

    HashTable* dist_array = malloc(sizeof(HashTable)*(MAX_DIST - 1));
    for(int i = 0; i < (MAX_DIST - 1); i++)
        dist_array[i] = hash_create(200, (FuncionComparadora) dict_hash->comp, (FuncionCopiadora) dict_hash->copy,
                                    (FuncionDestructora) dict_hash->destr,(FuncionHash) dict_hash->hash);
    
    int flag = 0;
    unsigned int dict_cap = 0;

    GNode* temp;

    for(int i = 1; i <= MAX_DIST; i ++){
        if(i == 1){
            flag = apply_rules(string, len, dict_hash, dist_array, wrong_word, i);
            if(flag == 1){ 
                break;
            }
        }
        else{
            dict_cap = dist_array[i - 2]->capacidad;
            for(unsigned j = 0; j < dict_cap; j ++){
                temp = dist_array[i - 2]->array[j];
                while(temp!=NULL){
                    flag = apply_rules(temp->data, strlen(temp->data), dict_hash, dist_array, wrong_word, i);
                    temp = temp->next;
                    if(flag == 1){
                        break;
                    }
                }
            }
        }
    }

    for(int i = 0; i < MAX_DIST -1; i ++){
        hash_destroy(dist_array[i]);
    }
    free(dist_array);
}


void word_check(char* string, int len, int current_dist, HashTable dict_hash, HashTable* dist_array, WWord* wrong_word ){

    int flag = 0;

    // Verificacion en hash de distancias anteriores y actual
    for(int i = 0; i <= current_dist - 1 && current_dist < MAX_DIST; i ++){
        if(hash_search(dist_array[i], string) == 1){
            flag = 1;
            break;
        }
    }

    if(flag == 0){
        if(hash_search(dict_hash, string) == 1){  // Verificacion palabra en diccionario
            for(int i = 0; i < wrong_word->cant; i++){ // Verificacion palabra en sugerencias
                if(strcmp(string, wrong_word->options[i]) == 0){ 
                    flag = 1;
                    break;
                }
            }
            if(flag == 0){
                strcpy(wrong_word->options[wrong_word->cant],string);
                wrong_word->cant++;
            }
        }
    }
    if(current_dist < MAX_DIST) 
        dist_array[current_dist - 1] = hash_insert(dist_array[current_dist - 1], string);
}


int apply_rules(char* string,int len,HashTable dict_hash,HashTable* dist_array,WWord* wrong_word,int current_dist){
    if(len > 1){
        if(divide_rule(string, len, dict_hash, wrong_word) == 1) return 1;
        if(swap_rule(string, len, dict_hash, dist_array, wrong_word, current_dist) == 1) return 1;
        if(eliminate_rule(string, len, dict_hash, dist_array, wrong_word, current_dist) == 1) return 1;
    }
    if(replace_rule(string, len, dict_hash, dist_array, wrong_word, current_dist) == 1) return 1;
    if(insert_rule(string, len, dict_hash, dist_array, wrong_word, current_dist) == 1) return 1;
    return 0;
}


int swap_rule(char* string, int len, HashTable dict_hash, HashTable* dist_array, WWord *wrong_word, int current_dist){

    char* result = malloc(sizeof(char)*len+2);
    char aux;

    memcpy(result, string,len + 1);
    for(int i = 0; i < len - 1; i ++){
        aux = result[i];
        result[i] = result[i+1];
        result[i+1] = aux;
        
        word_check(result, len + 1, current_dist, dict_hash, dist_array, wrong_word);

        if(wrong_word->cant == 5){
            free(result);
            return 1;
        }
        result[i+1] = result[i];
        result[i] = aux;
    }
    free(result);
    return 0;
}


int insert_rule(char* string, int len, HashTable dict_hash, HashTable* dist_array, WWord* wrong_word, int current_dist){

    char* result = malloc(sizeof(char)*len+2);
    char aux;
    strcpy(result," ");
    strcat(result,string);
    for(int i = 0; i < len + 1; i++){
        for(int j = 97; j < 123; j ++){
            result[i] = (char) j;

            word_check(result, len + 1, current_dist, dict_hash, dist_array, wrong_word);

            if(wrong_word->cant == 5){
                free(result);
                return 1;
            }
        }
        aux = result[i + 1];
        result[i + 1] = result[i];
        result[i] = aux;
    }
    free(result);
    return 0;
}


int eliminate_rule(char* string, int len, HashTable dict_hash, HashTable* dist_array, WWord* wrong_word, int current_dist){
    
    char* result = malloc(sizeof(char)*len+2);
    
    for(int i = 0; i < len; i++){
        memcpy(result, string, len + 1);
        for(int j = i; j < len; j++){
            result[j] = result[j + 1];
        }
        result[len - 1] = '\0';
        
        word_check(result, len + 1, current_dist, dict_hash, dist_array, wrong_word);

        if(wrong_word->cant == 5){
            free(result);
            return 1;
        }
    }
    free(result);
    return 0;
    }


int replace_rule(char* string, int len, HashTable dict_hash, HashTable* dist_array, WWord* wrong_word, int current_dist){

    char *result = malloc(sizeof(char)*len+2);
    char aux;
    memcpy(result, string,len + 1);    
    for(int i = 0; i < len; i++){
        aux = result[i];
        for(int j = 97; j < 123; j++){
            if(aux == (char) j) continue;
            result[i] = (char) j;
        
            word_check(result, len + 1, current_dist, dict_hash, dist_array, wrong_word);
            
            if(wrong_word->cant == 5){
                free(result);
                return 1;
            }
        }
        result[i] = aux;
    }
    
    free(result);
    return 0;
}



int divide_rule(char* string, int len, HashTable dict_hash, WWord* wrong_word){
    char* result = malloc(sizeof(char)*len + 2);
    char* word1 = malloc(sizeof(char)*len);
    char* word2 = malloc(sizeof(char)*len);

    char aux;
    strcpy(result," ");
    strcat(result, string);
    for(int i = 1; i < len ; i ++){
        aux = result[i];
        result[i] = result[i - 1];
        result[i - 1] = aux;
        memcpy(word1, result, i);
        word1[i] = '\0';
        for(int j = i + 1; j < len + 1; j++){
            word2[j - i - 1] = result[j];
        }
        word2[len - i] = '\0';

        if(hash_search(dict_hash, word1) == 1 && hash_search(dict_hash, word2) == 1){
            strcpy(wrong_word->options[wrong_word->cant],result);
            wrong_word->cant++;
        }
        
        if(wrong_word->cant == 5){
            free(result);
            free(word1);
            free(word2);
            return 1;
        }
 
    }
    free(result);
    free(word1);
    free(word2);
    return 0;
    }


WWord* ww_create(){

    WWord* wrong_word = malloc(sizeof(WWord));
    wrong_word->string = malloc(sizeof(char)*40);
    wrong_word->cant = 0;
    wrong_word->options = malloc(sizeof(char*)*5);
    for(int i = 0; i < 5; i++)
        wrong_word->options[i] = malloc(sizeof(char)*40);

    wrong_word->line = 0;
    
    return wrong_word;
}
