#include<stdio.h>

#define DEFAULT_GROWTH 2
#define DOPE_INIT_SIZE 16
#define DEFAULT_K 16
#define DEFAULT_ELEMENT_SIZE 16

typedef unsigned int word_t;
typedef long key_t;

typedef struct{
    char** dope;
    word_t dope_size;
    word_t last_seg_size;
    word_t num_segs;
    word_t last_seg_num_elements;
    word_t num_elements;
    word_t element_size;
    double growth_multiplier;
} dope_vector_t;

inline dope_vector_t* initialize_dope_vector(word_t init_size, double growth_mult, word_t element_size);
inline void insert_segment(dope_vector_t* handle, word_t segsize);
inline void dope_insert(dope_vector_t* handle, char new_ele[]);
inline void* dope_get(dope_vector_t* handle, word_t segnum, word_t offset);
inline void* initialize(word_t k, word_t element_size);
inline void insert(void* array, char new_ele[]);
inline void* get(void* array, word_t v);
inline void free_mem(void* array);
inline void print_info(void* array);