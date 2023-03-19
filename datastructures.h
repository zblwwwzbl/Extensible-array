#include<stdio.h>


typedef struct{
    long key;
    char info[0]; 
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
    unsigned int length_counter
} SQarray_t;

typedef struct {
    dope_vector_t* handle;
    unsigned int array_size;
    unsigned int segment_size;
} sliced_array_t;

typedef struct {
    unsigned int segnum;
    unsigned int offset;
} index_t;