#include <stdio.h>
#include <stdlib.h>

#include "flheap.h"
#include "flist.h"

void * flheap;
flnode_t * head;

void fl_install_heap( size_t heapsize ) {
    flheap = malloc( heapsize );
    head = fl_init( flheap, heapsize );
    printf( "flheap installed at %p\n", flheap );
}

void fl_uninstall_heap( void ) {
    free( flheap );
}

void * fl_malloc( size_t size ) {
    flnode_t * tmp = fl_get_next_free( head, size );
    printf( "fl_get_next_free returned flnode_t at %p\n", tmp );
    if ( tmp == head ) { // memory located at head
        if ( head->next == NULL ) {
            size_t oldsize = head->size;
            size_t memsize = sizeof( memobj_t ) + size;
            void * newhead = ( void * ) head + memsize;
            head = newhead;
            head->next = NULL;
            head->size = oldsize - memsize;
        }
        else {
            head = head->next;
        }
        memobj_t * obj = fl_allocate_at_node( tmp, size );
        printf( "memory allocated - head moved to %p\n", head );
        return ( void * ) obj + sizeof( memobj_t );
    }
    return NULL;
}

void fl_free( void * ptr ) {

}