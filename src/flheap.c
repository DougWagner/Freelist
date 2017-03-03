#include <stdio.h>
#include <stdlib.h>

#include "flheap.h"
#include "flist.h"

void * flheap;
flnode_t * head;

void fl_install_heap( size_t heapsize ) {
    flheap = malloc( heapsize );
    printf( "flheap installed at %p\n", flheap );
}

void fl_uninstall_heap( void ) {
    free( flheap );
}