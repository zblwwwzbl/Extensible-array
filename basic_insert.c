#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>

#ifndef SIZE
    #define SIZE 12
#endif

#define NUM_DATA 1048576
#define LIMIT 2048
#define SEED 19284729

typedef struct{
    unsigned int key;
    char data[SIZE];
} node_t;

int main(int argc, char *argv[]) {
    FILE* fp = fopen("./data/insert_results.csv", "a");
    srand(SEED);
    float startTime = (float)clock()/CLOCKS_PER_SEC;
    node_t* array = (node_t*)malloc(sizeof(node_t)*NUM_DATA);
    for (unsigned int i=0;i<NUM_DATA;i++) {
        char content[SIZE];
        array[i].key = (unsigned int) rand() % NUM_DATA;
        memcpy(content, array[i].data, SIZE);
    }
    float endTime = (float)clock()/CLOCKS_PER_SEC;
    float timeElapsed = endTime - startTime;
    int rand_index = (int) rand() % NUM_DATA;
    node_t block = array[rand_index];
    for (int i=0;i<SIZE;i++) {
        block.data[i] = block.data[i]+ rand_index + i;
    }
    fprintf(fp, "%s, %f, %lu\n", "base", timeElapsed, sizeof(node_t));
    free(array);
}