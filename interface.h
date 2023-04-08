#include "general.h"

#define NUM_DATA 1048576
#define LIMIT 2048
#define SEED 19284729

void* initialize(word_t seg_size, word_t element_size, word_t init_size);
void insert(void* array, char new_ele[]);
void* get(void* array, word_t v);
void free_mem(void* array);
void print_info(void* array);
word_t size(void* array);
void update(void* array, word_t v, char new_ele[]);
char* name(void* array);