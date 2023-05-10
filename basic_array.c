#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>

#ifndef SIZE
    #define SIZE 12
#endif

#ifndef NUM_ELE
    #define NUM_ELE 1048576
#endif

#define NUM_DATA 1048576
#define LIMIT 2048
#define SEED 19284729

typedef struct{
    long key;
    char data[SIZE];
} node_t;

static inline void incone(node_t* array) {
    for (unsigned int i=0;i<NUM_DATA;i++) {
        unsigned int key = array[i].key;
        key += 1;
        array[i].key = key;
    }
}

static inline unsigned int access(node_t* array) {
    unsigned int count = 0;
    for (unsigned int i=0;i<NUM_DATA;i++) {
        unsigned int key = array[i].key;
        count += key;
    }
    return count;
}

static inline unsigned int random_access(node_t* array) {
    unsigned int count = 0;
    for (unsigned int i=0;i<NUM_DATA;i++) {
        unsigned int idx = rand() % NUM_DATA;
        unsigned int key = array[idx].key;
        count += key;
    }
    return count;
}

static inline void reverse(node_t *array, int num_data) {
    int i, j;
    node_t temp;

    for (i = 0, j = num_data - 1; i < j; i++, j--) {
        temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }
}

static void quicksort(node_t arr[], unsigned int low, unsigned int high) {
    if (low < high && high + 1 != 0) {
        long pivot = arr[high].key;
        unsigned int i = (low - 1);
        node_t temp;
        for (int j = low; j <= high - 1; j++) {
            if (arr[j].key < pivot) {
                i++;
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
        temp = arr[i+1];
        arr[i+1] = arr[high];
        arr[high] = temp;
        unsigned int pi = i + 1;
        quicksort(arr, low, pi - 1);
        quicksort(arr, pi + 1, high);
    }
}

static void heapify(node_t* arr, int n, int i) {
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    node_t temp;

    if (l < n && arr[l].key > arr[largest].key)
        largest = l;

    if (r < n && arr[r].key > arr[largest].key)
        largest = r;

    if (largest != i) {
        temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;

        heapify(arr, n, largest);
    }
}

static void heapSort(node_t* arr, int n) {
    node_t temp;
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    for (int i = n - 1; i > 0; i--) {
        temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;

        heapify(arr, i, 0);
    }
}


int main(int argc, char *argv[]) {
    char buffer[100];
    sprintf(buffer, "./data/%s_results.csv", argv[1]);
    FILE* fp = fopen(buffer, "a");
    srand(SEED);
    int num_ele = (int) NUM_ELE;
    node_t* array = (node_t*)malloc(sizeof(node_t)*num_ele);
    // float startTime = (float)clock()/CLOCKS_PER_SEC;
    for (unsigned int i=0;i<num_ele;i++) {
        char content[SIZE] = {[0 ... SIZE-1] = -1};
        array[i].key = (unsigned int) rand() % num_ele;
        memcpy(content, array[i].data, SIZE);
    }
    // float endTime = (float)clock()/CLOCKS_PER_SEC;
    float startTime = (float)clock()/CLOCKS_PER_SEC;
    if (strcmp(argv[1], "reverse") == 0) {
        reverse(array, NUM_DATA);
    } else if (strcmp(argv[1], "incone") == 0) {
        incone(array);
    } else if (strcmp(argv[1], "sort") == 0) {
        quicksort(array, 0, NUM_DATA-1);
    } else if (strcmp(argv[1], "heapsort") == 0) {
        heapSort(array, NUM_DATA);
    } else if (strcmp(argv[1], "access") == 0) {
        unsigned int count = access(array);
        array[0].key = count;
    } else if (strcmp(argv[1], "random_access") == 0) {
        unsigned int count = random_access(array);
        array[0].key = count;
    }
    float endTime = (float)clock()/CLOCKS_PER_SEC;
    float timeElapsed = endTime - startTime;
    int rand_index = (int) rand() % num_ele;
    node_t block = array[rand_index];
    for (int i=0;i<SIZE;i++) {
        block.data[i] = block.data[i]+ rand_index + i;
    }
    fprintf(fp, "%s, %f, %d\n", "base", timeElapsed, num_ele);
    free(array);
}