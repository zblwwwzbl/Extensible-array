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
} handle_t;

handle_t* initialize_dope_vector(word_t init_size, double growth_mult, word_t element_size);
void insert_segment(handle_t* handle, word_t segsize);
void dope_insert(handle_t* handle, char new_ele[]);
void* dope_get(handle_t* handle, word_t segnum, word_t offset);
void dope_update(handle_t* handle, word_t segnum, word_t offset, char new_ele[]);
