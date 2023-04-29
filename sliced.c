#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include "interface.h"

typedef struct {
    handle_t* handle;
    word_t segment_size;
    word_t seg_size;
} sliced_array_t;



void* initialize(word_t seg_size, word_t element_size, word_t init_size, word_t r) {
    sliced_array_t* sliced = (sliced_array_t*)malloc(sizeof(sliced_array_t*));
    sliced->segment_size = DEFAULT_K;
    sliced->handle = initialize_dope_vector(DOPE_INIT_SIZE, DEFAULT_GROWTH, element_size);
    return (void*)sliced;
}

void insert(void* array, char new_ele[]) {
    sliced_array_t* sliced = (sliced_array_t*) array;
    handle_t* handle = sliced->handle;
    // printf("%d ", sliced->segment_size);
    if (handle->last_seg_num_elements == handle->last_seg_size || handle->num_elements == 0) {
        insert_segment(handle, DEFAULT_K);
    }
    dope_insert(handle, new_ele);
}

void* get(void* array, word_t v) {
    sliced_array_t* sliced = (sliced_array_t*) array;
    return dope_get(sliced->handle,v / DEFAULT_K, v % DEFAULT_K);
}

word_t size(void* array) {
    sliced_array_t* sliced = (sliced_array_t*) array;
    return sliced->handle->num_elements;
}

void update(void* array, word_t v, char new_ele[]) {
    sliced_array_t* sliced = (sliced_array_t*) array;
    dope_update(sliced->handle, v / DEFAULT_K, v % DEFAULT_K, new_ele);
}

void print_info(void* array) {
    sliced_array_t* sliced = (sliced_array_t*) array;
    handle_t* handle = sliced->handle;
    for (word_t i = 0; i < handle->num_segs;i++) {
        printf("segment %d:", i);
        for (word_t j = 0; j < DEFAULT_K;j++) {
            if (i == handle->num_segs - 1 && j == handle->last_seg_num_elements) break;
            void* start = dope_get(handle, i, j);
            key_t key = *((key_t*) start);
            printf(" %ld", key);
        }
        printf("\n");
    }
}

void free_mem(void* array) {
    sliced_array_t* sliced = (sliced_array_t*) array;
    handle_t* handle = sliced->handle;
    for (int i = 0; i < handle->num_segs;i++) {
        free(handle->dope[i]);
    }
    free(handle->dope);
    free(handle);
    free(sliced);
}

char* name(void* array) {
    char* name = malloc(sizeof(char)*10);
    strncpy(name, "sliced", 10);
    return name;
}