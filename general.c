#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<string.h>
#include"general.h"


handle_t* initialize_dope_vector(word_t init_size, double growth_mult, word_t element_size) {
    handle_t* new_dope_vec = (handle_t*)malloc(sizeof(handle_t));
    new_dope_vec->dope_size = init_size;
    new_dope_vec->dope = (char**)malloc(sizeof(char*)*init_size);
    for (int i=0;i<init_size;i++) {
        new_dope_vec->dope[i] = NULL;
    }
    new_dope_vec->growth_multiplier = growth_mult;
    new_dope_vec->num_segs = 0;
    new_dope_vec->last_seg_size = 0;
    new_dope_vec->last_seg_num_elements = 0;
    new_dope_vec->num_elements = 0;
    new_dope_vec->element_size = element_size;
    return new_dope_vec;
}

void insert_segment(handle_t* handle, word_t segsize) {
    if (handle->num_segs == handle->dope_size) {
        handle->dope_size = handle->growth_multiplier * handle->dope_size;
        handle->dope = (char**)realloc(handle->dope,sizeof(char*)*(handle->dope_size));
    }
    handle->dope[handle->num_segs] = (char*)malloc(sizeof(char)*segsize*handle->element_size);
    handle->num_segs += 1;
    handle->last_seg_num_elements = 0;
    handle->last_seg_size = segsize;
}

void* dope_get(handle_t* handle, word_t segnum, word_t offset) {
    char* start = (handle->dope)[segnum];
    return (void*)(start + offset*(handle->element_size));
}

void dope_insert(handle_t* handle, char new_ele[]) {
    char* seg = (handle->dope)[handle->num_segs-1];
    char* start = seg + handle->last_seg_num_elements*handle->element_size;
    memcpy(start, new_ele, handle->element_size);
    handle->last_seg_num_elements += 1;
    handle->num_elements += 1;
}

void dope_update(handle_t* handle, word_t segnum, word_t offset, char new_ele[]) {
    char* start = (handle->dope)[segnum];
    memcpy(start + offset*(handle->element_size), new_ele, handle->element_size);
}