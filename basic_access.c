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


// static inline long access(node_t* array) {
//     long count = 0;
//     for (unsigned int i=0;i<NUM_DATA;i++) {
//         long key = array[i].key;
//         count += key;
//     }
//     return count;
// }

static inline long random_access(node_t* array) {
    long count = 0;
    for (unsigned int i=0;i<NUM_DATA;i++) {
        unsigned int idx = rand() % NUM_DATA;
        long key = array[idx].key;
        count += key;
    }
    return count;
}

int main(int argc, char *argv[]) {
    FILE* fp = fopen("./data/random_access_results.csv", "a"); 
    srand(SEED);
    node_t* array = (node_t*)malloc(sizeof(node_t)*NUM_DATA);
    // float startTime = (float)clock()/CLOCKS_PER_SEC;
    for (unsigned int i=0;i<NUM_DATA;i++) {
        char content[SIZE] = {[0 ... SIZE-1] = -1};
        array[i].key = (long) rand() % NUM_DATA;
        memcpy(content, array[i].data, SIZE);
    }
    // float endTime = (float)clock()/CLOCKS_PER_SEC;
    float startTime = (float)clock()/CLOCKS_PER_SEC;
    long count = random_access(array);
    float endTime = (float)clock()/CLOCKS_PER_SEC;
    float timeElapsed = endTime - startTime;
    int rand_index = (int) rand() % NUM_DATA;
    node_t block = array[rand_index];
    for (int i=0;i<SIZE;i++) {
        block.data[i] = block.data[i]+ rand_index + i;
    }
    fprintf(fp, "%s, %f, %lu, %ld\n", "base", timeElapsed, sizeof(node_t), count);
    free(array);
}