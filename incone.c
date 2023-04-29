#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "interface.h"

#ifndef SIZE
    #define SIZE 12
#endif

#ifndef R
    #define R 2
#endif

int main(int argc, char *argv[]) {
    FILE* fp = fopen("./data/incone_results.csv", "a"); 
    srand(SEED);
    void* array = initialize(DEFAULT_K, SIZE, NUM_DATA, R);
    for (int i=0;i<NUM_DATA;i++) {
        char ele[SIZE];
        key_t key = (key_t) rand() % NUM_DATA;
        memcpy(ele, &key, sizeof(key_t));
        insert(array, ele);
    }
    float startTime = (float)clock()/CLOCKS_PER_SEC;
    for (int i=0;i<NUM_DATA;i++) {
        key_t key = *((key_t*) get(array, i));
        key += 1;
        char ele[SIZE];
        memcpy(ele, &key, sizeof(key_t));
        update(array, i, ele);
    }
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