/**
 * @file datastructures.c
 * @author Beilun Zhang
 * @brief 
 * @version 0.1
 * @date 2023-03-19
 * 
 * 
 */
#include<stdio.h>
#include<assert.h>
#include"datastructures.h"

#define DEFAULT_GROWTH 2
#define DOPE_INIT_SIZE 16



dope_vector_t* initialize_dope_vector(unsigned int init_size, double growth_mult) {
    dope_vector_t* new_dope_vec = (dope_vector_t*)malloc(sizeof(dope_vector_t));
    new_dope_vec->dope_size = init_size;
    new_dope_vec->dope = (node_t**)malloc(sizeof(node_t*)*init_size);
    for (int i=0;i<init_size;i++) {
        new_dope_vec->dope[i] = NULL;
    }
    new_dope_vec->growth_multiplier = growth_mult;
    new_dope_vec->num_segs = 0;
    new_dope_vec->last_seg_size = 0;
    new_dope_vec->last_seg_num_elements = 0;
    new_dope_vec->num_elements = 0;
    return new_dope_vec;
}

SQarray_t* initialize_SQ_array() {
    SQarray_t* new_SQ = (SQarray_t*)malloc(sizeof(SQarray_t));
    new_SQ->handle = initialize_dope_vector(DOPE_INIT_SIZE, DEFAULT_GROWTH);
    new_SQ->cur_l = 1;
    new_SQ->length_counter = 2;
    return new_SQ;
}

index_t* address_mapping(unsigned int v) {
    unsigned int b;
    unsigned int shift = 1;
    if (v == 0) { 
        b = 1; 
    } else { 
        b = sizeof(unsigned int) + shift - __builtin_clz(v);
        b = b >> shift;
    }
    index_t* index = (index_t*)malloc(sizeof(index_t));
    index->segnum = (v >> b) + (shift << (b-shift)) - shift;
    index->offset = v & ((shift << b) - shift);
    return index;
}

void insert_segment(dope_vector_t* handle, unsigned int segsize) {
    if (handle->num_segs == handle->dope_size) {
        handle->dope_size = handle->growth_multiplier * handle->dope_size;
        handle->dope = (node_t**)realloc(handle->dope,sizeof(node_t*)*(handle->dope_size));
    }
    handle->dope[handle->num_segs] = (node_t*)malloc(sizeof(node_t)*segsize);
    handle->num_segs += 1;
    handle->last_seg_num_elements = 0;
    handle->last_seg_size = segsize;
}

void SQarray_insert(SQarray_t* SQarray, node_t new_ele) {
    dope_vector_t* handle = SQarray->handle;
    unsigned int seg_size = handle->last_seg_num_elements;
    if (handle->last_seg_num_elements == seg_size || handle->num_segs == 0) {
        if (SQarray->length_counter == 0) {
            SQarray->cur_l += 1;
            SQarray->length_counter = 3*(1 << (SQarray->cur_l - 2));
            seg_size = (unsigned int) 1 << SQarray->cur_l;
        }
        insert_segment(handle,seg_size);
    }
    handle->dope[handle->num_segs-1][handle->last_seg_num_elements] = new_ele;
    handle->last_seg_num_elements += 1;
    handle->num_elements += 1;
}

void SQarray_get(SQarray_t* SQarray, unsigned int v) {
    index_t* index = address_mapping(v);
    node_t node = SQarray->handle->dope[index->segnum][index->offset];
    free(index);
    return node;
}

void SQarray_free(SQarray_t* SQarray) {
    dope_vector_t* handle = SQarray->handle;
    unsigned int cur_l = 1;
    unsigned int cur_seg = 0;
    unsigned int counter = 2;
    unsigned int cur_seg_length = 2;
    while (cur_seg < handle->num_segs) {
        for (int i=0;i<counter;i++) {
            if (cur_seg == handle->num_segs) {
                break;
            }
            for (int j =0;j<cur_seg_length;j++) {
                free(handle->dope[cur_seg][j]);
            }
            free
            cur_seg++;
        }
        cur_l++;
        counter = 3*(1 << (cur_l - 2));
        cur_seg_length = (unsigned int) 1 << cur_l;
    }
}

void print_SQarray(SQarray_t* SQarray) {

}