#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "interface.h"

#define DATA 133
#define ELE_SIZE 34
#define R 3

typedef struct {
    void* data;
    word_t rows;
    word_t cols;
} matrix_t;

matrix_t* create_matrix(word_t rows, word_t cols, word_t element_size) {
    matrix_t* matrix = (matrix_t*)malloc(sizeof(matrix_t));
    matrix->rows = rows;
    matrix->cols = cols;
    matrix->data = initialize(DEFAULT_K, element_size, rows*cols, R);
    return matrix;
}

void free_matrix(matrix_t* matrix) {
    free_mem(matrix->data);
    free(matrix);
}

matrix_t* multiply(matrix_t* a, matrix_t* b, word_t element_size) {
    if (a->cols != b->rows) {
        // Error: matrices cannot be multiplied
        return NULL;
    }

    // Allocate memory for the result matrix
    matrix_t* result = create_matrix(a->rows, b->cols, element_size);

    for (word_t i = 0; i < a->rows; i++) {
        for (word_t j = 0; j < b->cols; j++) {
            key_t sum = 0;
            for (word_t k = 0; k < a->cols; k++) {
                key_t* a_value = (key_t*) get(a->data, i*a->cols+k);
                key_t* b_value = (key_t*) get(b->data, k*b->cols+j);
                sum += (*a_value) * (*b_value);
            }
            char ele[element_size];
            memcpy(ele, &sum, sizeof(key_t));
            insert(result->data, ele);
        }
    }

    return result;
}

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
    // matrix_t* m = create_matrix(16, 16, ELE_SIZE);
    // matrix_t* n = create_matrix(16, 16, ELE_SIZE);
    void* array = initialize(DEFAULT_K, ELE_SIZE, DATA, R);
    for (int i=0;i<DATA;i++) {
        char ele1[ELE_SIZE];
        // char ele2[ELE_SIZE];
        key_t key = (key_t) rand()%DATA;
        memcpy(ele1, &key, sizeof(key_t));
        // memcpy(ele2, &key, sizeof(key_t));
        insert(array, ele1);
        // insert(n->data, ele2);
    }
    // print_info(array);
    // print_info(n->data);
    // float startTime = (float)clock()/CLOCKS_PER_SEC;
    // reverse(array);
    print_info(array);
    // reverse(array, ELE_SIZE);
    quicksort(array, 0, DATA-1, ELE_SIZE);
    // heap_sort(array, DATA, ELE_SIZE);
    print_info(array);
    // matrix_t* result = multiply(m, n, ELE_SIZE);
    // for (int i=0;i<DATA;i++) {
    //         key_t key = *((key_t*) get(array, i));
    //         key += 1;
    //         char ele[ELE_SIZE];
    //         memcpy(ele, &key, sizeof(key_t));
    //         update(array, i, ele);
    // }
    // print_info(array);
    // float endTime = (float)clock()/CLOCKS_PER_SEC;
    // float timeElapsed = endTime - startTime;
    // print_info(array);
    // fprintf(fp, "%s, %f, %d\n", name(array), timeElapsed, ele_size);
    // free_mem(array);
    // free_matrix(m);
    // free_matrix(n);
    // free_matrix(result);
    
}