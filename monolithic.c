#include "monolithic.h"

inline void* initialize(word_t k, word_t element_size) {
    monolithic_t* mono = (monolithic_t*)malloc(sizeof(monolithic_t));
    mono->nodes = (char*)malloc(sizeof(char)*k*element_size);
    mono->size = k;
    mono->num_elemnts = 0;
    mono->element_size = element_size;
    return (void*)mono;
}


inline void insert(void* array, char new_ele[]) {
    monolithic_t* mono = (monolithic_t*)array;
    void* start = mono->nodes + mono->num_elemnts * mono->element_size;
    memcopy(new_ele, start, mono->element_size);
    mono->num_elemnts += 1;
}

inline void* get(void* array, word_t v) {
    monolithic_t* mono = (monolithic_t*)array;
    return mono->nodes + v*mono->element_size;
}


inline void free_mem(void* array) {
    monolithic_t* mono = (monolithic_t*)array;
    free(mono->nodes);
    free(mono);
}


inline void print_info(void* array) {
    monolithic_t* mono = (monolithic_t*)array;
    for (int i=0;i<mono->num_elemnts;i++) {
        void* start = mono->nodes + i*mono->element_size;
        key_t key = *((key_t*) start);
        printf("%ld ", key);
    }
}