#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>
#include "interface.h"

int main(int argc, char *argv[]) {
    FILE* fp = fopen("./data/insert_results.csv", "a");
    for (word_t ele_size = DEFAULT_ELEMENT_SIZE; ele_size <= LIMIT; ele_size+=DEFAULT_ELEMENT_SIZE) {
        float startTime = (float)clock()/CLOCKS_PER_SEC;
        void* array = initialize(DEFAULT_K, ele_size, NUM_DATA);
        for (int i=0;i<NUM_DATA;i++) {
            char ele[ele_size];
            key_t key = i;
            memcpy(ele, &key, sizeof(key_t));
            insert(array, ele);
        }
        float endTime = (float)clock()/CLOCKS_PER_SEC;
        float timeElapsed = endTime - startTime;
        fprintf(fp, "%s, %f, %d\n", name(array), timeElapsed, ele_size);
        free_mem(array);
    }
}
