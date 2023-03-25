#include <stdio.h>
#include "datastructures.h"


int main(int argc, char *argv[]){	
    SQarray_t* SQarray = initialize_SQ_array();
    sliced_array_t* sliced = initialize_sliced_array(DEFAULT_K);
	for (int i=0;i<256;i++) {
        node_t new_node;
        new_node.key = i;
        SQarray_insert(SQarray, new_node);
        sliced_insert(sliced, new_node);
    }
    SQarray_print(SQarray);
    sliced_print(sliced);
    SQarray_free(SQarray);
    sliced_free(sliced);
}