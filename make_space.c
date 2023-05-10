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
    FILE* fp = fopen("./data/make_space_results.csv", "a"); 
    FILE* fp2 = fopen("./data/update_results.csv", "a"); 
    srand(SEED);
    void* array = initialize(DEFAULT_K, SIZE, NUM_DATA, R);
    float startTime = (float)clock()/CLOCKS_PER_SEC;
    for (int i=0;i<NUM_DATA;i++) {
        make_space(array);
    }
    float endTime = (float)clock()/CLOCKS_PER_SEC;
    float timeElapsed = endTime - startTime;
    key_t count = 0;
    float start2 = (float)clock()/CLOCKS_PER_SEC;
    for (int i=0;i<NUM_DATA;i++) {
        char ele[SIZE] = {[0 ... SIZE-1] = -1};
        key_t key = (key_t) rand() % NUM_DATA;
        memcpy(ele, &key, sizeof(key_t));
        update(array, i, ele);
    }
    float end2 = (float)clock()/CLOCKS_PER_SEC;
    float time2 = end2 - start2;
    for (int i=0;i<NUM_DATA;i++) {
        word_t idx = rand() % NUM_DATA;
        char* ele = (char*) get(array, idx);
        key_t key = *((key_t*) ele);
        count += key;
    }
    word_t rand_index = (word_t) rand() % NUM_DATA;
    char* block = (char*) get(array, rand_index);
    for (int i=0;i<SIZE;i++) {
        block[i] = block[i]+ rand_index + i;
    }
    memcpy(block, &count, sizeof(key_t));
    fprintf(fp, "%s, %f, %d, %ld\n", name(array), timeElapsed, SIZE, count);
    fprintf(fp2, "%s, %f, %d, %ld\n", name(array), time2, SIZE, count);
    free_mem(array);
}