#include "sliced.h"


inline void* initialize(word_t k, word_t element_size) {
    sliced_array_t* sliced = (sliced_array_t*)malloc(sizeof(sliced_array_t*));
    sliced->segment_size = k;
    sliced->handle = initialize_dope_vector(DOPE_INIT_SIZE, DEFAULT_GROWTH, element_size);
    return (void*)sliced;
}

inline void insert(void* array, char new_ele[]) {
    sliced_array_t* sliced = (sliced_array_t*) array;
    dope_vector_t* handle = sliced->handle;
    if (handle->last_seg_num_elements == handle->last_seg_size) {
        insert_segment(handle,sliced->segment_size);
    }
    dope_insert(handle, new_ele);
}

inline void* get(void* array, word_t v) {
    sliced_array_t* sliced = (sliced_array_t*) array;
    return dope_get(sliced->handle,v / sliced->segment_size,v % sliced->segment_size);
}

inline void print_info(void* array) {
    sliced_array_t* sliced = (sliced_array_t*) array;
    dope_vector_t* handle = sliced->handle;
    for (word_t i = 0; i < handle->num_segs;i++) {
        printf("segment %d:", i);
        for (word_t j = 0; j < sliced->segment_size;j++) {
            if (i == handle->num_segs - 1 && j == handle->last_seg_num_elements) break;
            void* start = dope_get(handle, i, j);
            key_t key = *((key_t*) start);
            printf(" %ld", key);
        }
        printf("\n");
    }
}

inline void free_mem(void* array) {
    sliced_array_t* sliced = (sliced_array_t*) array;
     dope_vector_t* handle = sliced->handle;
    for (int i = 0; i < handle->num_segs;i++) {
        free(handle->dope[i]);
    }
    free(handle->dope);
    free(handle);
    free(sliced);
}
