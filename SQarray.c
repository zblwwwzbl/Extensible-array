#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"SQarray.h"
#include"interface.h"

typedef struct {
    handle_t* handle;
    word_t cur_l;
    word_t length_counter;
} SQarray_t;

typedef struct {
    word_t segnum;
    word_t offset;
} index_t;

void* initialize(word_t k, word_t element_size, word_t init_size) {
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
        b = 33 - __builtin_clz(v);
        b = b >> shift;
    }
    index_t* index = (index_t*)malloc(sizeof(index_t));
    index->segnum = (v >> b) + (shift << (b-shift)) - shift;
    index->offset = v & ((shift << b) - shift);
    return index;
}

void insert(void* array, char new_ele[]) {
    SQarray_t* SQarray = (SQarray_t*) array;
    handle_t* handle = SQarray->handle;
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

void* get(void* array, word_t v) {
    SQarray_t* SQarray = (SQarray_t*) array;
    index_t* index = address_mapping(v);
    void* ele = dope_get(SQarray->handle, index->segnum, index->offset);
    free(index);
    return ele;
}

word_t size(void* array) {
    SQarray_t* SQarray = (SQarray_t*) array;
    return SQarray->handle->num_elements;
}

void update(void* array, word_t v, char new_ele[]) {
    SQarray_t* SQarray = (SQarray_t*) array;
    index_t* index = address_mapping(v);
    dope_update(SQarray->handle, index->segnum, index->offset, new_ele);
    free(index);
}

void free_mem(void* array) {
    SQarray_t* SQarray = (SQarray_t*) array;
    handle_t* handle = SQarray->handle;
    for (int i = 0; i < handle->num_segs;i++) {
        free(handle->dope[i]);
    }
    free(handle->dope);
    free(handle);
    free(SQarray);
}


void print_info(void* array) {
    SQarray_t* SQarray = (SQarray_t*) array;
    handle_t* handle = SQarray->handle;
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

char* name(void* array) {
    char* name = malloc(sizeof(char)*10);
    strncpy(name, "SQ", 10);
    return name;
}