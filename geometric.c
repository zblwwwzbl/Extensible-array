#include <string.h>
#include<stdlib.h>
#include<stdio.h>
#include "interface.h"

#define DEFAULT_INIT_SIZE 1024
#define DEFAULT_MULT 2

typedef struct {
    char* nodes;
    word_t size;
    word_t num_elements;
    word_t element_size;
    word_t growth_multiplier;
} geometric_t;

void* initialize(word_t k, word_t element_size, word_t init_size, word_t r) {
    geometric_t* geo = (geometric_t*)Malloc(sizeof(geometric_t));
    geo->nodes = (char*)Malloc(sizeof(char)*DEFAULT_INIT_SIZE*element_size);
    geo->size = DEFAULT_INIT_SIZE;
    geo->num_elements = 0;
    geo->element_size = element_size;
    geo->growth_multiplier = DEFAULT_MULT;
    return (void*)geo;
}


void insert(void* array, char new_ele[]) {
    geometric_t* geo = (geometric_t*)array;
    if (geo->size == geo->num_elements) {
        geo->size *= geo->growth_multiplier;
        geo->nodes = (char*)realloc(geo->nodes, geo->size*geo->element_size);
    }
    void* start = geo->nodes + geo->num_elements * geo->element_size;
    memcpy(start, new_ele, geo->element_size);
    geo->num_elements += 1;
}

void* get(void* array, word_t v) {
    geometric_t* geo = (geometric_t*)array;
    return geo->nodes + v*geo->element_size;
}

word_t size(void* array) {
    geometric_t* geo = (geometric_t*)array;
    return geo->num_elements;
}

void update(void* array, word_t v, char new_ele[]) {
    geometric_t* geo = (geometric_t*)array;
    memcpy(geo->nodes + v*geo->element_size, new_ele, geo->element_size);
}

void make_space(void* array) {
    geometric_t* geo = (geometric_t*)array;
    if (geo->size == geo->num_elements) {
        geo->size *= geo->growth_multiplier;
        geo->nodes = (char*)realloc(geo->nodes, geo->size*geo->element_size);
    }
    geo->num_elements += 1;
}

void free_mem(void* array) {
    geometric_t* geo = (geometric_t*)array;
    free(geo->nodes);
    free(geo);
}


void print_info(void* array) {
    geometric_t* geo = (geometric_t*)array;
    for (int i=0;i<geo->num_elements;i++) {
        void* start = geo->nodes + i*geo->element_size;
        key_t key = *((key_t*) start);
        printf("%ld ", key);
    }
}

char* name(void* array) {
    char* name = malloc(sizeof(char)*10);
    strncpy(name, "geo", 10);
    return name;
}