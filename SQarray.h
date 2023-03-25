#include "general.h"

typedef struct {
    dope_vector_t* handle;
    word_t cur_l;
    word_t length_counter;
} SQarray_t;

typedef struct {
    word_t segnum;
    word_t offset;
} index_t;