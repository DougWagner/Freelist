#include <stdio.h>
#include <stdlib.h>

#include "flist.h"
#include "fltest.h"

#define FLIST_SIZE 0x100000 // 1 MiB

int main() {
    void * flist_heap = malloc( FLIST_SIZE );
    printf( "flist_heap: %p\n", flist_heap );
    flnode_t * head = flist_init( flist_heap, FLIST_SIZE );
    run_tests( head );
    free( flist_heap );
    return 0;
}