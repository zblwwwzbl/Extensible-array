#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>
#include "interface.h"

#define MATRIX_SIZE 512

typedef struct {
    void* data;
    word_t rows;
    word_t cols;
} matrix_t;

matrix_t* create_matrix(word_t rows, word_t cols, word_t element_size) {
    matrix_t* matrix = (matrix_t*)malloc(sizeof(matrix_t));
    matrix->rows = rows;
    matrix->cols = cols;
    matrix->data = initialize(DEFAULT_K, element_size, rows*cols);
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

int main(int argc, char *argv[]) {
    FILE* fp = fopen("./data/matrixmult_results.csv", "a");
    srand(SEED); 
    for (word_t ele_size = DEFAULT_ELEMENT_SIZE; ele_size <= LIMIT; ele_size+=DEFAULT_ELEMENT_SIZE) {
        matrix_t* m = create_matrix(MATRIX_SIZE, MATRIX_SIZE, ele_size);
        matrix_t* n = create_matrix(MATRIX_SIZE, MATRIX_SIZE, ele_size);
        for (int i=0;i<MATRIX_SIZE*MATRIX_SIZE;i++) {
            char ele1[ele_size];
            char ele2[ele_size];
            key_t key = (key_t) rand() % 10;
            memcpy(ele1, &key, sizeof(key_t));
            memcpy(ele2, &key, sizeof(key_t));
            insert(m->data, ele1);
            insert(n->data, ele2);
        }
        float startTime = (float)clock()/CLOCKS_PER_SEC;
        matrix_t* result = multiply(m, n, ele_size);
        float endTime = (float)clock()/CLOCKS_PER_SEC;
        float timeElapsed = endTime - startTime;
        fprintf(fp, "%s, %f, %d\n", name(result->data), timeElapsed, ele_size);

        free_matrix(m);
        free_matrix(n);
        free_matrix(result);
    }
}
    

