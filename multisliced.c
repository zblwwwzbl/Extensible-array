#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"interface.h"

#define INIT_POW 3

typedef struct {
    handle_t** handles;
    word_t B;
    word_t r;
    word_t N;
    word_t pow;
    word_t* Ni;
} multisliced_t;

typedef struct {
    word_t block;
    word_t segnum;
    word_t offset;
} index_t;

inline static void combine_blocks(multisliced_t* multisliced) {
    word_t k = 0;
    handle_t** handles = multisliced->handles;
    for (word_t i = 0; i < multisliced->r-1;i++) {
        if (handles[i]->num_segs < handles[i]->dope_size) {
            k = i;
            break;
        }
    }
    for (word_t i = k-1; i != -1;i--) {
        word_t seg_size = 1 << (multisliced->pow * (i+2));
        word_t Bi = 1 << (multisliced->pow * (i+1));
        handle_t *cur_handle = handles[i+1];
        word_t mem_size = Bi*(cur_handle->element_size);
        insert_segment(cur_handle, seg_size);
        char* new_seg = (cur_handle->dope)[cur_handle->num_segs-1];
        for (word_t j=0; j<multisliced->B;j++) {
            memcpy(new_seg + j*mem_size, (handles[i]->dope)[j], mem_size);
            free((handles[i]->dope)[j]);
            (handles[i]->dope)[j] = NULL;
        }
        cur_handle->last_seg_num_elements = seg_size;
        cur_handle->num_elements += seg_size;
        handles[i]->num_segs = 0;
        handles[i]->last_seg_num_elements = 0;
        handles[i]->num_elements = 0;
        multisliced->Ni[i+2] += seg_size;
    }
    for (word_t i=k;i<multisliced->r-2;i++) {
        if (handles[i]->num_segs != handles[i]->dope_size) {
            break;
        }
        word_t seg_size = 1 << (multisliced->pow * (i+2));
        word_t Bi = 1 << (multisliced->pow * (i+1));
        handle_t *cur_handle = handles[i+1];
        word_t mem_size = Bi*(cur_handle->element_size);
        insert_segment(cur_handle, seg_size);
        char* new_seg = (cur_handle->dope)[cur_handle->num_segs-1];
        for (word_t j=0; j<multisliced->B;j++) {
            memcpy(new_seg + j*mem_size, (handles[i]->dope)[j], mem_size);
            free((handles[i]->dope)[j]);
            (handles[i]->dope)[j] = NULL;
        }
        cur_handle->last_seg_num_elements = seg_size;
        cur_handle->num_elements += seg_size;
        handles[i]->num_segs = 0;
        handles[i]->last_seg_num_elements = 0;
        handles[i]->num_elements = 0;
        multisliced->Ni[i+2] += seg_size;
    }

}

inline static void rebuild(multisliced_t* multisliced) {
    // assume B > 2^(r-1)
    handle_t** handles = multisliced->handles;
    word_t blocks = multisliced->B;
    word_t last_mult = 1 << (multisliced->r-1);
    word_t old_last_seg = 1 << (multisliced->pow * (multisliced->r-1));
    multisliced->B *= 2;
    multisliced->pow += 1;
    word_t ins = 0;
    handle_t *last_handle = handles[multisliced->r-2];
    word_t last_seg_size = 1 << (multisliced->pow * (multisliced->r-1));
    word_t mem_size = old_last_seg*(last_handle->element_size);
    for (word_t i=0; i<multisliced->r-1;i++) {
        handles[i]->dope = (char**) realloc(handles[i]->dope, sizeof(char*)*multisliced->B);
        handles[i]->dope_size = multisliced->B;
    }
    for (word_t i = 0;i < blocks; i += last_mult) {
        char* cur = (last_handle->dope)[i];
        cur = (char*)realloc(cur,last_seg_size * last_handle->element_size);
        for (word_t j=1;j<last_mult;j++) {
            memcpy(cur + j*mem_size, (last_handle->dope)[i+j], mem_size);
            free((last_handle->dope)[i+j]);
        }
        (last_handle->dope)[ins] = cur;
        ins++;
    }
    last_handle->num_segs = blocks/last_mult;
    last_handle->last_seg_num_elements = last_seg_size;
    last_handle->last_seg_size = last_seg_size;
}



void* initialize(word_t seg_size, word_t element_size, word_t init_size, word_t r) {
    multisliced_t* multisliced = (multisliced_t*)malloc(sizeof(multisliced_t));
    multisliced->r = r;
    multisliced->B = 1 << INIT_POW;
    multisliced->pow = INIT_POW;
    multisliced->N = 0;
    multisliced->handles = (handle_t**)malloc(r*sizeof(handle_t*));
    for (word_t i = 0; i < r-1;i++) {
        multisliced->handles[i] = initialize_dope_vector(multisliced->B, 2, element_size);
    }
    multisliced->Ni = (word_t*)calloc(r+1, sizeof(word_t));
    return multisliced;
}

inline static index_t* address_mapping(multisliced_t* multisliced, word_t v) {
    handle_t** handles = multisliced->handles;
    // word_t diff = multisliced->N - v;
    // word_t k;
    // if (diff == 0) {
    //     k = 0;
    // } else {
    //     k = (31 - __builtin_clz(diff))/(multisliced->pow);
    // }
    // word_t Nkp1 = 0;
    // for (int i=k;i < multisliced->r - 1;i++) {
    //     Nkp1 += handles[i]->num_segs * (1 << (multisliced->pow * (i+1)));
    // }
    // if (k == 0 && handles[0]->last_seg_num_elements != multisliced->B) {
    //     Nkp1 -= multisliced->B;                   
    // }
    word_t k = 0;
    for (int i=0;i<multisliced->r;i++) {
        if (multisliced->Ni[i+1] <= v && v < multisliced->Ni[i]) {
            k = i;
            break;
        }
    }
    word_t Bk = 1 << (multisliced->pow * k);
    word_t offset = (v - multisliced->Ni[k+1]) % Bk;
    word_t segnum = (v - multisliced->Ni[k+1]) / Bk;
    index_t* index = (index_t*)malloc(sizeof(index_t));
    if (k == 0) {
        index->block = 0;
        index->segnum = handles[0]->num_segs-1;
        index->offset = segnum;
    } else {
        index->block = k-1;
        index->segnum = segnum;
        index->offset = offset;
    }
    return index;
}

void insert(void* array, char new_ele[]) {
    multisliced_t* multisliced = (multisliced_t*)array;
    handle_t** handles = multisliced->handles;
    handle_t* h1 = handles[0];
    // if (multisliced->N == 1 << (multisliced->pow * multisliced->r)) {
    //     rebuild(multisliced);
    // } 
    // else if (h1->num_segs == h1->dope_size && 
    //     h1->last_seg_num_elements == h1->last_seg_size) {
    //     combine_blocks(multisliced);
    // } 
    if (h1->last_seg_num_elements == h1->last_seg_size || 
               h1->num_elements == 0) {
        insert_segment(h1, multisliced->B);
        if (h1->num_elements != 0) {
            multisliced->Ni[1] += multisliced->B;
        }
    }
    dope_insert(h1, new_ele);
    multisliced->N += 1;
    multisliced->Ni[0] += 1;
    if (h1->num_segs == h1->dope_size && 
        h1->last_seg_num_elements == h1->last_seg_size) {
        multisliced->Ni[1] += multisliced->B;
        combine_blocks(multisliced);
    }
    if (multisliced->N == 1 << (multisliced->pow * multisliced->r)) {
        rebuild(multisliced);
    } 
    
}

void* get(void* array, word_t v) {
    multisliced_t* multisliced = (multisliced_t*)array;
    handle_t** handles = multisliced->handles;
    index_t* index = address_mapping(multisliced, v);
    void* ele = dope_get(handles[index->block], index->segnum, index->offset);
    free(index);
    return ele;
}

void free_mem(void* array) {
    multisliced_t* multisliced = (multisliced_t*)array;
    handle_t** handles = multisliced->handles;
    for (int i=0; i<multisliced->r-1; i++) {
        handle_t* cur = handles[i];
        for (int j=0;j<cur->num_segs;j++) {
            free(cur->dope[j]);
        }
        free(handles[i]);
    }
    free(handles);
    free(multisliced);
}

void print_info(void* array) {
    multisliced_t* multisliced = (multisliced_t*)array;
    handle_t** handles = multisliced->handles;
    for (int k=0; k<multisliced->r-1; k++) {
        printf("handle %d: \n", k);
        handle_t* handle = handles[k];
        for (word_t i = 0; i < handle->num_segs;i++) {
            printf("    segment %d:", i);
            for (word_t j = 0; j < handle->last_seg_size;j++) {
                if (i == handle->num_segs - 1 && j == handle->last_seg_num_elements) break;
                void* start = dope_get(handle, i, j);
                key_t key = *((key_t*) start);
                printf(" %ld", key);
            }
            printf("\n");
        }
    }
}

word_t size(void* array) {
    multisliced_t* multisliced = (multisliced_t*)array;
    return multisliced->N;
}

void update(void* array, word_t v, char new_ele[]) {
    multisliced_t* multisliced = (multisliced_t*)array;
    index_t* index = address_mapping(multisliced, v);
    dope_update((multisliced->handles)[index->block], index->segnum, index->offset, new_ele);
    free(index);
}


char* name(void* array) {
    multisliced_t* multisliced = (multisliced_t*)array;
    char* name = malloc(sizeof(char)*10);
    sprintf(name, "MSarray_%d", multisliced->r);
    return name;
}