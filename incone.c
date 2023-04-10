#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "interface.h"


int main(int argc, char *argv[]) {
    FILE* fp = fopen("./data/incone_results.csv", "a");
    for (word_t ele_size = DEFAULT_ELEMENT_SIZE; ele_size <= LIMIT; ele_size+=DEFAULT_ELEMENT_SIZE) {
        void* array = initialize(DEFAULT_K, ele_size, NUM_DATA);
        for (int i=0;i<NUM_DATA;i++) {
            char ele[ele_size];
            key_t key = i;
            memcpy(ele, &key, sizeof(key_t));
            insert(array, ele);
        }
        float startTime = (float)clock()/CLOCKS_PER_SEC;
        for (int i=0;i<NUM_DATA;i++) {
            key_t key = *((key_t*) get(array, i));
            key += 1;
            char ele[ele_size];
            memcpy(ele, &key, sizeof(key_t));
            update(array, i, ele);
        }
        float endTime = (float)clock()/CLOCKS_PER_SEC;
        float timeElapsed = endTime - startTime;
        fprintf(fp, "%s, %f, %d\n", name(array), timeElapsed, ele_size);
        free_mem(array);
    }
}