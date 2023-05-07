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

#ifndef NUM_ELE
    #define NUM_ELE 1048576
#endif

int main(int argc, char *argv[]) {
    FILE* fp = fopen("./data/insert_results.csv", "a");
    srand(SEED); 
    float startTime = (float)clock()/CLOCKS_PER_SEC;
    word_t num_ele = (word_t) NUM_ELE;
    void* array = initialize(DEFAULT_K, SIZE, num_ele, R);
    for (int i=0;i<num_ele;i++) {
        char ele[SIZE] = {[0 ... SIZE-1] = -1};
        key_t key = (key_t) rand() % num_ele;
        memcpy(ele, &key, sizeof(key_t));
        insert(array, ele);
    }
    float endTime = (float)clock()/CLOCKS_PER_SEC;
    float timeElapsed = endTime - startTime;
    word_t rand_index = (word_t) rand() % num_ele;
    char* block = (char*) get(array, rand_index);
    for (int i=0;i<SIZE;i++) {
        block[i] = block[i]+ rand_index + i;
    }
    fprintf(fp, "%s, %f, %d\n", name(array), timeElapsed, SIZE);
    free_mem(array);
}
