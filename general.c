#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include"general.h"



inline dope_vector_t* initialize_dope_vector(word_t init_size, double growth_mult, word_t element_size) {
    dope_vector_t* new_dope_vec = (dope_vector_t*)malloc(sizeof(dope_vector_t));
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

inline void insert_segment(dope_vector_t* handle, word_t segsize) {
    if (handle->num_segs == handle->dope_size) {
        handle->dope_size = handle->growth_multiplier * handle->dope_size;
        handle->dope = (char**)realloc(handle->dope,sizeof(char*)*(handle->dope_size));
    }
    handle->dope[handle->num_segs] = (char*)malloc(sizeof(char)*segsize*handle->element_size);
    handle->num_segs += 1;
    handle->last_seg_num_elements = 0;
    handle->last_seg_size = segsize;
}

inline void* dope_get(dope_vector_t* handle, word_t segnum, word_t offset) {
    char* start = (handle->dope)[segnum];
    return (void*)(start + offset*(handle->element_size));
}

inline void dope_insert(dope_vector_t* handle, char new_ele[]) {
    char* seg = (handle->dope)[handle->num_segs-1];
    char* start = seg + handle->num_elements*handle->element_size;
    memcpy(new_ele, start, handle->element_size);
    handle->last_seg_num_elements += 1;
    handle->num_elements += 1;
}