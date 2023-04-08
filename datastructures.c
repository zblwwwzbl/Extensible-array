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
#include<stdlib.h>
#include<assert.h>
#include"datastructures.h"


handle_t* initialize_dope_vector(unsigned int init_size, double growth_mult) {
    handle_t* new_dope_vec = (handle_t*)malloc(sizeof(handle_t));
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

void insert_segment(handle_t* handle, unsigned int segsize) {
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
    handle_t* handle = SQarray->handle;
    unsigned int seg_size = (unsigned int) 1 << SQarray->cur_l;
    if (handle->last_seg_num_elements == seg_size || handle->num_elements == 0) {
        if (SQarray->length_counter == 0) {
            SQarray->cur_l += 1;
            SQarray->length_counter = 3*(1 << (SQarray->cur_l - 2));
            seg_size = (unsigned int) 1 << SQarray->cur_l;
        }
        SQarray->length_counter -= 1;
        insert_segment(handle,seg_size);
    }
    handle->dope[handle->num_segs-1][handle->last_seg_num_elements] = new_ele;
    handle->last_seg_num_elements += 1;
    handle->num_elements += 1;
}

node_t SQarray_get(SQarray_t* SQarray, unsigned int v) {
    index_t* index = address_mapping(v);
    node_t node = SQarray->handle->dope[index->segnum][index->offset];
    free(index);
    return node;
}

void SQarray_free(SQarray_t* SQarray) {
    handle_t* handle = SQarray->handle;
    for (int i = 0; i < handle->num_segs;i++) {
        free(handle->dope[i]);
    }
    free(handle->dope);
    free(handle);
    free(SQarray);
    // unsigned int cur_l = 1;
    // unsigned int cur_seg = 0;
    // unsigned int counter = 2;
    // unsigned int cur_seg_length = 2;
    
    // while (cur_seg < handle->num_segs) {
    //     for (int i=0;i<counter;i++) {
    //         if (cur_seg == handle->num_segs) {
    //             break;
    //         }
    //         for (int j =0;j<cur_seg_length;j++) {
    //             free(handle->dope[cur_seg][j]);
    //         }
    //         free
    //         cur_seg++;
    //     }
    //     cur_l++;
    //     counter = 3*(1 << (cur_l - 2));
    //     cur_seg_length = (unsigned int) 1 << cur_l;
    // }
}


void SQarray_print(SQarray_t* SQarray) {
    handle_t* handle = SQarray->handle;
    unsigned int cur_l = 1;
    unsigned int cur_seg = 0;
    unsigned int counter = 2;
    unsigned int cur_seg_length = 2;
    
    while (cur_seg < handle->num_segs) {
        for (int i=0;i<counter;i++) {
            if (cur_seg == handle->num_segs) {
                break;
            }
            printf("segment %d:", cur_seg);
            for (int j =0;j<cur_seg_length;j++) {
                printf(" %ld", handle->dope[cur_seg][j].key);
            }
            printf("\n");
            cur_seg++;
        }
        cur_l++;
        counter = 3*(1 << (cur_l - 2));
        cur_seg_length = (unsigned int) 1 << cur_l;
    }
}

sliced_array_t* initialize_sliced_array(unsigned int k) {
    sliced_array_t* sliced = (sliced_array_t*)malloc(sizeof(sliced_array_t*));
    sliced->segment_size = k;
    sliced->handle = initialize_dope_vector(DOPE_INIT_SIZE, DEFAULT_GROWTH);
    return sliced;
}

void sliced_insert(sliced_array_t* sliced, node_t new_ele) {
    handle_t* handle = sliced->handle;
    if (handle->last_seg_num_elements == handle->last_seg_size) {
        insert_segment(handle,sliced->segment_size);
    }
    handle->dope[handle->num_segs-1][handle->last_seg_num_elements] = new_ele;
    handle->last_seg_num_elements += 1;
    handle->num_elements += 1;
}

node_t sliced_get(sliced_array_t* sliced, unsigned int v) {
    return sliced->handle->dope[v / sliced->segment_size][v % sliced->segment_size];
}

void sliced_print(sliced_array_t* sliced) {
    handle_t* handle = sliced->handle;
    for (unsigned int i = 0; i < handle->num_segs;i++) {
        printf("segment %d:", i);
        for (unsigned int j = 0; j < sliced->segment_size;j++) {
            if (i == handle->num_segs - 1 && j == handle->last_seg_num_elements) break;
            printf(" %ld", handle->dope[i][j].key);
        }
        printf("\n");
    }
}

void sliced_free(sliced_array_t* sliced) {
     handle_t* handle = sliced->handle;
    for (int i = 0; i < handle->num_segs;i++) {
        free(handle->dope[i]);
    }
    free(handle->dope);
    free(handle);
    free(sliced);
}

