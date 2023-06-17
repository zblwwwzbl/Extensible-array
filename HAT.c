#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"interface.h"

#define INIT_B 16
#define INIT_POW 4

word_t memory_overhead;

typedef struct {
    handle_t* handle;
    word_t B;
    word_t pow;
    word_t mask;
} HAT_t;

void* initialize(word_t seg_size, word_t element_size, word_t init_size, word_t r) {
    HAT_t* newHAT = (HAT_t*)Malloc(sizeof(HAT_t));
    newHAT->handle = initialize_dope_vector(INIT_B, 2, element_size);
    newHAT->B = INIT_B;
    newHAT->pow = 4;
    newHAT->mask = 0xF;
    return (void*)newHAT;
}

inline static void rebuild(HAT_t *hat) {
    word_t oldB = hat->B;
    hat->B *= 2;
    hat->pow += 1;
    hat->mask = (hat->B) -1;
    handle_t* handle = hat->handle;
    word_t ins = 0;
    for (word_t i = 0; i < handle->dope_size;i+=2) {
        char* cur = handle->dope[i];
        cur = (char*)Realloc(cur, hat->B * handle->element_size, hat->B * handle->element_size/2);
        memcpy(cur + oldB * handle->element_size, handle->dope[i+1], oldB * handle->element_size);
        Free(handle->dope[i+1], oldB * handle->element_size);
        handle->dope[ins] = cur;
        ins++;
    }
    handle->dope_size = hat->B;
    handle->dope = (char**)Realloc(handle->dope,sizeof(char*)*(handle->dope_size), sizeof(char*)*(handle->dope_size)/2);
    handle->last_seg_size = hat->B;
    handle->last_seg_num_elements = hat->B;
    handle->num_segs /= 2;
    set_instantaneous(hat->B * handle->element_size + memory_overhead);
}

void insert(void* array, char new_ele[]){
    HAT_t* hat = (HAT_t*) array;
    handle_t* handle = hat->handle;
    if (handle->last_seg_num_elements == handle->last_seg_size || handle->num_elements == 0) {
        if (handle->num_segs == handle->dope_size) {
            rebuild(hat);
        }
        insert_segment(handle, hat->B);
    }
    dope_insert(handle, new_ele);
}

void* get(void* array, word_t v){
    HAT_t* hat = (HAT_t*) array;
    return dope_get(hat->handle,v >> hat->pow, v & hat->mask);
}

void free_mem(void* array) {
    HAT_t* hat = (HAT_t*) array;
    handle_t* handle = hat->handle;
    for (int i = 0; i < handle->num_segs;i++) {
        free(handle->dope[i]);
    }
    free(handle->dope);
    free(handle);
    free(hat);
}

void print_info(void* array) {
    HAT_t* hat = (HAT_t*) array;
    handle_t* handle = hat->handle;
    for (word_t i = 0; i < handle->num_segs;i++) {
        printf("segment %d:", i);
        for (word_t j = 0; j < hat->B;j++) {
            if (i == handle->num_segs - 1 && j == handle->last_seg_num_elements) break;
            void* start = dope_get(handle, i, j);
            key_t key = *((key_t*) start);
            printf(" %ld", key);
        }
        printf("\n");
    }
}

word_t size(void* array) {
    HAT_t* hat = (HAT_t*) array;
    return hat->handle->num_elements;
}

void update(void* array, word_t v, char new_ele[]) {
    HAT_t* hat = (HAT_t*) array;
    dope_update(hat->handle, v >> hat->pow, v & hat->mask, new_ele);
}

void make_space(void* array) {
    HAT_t* hat = (HAT_t*) array;
    handle_t* handle = hat->handle;
    if (handle->last_seg_num_elements == handle->last_seg_size || handle->num_elements == 0) {
        if (handle->num_segs == handle->dope_size) {
            rebuild(hat);
        }
        insert_segment(handle, hat->B);
    }
    handle->last_seg_num_elements += 1;
    handle->num_elements += 1;
}

char* name(void* array) {
    char* name = malloc(sizeof(char)*10);
    strncpy(name, "HAT", 10);
    return name;
}