#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "word_functions.h"
#define MAX_DIST 3




void split(char* string, int pos, int len){

    for(int i = len; i > pos; i --){
        string[i] = string[i - 1];
    }
    string[pos] = ' ';
    string[len + 1] = '\0';
    
    return;
    }

int normalize_word(char* string, int len, int current_line){
    
    if((unsigned int) string[len-1] == 10) current_line++;
    
    for(int i = 0; i < len; i ++)
        string[i] = tolower(string[i]);
    if((unsigned int)string[len-1] < 97 || (unsigned int)string[len-1] > 122){
        string[len-1] = '\0';
    }

    return current_line;
}

//intercambiar dos letras adyacentes
int rule_1(char* string, int len, HashTable dict_hash, HashTable* dist_array, WWord *wrong_word, int current_dist){

    char* result = malloc(sizeof(char)*len);
    for(int i = 0; i < len - 1; i ++){
        memcpy(result, string, len+1);
        result[i] = string[i + 1];
        result[i+1] = string[i];
        // printf("%s\n", result);
        
        word_check(result, len + 1, current_dist, dict_hash, dist_array, wrong_word);

        if(wrong_word->cant == 5){
            free(result);
            return 1;
        }
    }

    free(result);
    return 0;

}


// insertar las letras A - Z en cualquier posicion de la palabra
int rule_2(char* string, int len, HashTable dict_hash, HashTable* dist_array, WWord* wrong_word, int current_dist){

    char* result = malloc(sizeof(char)*len+1);

    for(int i = 0; i < len + 1; i++){
        memcpy(result, string, len);
        split(result, i , len);
        for(int j = 97; j < 123; j ++){
            result[i] = (char) j;
            // printf("%s\n",result);
        
            word_check(result, len, current_dist, dict_hash, dist_array, wrong_word);
        
            if(wrong_word->cant == 5){
                free(result);
                return 1;
            }
        }
        }
        free(result);
        return 0;
    }


// eliminar cada caracter
int rule_3(char* string, int len, HashTable dict_hash, HashTable* dist_array, WWord* wrong_word, int current_dist){
    
    char* result = malloc(sizeof(char)*len);
    
    for(int i = 0; i < len; i++){
        memcpy(result, string, len);
        for(int j = i; j < len; j++){
            result[j] = result[j + 1];
        }
        result[len - 1] = '\0';
        // printf("%s\n",result);
  
        word_check(result, len - 1, current_dist, dict_hash, dist_array, wrong_word);
        
        if(wrong_word->cant == 5){
            free(result);
            return 1;
        }
    }

    free(result);
    return 0;
    }

// intercambia las letras de la a a la z
int rule_4(char* string, int len, HashTable dict_hash, HashTable* dist_array, WWord* wrong_word, int current_dist){

    char *result = malloc(sizeof(char)*len);
    
    for(int i = 0; i < len; i++){
        memcpy(result, string, len);    
        for(int j = 97; j < 123; j++){
            result[i] = (char) j;
            result[len] = '\0';
        
            word_check(result, len + 1, current_dist, dict_hash, dist_array, wrong_word);
            if(wrong_word->cant == 5){
                free(result);
                return 1;
            }
        }
    }
    free(result);
    return 0;
}

// separa las palabras en 2

int rule_5(char* string, int len, HashTable dict_hash, WWord* wrong_word){
    char* result = malloc(sizeof(char)*len + 1);
    char* word1 = malloc(sizeof(char)*len);
    char* word2 = malloc(sizeof(char)*len);
    
    for(int i = 1; i < len ; i ++){
        memcpy(result, string, len);
        split(result, i, len);
        memcpy(word1, result, i);
        word1[i] = '\0';
        for(int j = i + 1; j < len + 1; j++){
            word2[j - i - 1] = result[j];
        }
        word2[len - i] = '\0';


        if(hash_search(dict_hash, word1) == 1 && hash_search(dict_hash, word2) == 1){
            strcpy(wrong_word->options[wrong_word->cant],string);
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

void word_check(char* string, int len, int current_dist, HashTable dict_hash, HashTable* dist_array, WWord* wrong_word ){

    int bandera = 0;

    for(int i = 0; i <= current_dist - 1 && current_dist < MAX_DIST; i ++){
        if(hash_search(dist_array[i], string) == 1){
            bandera = 1;
            i = current_dist;
        }
    }
    
    if(bandera == 0){
        if( hash_search(dict_hash, string) == 1){
            bandera = 1;
            for(int i = 0; i < wrong_word->cant; i++){
                bandera = strcmp(string, wrong_word->options[i]);
                if(bandera == 0) i = wrong_word->cant;
            }
            if(bandera == 1){
                memcpy(wrong_word->options[wrong_word->cant],string, len);
                wrong_word->cant++;
            }
    }
    if(current_dist < MAX_DIST)
        dist_array[current_dist - 1] = hash_insert(dist_array[current_dist - 1], string);
    }

}

void word_handler(char* string, int len, HashTable dict_hash, WWord* wrong_word){

    HashTable* dist_array = malloc(sizeof(HashTable)*MAX_DIST - 1);
    for(int i = 0; i < MAX_DIST - 1; i++){
        dist_array[i] = hash_create(6, dict_hash->comp, dict_hash->copy,
                                    dict_hash->destr, dict_hash->hash);
    }
    
    int bandera = 0;
    int len_word = 0;
    unsigned int dict_cap = 0;


    for(int i = 1; i <= MAX_DIST; i ++){
        printf("current dist %d\n", i);
        if(i == 3){
            printf("elems %u \n", dist_array[1]->elems);
        }
        if(i == 1){
            bandera = apply_rules(string, len, dict_hash, dist_array, wrong_word, i);
            if(bandera == 1) i = MAX_DIST + 1;
        }
        else{
            dict_cap = dist_array[i - 2]->capacidad;
            for(unsigned j = 0; j < dict_cap; j ++){
                GNode *temp = dist_array[i - 2]->array[j];
                while(temp!=NULL){
                    len_word = strlen(temp->data);
                    bandera = apply_rules(temp->data, len_word, dict_hash, dist_array, wrong_word, i);
                    temp = temp->next;
                    if(bandera == 1){
                        printf("ADENTRO\n");
                        j = dict_cap;
                        i = MAX_DIST + 1;
                        temp = NULL;
                    }   
                }
            }
        }
    }
    printf("AFUERA\n");

    for(int i = 0; i < MAX_DIST -1; i ++){
        hash_destroy(dist_array[i]);
    }
    free(dist_array);
    return;
}


int apply_rules(char* string,int len,HashTable dict_hash,HashTable* dist_array,WWord* wrong_word,int current_dist){
    if(len > 1){
        
        // printf("RULE 1\n");
        if(rule_1(string, len, dict_hash, dist_array, wrong_word, current_dist) == 1) return 1;
        // printf("RULE 3\n");
        if(rule_3(string, len, dict_hash, dist_array, wrong_word, current_dist) == 1) return 1;
        // printf("RULE 5\n");
        if(rule_5(string, len, dict_hash, wrong_word) == 1) return 1;
    }
    // printf("RULE 2\n");
    if(rule_2(string, len, dict_hash, dist_array, wrong_word, current_dist) == 1) return 1;
    // printf("RULE 4\n");
    if(rule_4(string, len, dict_hash, dist_array, wrong_word, current_dist) == 1) return 1;

    return 0;
}
