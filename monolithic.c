#include <string.h>
#include<stdlib.h>
#include<stdio.h>
#include "monolithic.h"
#include "interface.h"

typedef struct {
    char* nodes;
    word_t size;
    word_t num_elements;
    word_t element_size;
} monolithic_t;

void* initialize(word_t k, word_t element_size, word_t init_size) {
    monolithic_t* mono = (monolithic_t*)malloc(sizeof(monolithic_t));
    mono->nodes = (char*)malloc(sizeof(char)*init_size*element_size);
    mono->size = init_size;
    mono->num_elements = 0;
    mono->element_size = element_size;
    return (void*)mono;
}


void insert(void* array, char new_ele[]) {
    monolithic_t* mono = (monolithic_t*)array;
    void* start = mono->nodes + mono->num_elements * mono->element_size;
    memcpy(start, new_ele, mono->element_size);
    mono->num_elements += 1;
}

void* get(void* array, word_t v) {
    monolithic_t* mono = (monolithic_t*)array;
    return mono->nodes + v*mono->element_size;
}

word_t size(void* array) {
    monolithic_t* mono = (monolithic_t*)array;
    return mono->num_elements;
}

void update(void* array, word_t v, char new_ele[]) {
    monolithic_t* mono = (monolithic_t*)array;
    memcpy(mono->nodes + v*mono->element_size, new_ele, mono->element_size);
}

void free_mem(void* array) {
    monolithic_t* mono = (monolithic_t*)array;
    free(mono->nodes);
    free(mono);
}


void print_info(void* array) {
    monolithic_t* mono = (monolithic_t*)array;
    for (int i=0;i<mono->num_elements;i++) {
        void* start = mono->nodes + i*mono->element_size;
        key_t key = *((key_t*) start);
        printf("%ld ", key);
    }
}

char* name(void* array) {
    char* name = malloc(sizeof(char)*10);
    strncpy(name, "mono", 10);
    return name;
}