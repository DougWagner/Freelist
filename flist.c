#include <stdio.h>
#include <stdlib.h>

#include "flist.h"

flnode_t * fl_init( void * ptr, size_t heap_size ) {
    flnode_t * node = ptr;
    node->next = NULL;
    node->size = heap_size;
    return node;
}
