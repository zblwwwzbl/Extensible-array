#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>
#include "interface.h"


void heapify(void* array, word_t n, word_t i, word_t element_size) {
    int largest = i;
    int left_child = 2 * i + 1;
    int right_child = 2 * i + 2;

    // Find the largest element among the root and its children
    if (left_child < n) {
        char* largest_element = get(array, largest);
        char* left_element = get(array, left_child);
        key_t largest_key = *((key_t*) largest_element);
        key_t left_key = *((key_t*) left_element);
        if (left_key > largest_key) {
            largest = left_child;
        }
    }

    if (right_child < n) {
        char* largest_element = get(array, largest);
        char* right_element = get(array, right_child);
        key_t largest_key = *((key_t*) largest_element);
        key_t right_key = *((key_t*) right_element);
        if (right_key > largest_key) {
            largest = right_child;
        }
    }

    // If the largest element is not the root, swap the root with the largest element and heapify the affected subtree
    if (largest != i) {
        char* root_element = get(array, i);
        char* largest_element = get(array, largest);
        char temp[element_size];
        memcpy(temp, root_element, element_size);
        memcpy(root_element, largest_element, element_size);
        memcpy(largest_element, temp, element_size);
        heapify(array, n, largest, element_size);
    }
}

void heap_sort(void* array, word_t n, word_t element_size) {
    // Build a max heap from the array
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(array, n, i, element_size);
    }

    // Extract elements from the heap one by one and place them at the end of the array
    for (int i = n - 1; i >= 0; i--) {
        char* root_element = get(array, 0);
        char* last_element = get(array, i);
        char temp[element_size];
        memcpy(temp, root_element, element_size);
        memcpy(root_element, last_element, element_size);
        memcpy(last_element, temp, element_size);
        heapify(array, i, 0, element_size);
    }
}

int main(int argc, char *argv[]) {
    FILE* fp = fopen("./data/heapsort_results.csv", "a");
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
        heap_sort(array, NUM_DATA, ele_size);
        float endTime = (float)clock()/CLOCKS_PER_SEC;
        float timeElapsed = endTime - startTime;
        fprintf(fp, "%s, %f, %d\n", name(array), timeElapsed, ele_size);
        free_mem(array);
    }
}