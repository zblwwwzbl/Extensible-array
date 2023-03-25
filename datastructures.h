#include<stdio.h>

#define DEFAULT_GROWTH 2
#define DOPE_INIT_SIZE 16
#define DEFAULT_K 16

typedef struct{
    long key;
    char value[0]; 
} node_t;

/**
 * @brief 
 * 
 */
typedef struct{
    node_t** dope;
    unsigned int dope_size;
    unsigned int last_seg_size;
    unsigned int num_segs;
    unsigned int last_seg_num_elements;
    unsigned int num_elements;
    double growth_multiplier;
} dope_vector_t;

/**
 * @brief data structure SQarray as described in
 * 
 * The attributes are:
 *  handle - a pointer to the dope vector
 *  cur_l - defined as 2^cur_l = largest_segment_size
 *  legnth_counter - a counter that indicates the remaining number of segments before
 * largest_segment_size would double 
 * 
 * 
 */
typedef struct {
    dope_vector_t* handle;
    unsigned int cur_l;
    unsigned int length_counter;
} SQarray_t;

typedef struct {
    dope_vector_t* handle;
    unsigned int segment_size;
} sliced_array_t;

typedef struct {
    unsigned int segnum;
    unsigned int offset;
} index_t;

dope_vector_t* initialize_dope_vector(unsigned int init_size, double growth_mult);
SQarray_t* initialize_SQ_array();
index_t* address_mapping(unsigned int v);
void insert_segment(dope_vector_t* handle, unsigned int segsize);
void SQarray_insert(SQarray_t* SQarray, node_t new_ele);
node_t SQarray_get(SQarray_t* SQarray, unsigned int v);
void SQarray_free(SQarray_t* SQarray);
void SQarray_print(SQarray_t* SQarray);
sliced_array_t* initialize_sliced_array(unsigned int k);
void sliced_insert(sliced_array_t* sliced, node_t new_ele);
node_t sliced_get(sliced_array_t* sliced, unsigned int v);
void sliced_free(sliced_array_t* sliced);
void sliced_print(sliced_array_t* sliced);
