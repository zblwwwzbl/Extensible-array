#include <stdio.h>
#include <stdlib.h>
#include "general.h"


int main(int argc, char *argv[]){	
    void* array = initialize(DEFAULT_K, DEFAULT_ELEMENT_SIZE);
	for (int i=0;i<256;i++) {
        char ele[DEFAULT_ELEMENT_SIZE];
        key_t key = i;
        memcpy(&key, ele, sizeof(key_t));
        insert(array, ele);
    }
    print_info(array);
    free_mem(array);
}