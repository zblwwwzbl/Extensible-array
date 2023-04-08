#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>
#include "interface.h"



void quicksort(void* array, word_t low, word_t high, word_t ele_size) {
    if (low < high && high +1 != 0) {
        // Choose a pivot element
        void* pivot = get(array, high);
        key_t pivKey = *((key_t*) pivot);
        word_t i = low - 1;

        // Partition the array around the pivot element
        for (word_t j = low; j <= high - 1; j++) {
            void* current = get(array, j);
            key_t curKey = *((key_t*) current);
            if (curKey - pivKey <= 0) {
                i++;
                void* ati = get(array, i);
                char temp[ele_size];
                memcpy(temp, current, ele_size);
                memcpy(current, ati, ele_size);
                memcpy(ati, temp, ele_size);
            }
        }
        char temp[ele_size];
        void* ati = get(array, i+1);
        memcpy(temp, pivot, ele_size);
        memcpy(pivot, ati, ele_size);
        memcpy(ati, temp, ele_size);
        word_t pivot_index = i + 1;

        // Recursively sort the left and right partitions
        quicksort(array, low, pivot_index - 1, ele_size);
        quicksort(array, pivot_index + 1, high, ele_size);
    }
}

int main(int argc, char *argv[]) {
    FILE* fp = fopen("./data/sort_results.csv", "a");
    srand(SEED); 
    for (word_t ele_size = DEFAULT_ELEMENT_SIZE; ele_size <= LIMIT; ele_size+=DEFAULT_ELEMENT_SIZE) {
        void* array = initialize(DEFAULT_K, ele_size, NUM_DATA);
        for (int i=0;i<NUM_DATA;i++) {
            char ele[ele_size];
            key_t key = (key_t) rand() % NUM_DATA;
            memcpy(ele, &key, sizeof(key_t));
            insert(array, ele);
        }
        float startTime = (float)clock()/CLOCKS_PER_SEC;
        quicksort(array, 0, NUM_DATA-1, ele_size);
        float endTime = (float)clock()/CLOCKS_PER_SEC;
        float timeElapsed = endTime - startTime;
        fprintf(fp, "%s, %f, %d\n", name(array), timeElapsed, ele_size);
        free_mem(array);
    }
}