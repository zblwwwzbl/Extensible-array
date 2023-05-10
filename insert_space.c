#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>
#include "interface.h"

#ifndef SIZE
    #define SIZE 16
#endif

#ifndef R
    #define R 2
#endif

#define NUM_ELE 131072

word_t memory_overhead;
word_t instantaneous_overhead;

int main(int argc, char *argv[]) {
    FILE* fp = fopen("./data/insert_space_results.txt", "w");
    srand(SEED); 
    void* array = initialize(DEFAULT_K, SIZE, NUM_ELE, R);
    fprintf(fp, "%u", memory_overhead);
    for (int i=0;i<NUM_ELE;i++) {
        char ele[SIZE] = {[0 ... SIZE-1] = -1};
        key_t key = (key_t) rand() % NUM_ELE;
        memcpy(ele, &key, sizeof(key_t));
        insert(array, ele);
        word_t mem_use = memory_overhead + instantaneous_overhead;
        set_instantaneous(0);
        fprintf(fp, ",%u", mem_use);
    }
    word_t rand_index = (word_t) rand() % NUM_ELE;
    char* block = (char*) get(array, rand_index);
    for (int i=0;i<SIZE;i++) {
        block[i] = block[i]+ rand_index + i;
    }
    free_mem(array);
}
