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
    FILE* fp = fopen("./data/incone_results.csv", "a");
    node_t* array = (node_t*)malloc(sizeof(node_t)*NUM_DATA);
    for (unsigned int i=0;i<NUM_DATA;i++) {
        char content[SIZE];
        content[0] = (char) i;
        content[SIZE-1] = (char) i;
        array[i].key = i;
        memcpy(content, array[i].data, SIZE);
    }
    float startTime = (float)clock()/CLOCKS_PER_SEC;
    for (unsigned int i=0;i<NUM_DATA;i++) {
            unsigned int key = array[i].key;
            key += 1;
            array[i].key = key;
        }
    float endTime = (float)clock()/CLOCKS_PER_SEC;
    float timeElapsed = endTime - startTime;
    fprintf(fp, "%s, %f, %lu\n", "base", timeElapsed, sizeof(node_t));
    free(array);
}