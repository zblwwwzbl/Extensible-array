#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>
#include "interface.h"



void reverse(void* array, word_t ele_size) {
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
    for (word_t ele_size = DEFAULT_ELEMENT_SIZE; ele_size <= LIMIT; ele_size+=DEFAULT_ELEMENT_SIZE) {
        void* array = initialize(DEFAULT_K, ele_size, NUM_DATA);
        for (int i=0;i<NUM_DATA;i++) {
            char ele[ele_size];
            key_t key = i;
            memcpy(ele, &key, sizeof(key_t));
            insert(array, ele);
        }
        float startTime = (float)clock()/CLOCKS_PER_SEC;
        reverse(array, ele_size);
        float endTime = (float)clock()/CLOCKS_PER_SEC;
        float timeElapsed = endTime - startTime;
        fprintf(fp, "%s, %f, %d\n", name(array), timeElapsed, ele_size);
        free_mem(array);
    }
}