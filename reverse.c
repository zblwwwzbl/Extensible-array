#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>
#include "interface.h"

#ifndef SIZE
    #define SIZE 12
#endif

#ifndef R
    #define R 2
#endif

static inline void reverse(void* array, word_t ele_size) {
    word_t n = size(array);
    char temp[ele_size];
    for (int i=0;i<n/2;i++) {
        void* a = get(array, i);
        void* b = get(array, n-1-i);
        memcpy(temp, a, ele_size);
        memcpy(a, b, ele_size);
        memcpy(b, temp, ele_size);
    }
}

int main(int argc, char *argv[]) {
    FILE* fp = fopen("./data/reverse_results.csv", "a"); 
    srand(SEED);
    void* array = initialize(DEFAULT_K, SIZE, NUM_DATA, R);
    for (int i=0;i<NUM_DATA;i++) {
        char ele[SIZE];
        key_t key = (key_t) rand() % NUM_DATA;
        memcpy(ele, &key, sizeof(key_t));
        insert(array, ele);
    }
    float startTime = (float)clock()/CLOCKS_PER_SEC;
    reverse(array, SIZE);
    float endTime = (float)clock()/CLOCKS_PER_SEC;
    float timeElapsed = endTime - startTime;
    word_t rand_index = (word_t) rand() % NUM_DATA;
    char* block = (char*) get(array, rand_index);
    for (int i=0;i<SIZE;i++) {
        block[i] = block[i]+ rand_index + i;
    }
    fprintf(fp, "%s, %f, %d\n", name(array), timeElapsed, SIZE);
    free_mem(array);
}