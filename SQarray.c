#include<stdio.h>
#include"SQarray.h"

inline void* initialize(word_t k, word_t element_size) {
    SQarray_t* new_SQ = (SQarray_t*)malloc(sizeof(SQarray_t));
    new_SQ->handle = initialize_dope_vector(DOPE_INIT_SIZE, DEFAULT_GROWTH, element_size);
    new_SQ->cur_l = 1;
    new_SQ->length_counter = 2;
    return (void*) new_SQ;
}

inline static index_t* address_mapping(word_t v) {
    word_t b;
    word_t shift = 1;
    if (v == 0) { 
        b = 1; 
    } else { 
        b = sizeof(word_t) + shift - __builtin_clz(v);
        b = b >> shift;
    }
    index_t* index = (index_t*)malloc(sizeof(index_t));
    index->segnum = (v >> b) + (shift << (b-shift)) - shift;
    index->offset = v & ((shift << b) - shift);
    return index;
}

inline void insert(void* array, char new_ele[]) {
    SQarray_t* SQarray = (SQarray_t*) array;
    dope_vector_t* handle = SQarray->handle;
    word_t seg_size = (word_t) 1 << SQarray->cur_l;
    if (handle->last_seg_num_elements == seg_size || handle->num_elements == 0) {
        if (SQarray->length_counter == 0) {
            SQarray->cur_l += 1;
            SQarray->length_counter = 3*(1 << (SQarray->cur_l - 2));
            seg_size = (word_t) 1 << SQarray->cur_l;
        }
        SQarray->length_counter -= 1;
        insert_segment(handle,seg_size);
    }
    dope_insert(handle, new_ele);
}

inline void* get(void* array, word_t v) {
    SQarray_t* SQarray = (SQarray_t*) array;
    index_t* index = address_mapping(v);
    void* ele = dope_get(SQarray->handle, index->segnum, index->offset);
    free(index);
    return ele;
}

inline void free_mem(void* array) {
    SQarray_t* SQarray = (SQarray_t*) array;
    dope_vector_t* handle = SQarray->handle;
    for (int i = 0; i < handle->num_segs;i++) {
        free(handle->dope[i]);
    }
    free(handle->dope);
    free(handle);
    free(SQarray);
}


inline void print_info(void* array) {
    SQarray_t* SQarray = (SQarray_t*) array;
    dope_vector_t* handle = SQarray->handle;
    word_t cur_l = 1;
    word_t cur_seg = 0;
    word_t counter = 2;
    word_t cur_seg_length = 2;
    
    while (cur_seg < handle->num_segs) {
        for (int i=0;i<counter;i++) {
            if (cur_seg == handle->num_segs) {
                break;
            }
            printf("segment %d:", cur_seg);
            for (int j =0;j<cur_seg_length;j++) {
                void* start = dope_get(handle, cur_seg, j);
                key_t key = *((key_t*) start);
                printf(" %ld", key);
            }
            printf("\n");
            cur_seg++;
        }
        cur_l++;
        counter = 3*(1 << (cur_l - 2));
        cur_seg_length = (word_t) 1 << cur_l;
    }
}